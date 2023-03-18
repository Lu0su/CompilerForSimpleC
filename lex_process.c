#include "compiler.h"
#include "helpers/vector.h"
#include <stdlib.h>

struct lex_process* lex_process_creat(struct compile_process*       compiler,
                                      struct lex_process_functions* functions, void* the_private)
{
    // init a lex_process, like a constuctor in C++
    printf("into the lex_process\n");
    struct lex_process* process = (struct lex_process*)calloc(1, sizeof(struct lex_process));
    process->compiler           = compiler;
    process->function           = functions;
    process->token_ve           = vector_create(sizeof(struct token));
    process->the_private        = the_private;
    process->pos.col            = 1;
    process->pos.line           = 1;
    return process;
}

void free_lex_process(struct lex_process* process)
{
    // destructor like C++
    vector_free(process->token_ve);
    free(process);
}

void* get_lex_process_private(struct lex_process* process)
{
    return process->the_private;
}

void* get_lex_process_token_ve(struct lex_process* process)
{
    return process->token_ve;
}
