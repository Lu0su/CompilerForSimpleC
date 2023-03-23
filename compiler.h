#ifndef LUOSUCOMPILE_H
#define LUOSUCOMPILE_H
#include "helpers/vector.h"
#include <stdbool.h>   // for bool
#include <stdio.h>
#include <string.h>

// EQ function
#define S_EQ(str1, str2) (str1 && str2 && (!strcmp(str1, str2)))


/*
 *part1 the struct token
 * */

// pos
struct pos
{
    int         line;
    int         col;
    const char* filename;   // foe multi contain files
};

#define NUMERIC_CASE \
case '0':            \
case '1':            \
case '2':            \
case '3':            \
case '4':            \
case '5':            \
case '6':            \
case '7':            \
case '8':            \
case '9'

#define OPERATOR_CASE_EXCLUDING_DIVISION \
case '+':                                \
case '-':                                \
case '*':                                \
case '>':                                \
case '<':                                \
case '^':                                \
case '%':                                \
case '!':                                \
case '=':                                \
case '~':                                \
case '|':                                \
case '&':                                \
case '(':                                \
case '[':                                \
case ',':                                \
case '.':                                \
case '?'

#define SYMBOL_CASE \
case '{':           \
case '}':           \
case ':':           \
case ';':           \
case '#':           \
case '\\':          \
case ')':           \
case ']'

// all lex retrun type
enum
{
    LEX_ANALYSIS_ALL_OK,
    LEX_ANALYSIS_INPUT_ERROR
};

// all the token type
enum
{
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_ID,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
};

// the token struct
struct token
{
    int type;   // TOKEN TYPE
    int flags;
    struct pos pos;

    // basicly store every thing
    union
    {
        char               cval;
        const char*        sval;
        unsigned int       inum;
        unsigned long      lnum;
        unsigned long long llnum;
        void*              any;
    };
    // true if there is whitespace between this token an next token
    bool whitespace;
    // string between break like (2+3+4) - > 2+3+4
    const char* between_brack;
};

/*
 *part2 the struct lex
 * */
struct lex_process;
typedef char (*LEX_PROCESS_NEXT_CHAR)(struct lex_process* process);
typedef char (*LEX_PROCESS_PICK_CHAR)(struct lex_process* process);
typedef void (*LEX_PROCESS_PUSH_CHAR)(struct lex_process* process, char c);

struct lex_process_functions
{
    // some function we need to use in lex_process
    LEX_PROCESS_PUSH_CHAR push_char;
    LEX_PROCESS_NEXT_CHAR next_char;
    LEX_PROCESS_PICK_CHAR pick_char;
};

struct lex_process
{
    // the lex_process
    struct pos              pos;
    struct vector*          token_ve;
    struct compile_process* compiler;

    // ((50)) no need to worry about now
    int                          current_expression_count;
    struct buffer*               parentheses_buffer;
    struct lex_process_functions* function;

    // only you need to know
    void* the_private;
};

// enum for status ok / false
enum
{
    COMPILER_FALSE_WITH_ERROR = 0,
    COMPILER_FILE_COMPILE_OK
};
struct compile_process
{
    // flags shows how this file show be compile
    int flags;

    struct pos pos;

    // what does this do?
    // info of input file and output file
    struct compile_process_input_file
    {
        FILE*       ifile;
        const char* abs_path;
    } cfile;

    FILE* ofile;
};
//
int compile_file(const char* filename, const char* output_filename, int flags);

void compiler_error(struct compile_process* process, const char* msg, ...);
void compiler_warning(struct compile_process* process, const char* msg, ...);

// struct compiler_process store the info we need for compile
struct compile_process* compile_process_create(const char* filename, const char* filename_out,
                                               int flags);
char                    compile_process_next_char(struct lex_process* lex_process);

char compile_process_pick_char(struct lex_process* lex_process);

void compile_process_push_char(struct lex_process* lex_process, char c);

/*
 * the methods that lex_process may need
 * */

struct lex_process* lex_process_creat(struct compile_process*       compiler,
                                      struct lex_process_functions* functions, void* the_private);
void                free_lex_process(struct lex_process* process);

void* get_lex_process_private(struct lex_process* process);
void*               get_lex_process_token_ve(struct lex_process* process);
int                 lex(struct lex_process* process);
bool                token_is_keyword(struct token* the_token, const char* keyword);
#endif
