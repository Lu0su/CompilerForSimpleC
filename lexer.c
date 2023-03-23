//the actural function to handle lex_process
#include "compiler.h"
#include "helpers/buffer.h"
#include "helpers/vector.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// if filter, write the eligible c into the buffer tair
#define LEX_GETC_IF(buffer, c, exp)       \
    for (c = peekc(); exp; c = peekc()) { \
        buffer_write(buffer, c);          \
        nextc();                          \
    }

struct token*              read_next_token();
static struct lex_process* the_lex_process;
static struct token        tmp_token;
bool lex_is_in_expression();
/*
 *
 * the meta func we need to handle a char
 *
 */
static char peekc()
{
    return the_lex_process->function->pick_char(the_lex_process);
}

static char nextc()
{
    char c = the_lex_process->function->next_char(the_lex_process);
    if (lex_is_in_expression()){
        // if we are in the expression
        // we write it into the parentheses_buffer for debug information
        buffer_write(the_lex_process->parentheses_buffer, c);
    }
    the_lex_process->pos.col++;
    // we get the \n but we did not handle it
    if (c == '\n') {
        the_lex_process->pos.line++;
        the_lex_process->pos.col = 1;
    }

    return c;
}

static void pushc(char c)
{
    the_lex_process->function->push_char(the_lex_process, c);
    return;
}

// assert if the next char is gave c
static char assert_next_char(char c)
{
    char next_c = nextc();
    assert(c == next_c);
    return next_c;
}

static struct pos lex_file_position()
{
    return the_lex_process->pos;
}

struct token* token_create(struct token* the_token)
{
    memcpy(&tmp_token, the_token, sizeof(struct token));
    tmp_token.pos = lex_file_position();
    if (lex_is_in_expression()){
        // (10 + 4 + 3) for any token in this expression, we can get the full
        // expression of 10 + 4 + 3 i
        tmp_token.between_brack = buffer_ptr(the_lex_process->parentheses_buffer);
    }
    return &tmp_token;
}

/*
 *
 *
 *hanle whitespace
 *
 *
 * */

static struct token* lex_last_token()
{
    return vector_back_or_null(the_lex_process->token_ve);
}

// handle the whitespace like space \n and \t
static struct token* handle_whitespace()
{
    struct token* last_token = lex_last_token();
    if (last_token) {
        last_token->whitespace = true;
    }
    nextc();
    return read_next_token();
}

/*
 *
 * handle the number
 *
 *
 * */

const char* read_number_str()
{
    const char*    num    = NULL;
    struct buffer* buffer = buffer_create();
    char           c      = peekc();
    LEX_GETC_IF(buffer, c, (c >= '0' && c <= '9'));
    buffer_write(buffer, 0x00);   // the end \0

    return buffer_ptr(buffer);
}

unsigned long long read_number()
{
    const char* s = read_number_str();
    return atoll(s);   // long long unsigned
}

struct token* token_make_number_for_value(unsigned long long number)
{
    printf("number token: %lld \n", number);
    return token_create(&(struct token){.type = TOKEN_TYPE_NUMBER, .llnum = number});
}

struct token* token_make_number()
{
    return token_make_number_for_value(read_number());
}

/*
 *
 *
 *handle the string
 *
 *
 * */
static struct token* token_make_string(char start_delim, char end_delim)
{
    struct buffer* buf = buffer_create();
    assert(nextc() == start_delim);
    char           c   = nextc();
    for (; c != end_delim && c != EOF; c = nextc()) {
        if (c == '\\') {
            // handle \n something, not now
            continue;
        }
        buffer_write(buf, c);
    }

    buffer_write(buf, c);
    return token_create(&((struct token){.type = TOKEN_TYPE_STRING, .sval = buffer_ptr(buf)}));
}


/*
 *
 *
 *handle the expression
 *
 *
 * */

// handle the multi expression
//() is an expression
//( () ) the () inside the () will be in the buffer that created here
static void lex_new_expression()
{
    the_lex_process->current_expression_count++;
    if (the_lex_process->current_expression_count == 1) {
        the_lex_process->parentheses_buffer = buffer_create();
    }
}

static void lex_finish_expression()
{
    // this should at least be 0
    the_lex_process->current_expression_count--;
    if (the_lex_process->current_expression_count < 0) {
        compiler_error(the_lex_process->compiler, "you close an expression that you never opened");
    }
}


bool lex_is_in_expression()
{
    // if we are in the expression, return true
    return the_lex_process->current_expression_count > 0;
}

bool is_keyword(const char* str)
{
    return S_EQ(str, "unsigned") || S_EQ(str, "signed") || S_EQ(str, "signed") ||
           S_EQ(str, "char") || S_EQ(str, "short") || S_EQ(str, "int") || S_EQ(str, "long") ||
           S_EQ(str, "float") || S_EQ(str, "double") || S_EQ(str, "void") || S_EQ(str, "struct") ||
           S_EQ(str, "union") || S_EQ(str, "static") || S_EQ(str, "_ignore_typecheck") ||
           S_EQ(str, "return") || S_EQ(str, "include") || S_EQ(str, "sizeof") || S_EQ(str, "if") ||
           S_EQ(str, "else") || S_EQ(str, "while") || S_EQ(str, "for") || S_EQ(str, "do") ||
           S_EQ(str, "break") || S_EQ(str, "continue") || S_EQ(str, "switch") ||
           S_EQ(str, "case") || S_EQ(str, "default") || S_EQ(str, "goto") || S_EQ(str, "typedef") ||
           S_EQ(str, "const") || S_EQ(str, "extern") || S_EQ(str, "restrict");
}


/*
 *
 *
 * handle the operator
 *
 *
 *
 * */

// op but no follow up
static bool op_treated_as_one(char op)
{
    // may only need to be handle once
    return op == '(' || op == '[' || op == ',' || op == '.' || op == '?' || op == '*';
}

// ops can be the back of an op
static bool is_single_operator(char op)
{
    return op == '+' || op == '-' || op == '/' || op == '*' || op == '=' || op == '>' ||
           op == '<' || op == '|' || op == '&' || op == '^' || op == '%' || op == '!' ||
           op == '(' || op == '[' || op == ',' || op == '.' || op == '~' || op == '?';
}

bool op_valid(const char* op)
{
    // search if qualify
    return S_EQ(op, "+") || S_EQ(op, "-") || S_EQ(op, "*") || S_EQ(op, "/") || S_EQ(op, "!") ||
           S_EQ(op, "^") || S_EQ(op, "+=") || S_EQ(op, "-=") || S_EQ(op, "*=") || S_EQ(op, "/=") ||
           S_EQ(op, ">>") || S_EQ(op, "<<") || S_EQ(op, "<=") || S_EQ(op, ">") || S_EQ(op, "<") ||
           S_EQ(op, "||") || S_EQ(op, "&&") || S_EQ(op, "|") || S_EQ(op, "&") || S_EQ(op, "++") ||
           S_EQ(op, "--") || S_EQ(op, "=") || S_EQ(op, "!=") || S_EQ(op, "==") || S_EQ(op, "->") ||
           S_EQ(op, "(") || S_EQ(op, "[") || S_EQ(op, ",") || S_EQ(op, ".") || S_EQ(op, "...") ||
           S_EQ(op, "~") || S_EQ(op, "?") || S_EQ(op, "%");
}

void read_op_flush_back_keep_first(struct buffer* buf)
{
    const char* data = buffer_ptr(buf);
    int         len  = buf->len;
    // from back to front, only leave the first one
    for (int i = len - 1; i > 0; i--) {
        if (data[i] == 0x00) {
            continue;
        }
        // push back to the stream
        pushc(data[i]);
    }

    return;
}

const char* read_op()
{
    bool           single_operator = true;
    char           op              = nextc();
    struct buffer* buf             = buffer_create();
    buffer_write(buf, op);

    if (!op_treated_as_one(op)) {
        op = peekc();
        if (is_single_operator(op)) {
            buffer_write(buf, op);
            nextc();
            // do not take the ***
            single_operator = false;
        }
    }

    buffer_write(buf, 0x00);
    char* ptr = buffer_ptr(buf);
    if (!single_operator) {
        if (!op_valid(ptr)) {
            // if it is not qualify
            // push_back the characters aside from the first one
            // like +(, we only leave +, and push ( back to stream
            read_op_flush_back_keep_first(buf);
            ptr[1] = 0x00;   // end it
        }
    }
    else if (!op_valid(ptr)) {
        compiler_error(the_lex_process->compiler, "the op %s is not valid", ptr);
    }
    return ptr;
}

static struct token* token_make_operator_or_string()
{
    char op = peekc();
    if (op == '<') {
        struct token* last_token = lex_last_token();
        if (token_is_keyword(last_token, "include")) {
            return token_make_string('<', '>');
        }
    }
    struct token* token =
        token_create(&(struct token){.type = TOKEN_TYPE_STRING, .sval = read_op()});

    if (op == '(') {
        // we are in an expression now
        lex_new_expression();
    }
    return token;
}

/*
 *
 *
 * handle sybole
 *
 * */

static struct token* token_make_symbol()
{
    char c = nextc();
    if (c == ')') {
        // the end of the expression
        lex_finish_expression();
    }

    struct token* the_token = token_create(&(struct token){.type = TOKEN_TYPE_SYMBOL, .cval = c});
    return the_token;
}


static struct token* token_make_id_or_key()
{
    struct buffer* buf  = buffer_create();
    char           c    = 0;
    LEX_GETC_IF(
        buf,
        c,
        ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'));

    buffer_write(buf, 0x00);

    // check if this is a keyword
    if (is_keyword(buffer_ptr(buf))) {
        return token_create(&(struct token){.type = TOKEN_TYPE_KEYWORD, .sval = buffer_ptr(buf)});
    }

    // create token for id
    return token_create(&(struct token){.type = TOKEN_TYPE_ID, .sval = buffer_ptr(buf)});
}

struct token* read_special_token()
{
    char c = peekc();
    if (isalpha(c) || c == '_') {
        return token_make_id_or_key();
    }

    return NULL;
}

/*
 *
 *
 * handle newline
 *
 *
 * */

struct token* token_make_newline()
{
    nextc();
    return token_create(&(struct token){.type = TOKEN_TYPE_NEWLINE, .cval = '\n'});
}


/*
 *
 *
 *handle the comment
 *
 *
 * */

struct token* token_make_one_line_comment()
{
    struct buffer* buf = buffer_create();
    char           c   = 0;
    LEX_GETC_IF(buf, c, c != '\n' && c != EOF);
    return token_create(&(struct token){.type = TOKEN_TYPE_COMMENT, .sval = buffer_ptr(buf)});
}

struct token* token_make_multi_comments()
{
    struct buffer* buf = buffer_create();
    char           c   = 0;
    while (1) {
        LEX_GETC_IF(buf, c, c != '*' && c != EOF);
        if (c == EOF) {
            compiler_error(the_lex_process->compiler, "you did not close this multi comments");
        }
        else if (c == '*') {
            nextc();
            if (peekc() == '/') {
                nextc();
                break;
            }
        }
    }
    return token_create(&(struct token){.type = TOKEN_TYPE_COMMENT, .sval = buffer_ptr(buf)});
}


struct token* handle_comment()
{
    char c = peekc();
    if (c == '/') {
        nextc();
        if (peekc() == '/') {
            nextc();
            return token_make_one_line_comment();
        }
        else if (peekc() == '*') {
            nextc();
            return token_make_multi_comments();
        }

        // the div operator
        pushc('/');
        return token_make_operator_or_string();
    }

    return NULL;
}

/*
 *
 *
 * handle quote like ''
 * it is a single quote expression like 'a', '\t', '\n'
 * it contains only one useful character
 *
 *
 * */
char lex_get_esacped_char(char c)
{
    char co = 0;
    switch (c) {
    case 'n': co = '\n'; break;
    case 't': co = '\t'; break;
    case '\'': co = '\''; break;
    }

    return co;
}

struct token* token_make_quote()
{
    assert_next_char('\'');
    char c = nextc();
    // \n - > n
    if (c == '\\') {
        c = nextc();   // we got n if it is a \n
        c = lex_get_esacped_char(c);   // handle the n
    }

    if (nextc() != '\'') {
        compiler_error(the_lex_process->compiler,
                       "you opened a quote butt not close it with another ' character");
    }

    return token_create(&(struct token){.type = TOKEN_TYPE_NUMBER, .cval = c});
}

/*
 *
 *
 * handle special number
 * like 0x1ffc, 084
 *
 *
 * */

void lex_pop_token()
{
    vector_pop(the_lex_process->token_ve);
}

bool is_hex_char(char c)
{
    // turn it to lower case
    c = tolower(c);
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

const char* read_hex_number_str()
{
    struct buffer* buf = buffer_create();
    char           c   = peekc();
    LEX_GETC_IF(buf, c, is_hex_char(c));
    buffer_write(buf, 0x00);
    return buffer_ptr(buf);
}

void lex_validate_binary_string(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; ++i) {
        if (str[i] != '0' && str[i] != '1') {
            compiler_error(the_lex_process->compiler, "This is not vaild a binary number\n");
        }
    }
}

struct token* token_make_special_number_bin()
{
    // skip the 'b'
    nextc();

    unsigned long long number     = 0;
    const char*        number_str = read_number_str();   // get number_str
    lex_validate_binary_string(number_str);              // make sure it is binary string
    number = strtol(number_str, 0, 2);
    return token_make_number_for_value(number);
}

struct token* token_make_special_number_hex()
{
    // Skip the 'x'
    nextc();

    unsigned long number     = 0;
    const char*   number_str = read_hex_number_str();
    number                   = strtol(number_str, 0, 16);   // basic on 16
    return token_make_number_for_value(number);             // handle it to the number token
}

struct token* token_make_special_number()
{
    struct token* the_token = NULL;
    struct token* last_token = lex_last_token();

    // last_token is void or not the value we need
    if (!last_token || !(last_token->type == TOKEN_TYPE_NUMBER && last_token->llnum == 0)) {
        return token_make_id_or_key();
    }
    // pop off the last token
    lex_pop_token();

    char c = peekc();
    if (c == 'x') {
        the_token = token_make_special_number_hex();
    }
    else if (c == 'b') {
        the_token = token_make_special_number_bin();
    }

    // if it start with 0x, we can successful get the hex number
    // else we push back the 0 we just pop back
    return the_token;
}

struct token*              read_next_token()
{
    struct token* the_token = handle_comment();
    if (the_token) {
        if (the_token->type == TOKEN_TYPE_COMMENT)
            printf("comment token: %s \n", the_token->sval);
        else
            printf("operator token: %s \n", the_token->sval);
        return the_token;
    }

    // read but do not mov the fptr
    char          c         = peekc();

    switch (c) {
    NUMERIC_CASE:
        // printf("number token: %c \n", c);
        the_token = token_make_number();
        break;

    OPERATOR_CASE_EXCLUDING_DIVISION:
        // printf("operator token: %c \n", c);
        the_token = token_make_operator_or_string();
        printf("operator token: %s \n", the_token->sval);
        break;

    SYMBOL_CASE:
        the_token = token_make_symbol();
        printf("symbol token: %c \n", the_token->cval);
        break;

    // before the string token
    case 'x': the_token = token_make_special_number(); break;

    case '"':
        // printf("this is a string:\n");
        the_token = token_make_string('"', '"');
        printf("string token: %s \n", the_token->sval);
        break;
    case '\'':
        the_token = token_make_quote();
        printf("quote token: %c \n", the_token->cval);
        break;

    // we do not care whitespace
    // but we net the_token not to be NULL
    case ' ':
    case '\t': the_token = handle_whitespace(); break;

    case '\n': the_token = token_make_newline(); break;

    case EOF: printf("this is Eof"); break;

    default:
        // 23jk will not be there, 23 will be the number token
        // but jk232 can be there
        the_token = read_special_token();
        if (!the_token) {
            printf("the unexpect char is %c, and the value is %d \n", c, c);
            compiler_error(the_lex_process->compiler, "unexpect token", NULL);
        }
        else {
            the_token->type == TOKEN_TYPE_KEYWORD ? printf("keword token: %s \n", the_token->sval)
                                                  : printf("id token: %s \n", the_token->sval);
        }
        break;
    }

    return the_token;
}

int lex(struct lex_process* process)
{
    printf("into the lexer \n");
    process->current_expression_count = 0;   //?
    process->parentheses_buffer       = NULL;   //?
    the_lex_process                   = process;   // a ptr but why -> static var to call function
    process->pos.filename             = process->compiler->cfile.abs_path;   // from inside?
    struct token* the_token           = read_next_token();
    while (the_token) {
        vector_push(process->token_ve, &the_token);
        the_token = read_next_token();
    }

    return LEX_ANALYSIS_ALL_OK;
}
