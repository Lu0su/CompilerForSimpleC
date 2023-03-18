//the actural function to handle lex_process
#include "compiler.h"
#include "helpers/buffer.h"
#include "helpers/vector.h"
#include <assert.h>
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

static struct pos lex_file_position()
{
    return the_lex_process->pos;
}

struct token* token_create(struct token* the_token)
{
    memcpy(&tmp_token, the_token, sizeof(struct token));
    tmp_token.pos = lex_file_position();
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

struct token*              read_next_token()
{
    struct token* the_token = NULL;
    // read but do not mov the fptr
    char          c         = peekc();
    switch (c) {
    NUMERIC_CASE:
        // printf("number token: %c \n", c);
        the_token = token_make_number();
        printf("number token: %lld \n", the_token->llnum);
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

    case '"':
        // printf("this is a string:\n");
        the_token = token_make_string('"', '"');
        printf("string token: %s \n", the_token->sval);
        break;

        // we do not care whitespace
    // but we net the_token not to be NULL
    case ' ':
    case '\t': the_token = handle_whitespace(); break;

    case EOF: printf("this is Eof"); break;

    default:
        printf("the unexpect char is %c, and the value is %d \n", c, c);
        compiler_error(the_lex_process->compiler, "unexpect token", NULL);
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
