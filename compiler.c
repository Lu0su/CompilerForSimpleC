#include "compiler.h"
#include <stdarg.h>
#include <stdlib.h>
//point the file name that need to be compile and the output filename
//flags show how we should compile the text.c file

struct lex_process_functions compile_lex_functions = {.next_char = compile_process_next_char,
                                                      .pick_char = compile_process_pick_char,
                                                      .push_char = compile_process_push_char};

//... do not understand it yet, latter
void compiler_error(struct compile_process* process, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);

    fprintf(stderr,
            " on line %i, col %i, in file %s\n ",
            process->pos.line,
            process->pos.col,
            process->pos.filename);
    exit(1);
}

void compiler_warning(struct compile_process* process, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);

    fprintf(stderr,
            " on line %i, col %i, in file %s\n ",
            process->pos.line,
            process->pos.col,
            process->pos.filename);
}

int compile_file(const char* filename, const char* output_filename, int flags){
    struct compile_process* process = compile_process_create(filename, output_filename, flags);
    if (!process) {
        return COMPILER_FALSE_WITH_ERROR;
    }

    // lexical analyzer
    struct lex_process* the_lex_process = lex_process_creat(process, &compile_lex_functions, NULL);
    if (!the_lex_process) {
        printf("lex_process init error \n");
        return COMPILER_FALSE_WITH_ERROR;
    }

    if (lex(the_lex_process) != LEX_ANALYSIS_ALL_OK) {
        printf("lex_process false \n");
        return COMPILER_FALSE_WITH_ERROR;
    }

    return COMPILER_FILE_COMPILE_OK;
}
