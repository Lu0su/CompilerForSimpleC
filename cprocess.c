// charge for the complie text.c file and output it
#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
struct compile_process* compile_process_create(const char* filename, const char* filename_out,
                                               int flags)
{
    printf("into comile_process func\n");
    // preprocess make sure everthing is fine.
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    FILE* out_file = fopen(filename_out, "w");
    if (!filename_out) {
        return NULL;
    }
    // coppile process read
    struct compile_process* process =
        (struct compile_process*)calloc(1, sizeof(struct compile_process));
    // how does const char* -> FILE* ?
    process->flags                  = flags;
    process->cfile.ifile            = file;
    process->ofile                  = out_file;

    return process;
}

char compile_process_next_char(struct lex_process* lex_process)
{
    // if we get a \n, we do not handle it here
    struct compile_process* compiler = lex_process->compiler;
    compiler->pos.col++;
    char c = getc(compiler->cfile.ifile);
    if (c == '\n') {
        compiler->pos.line++;
        compiler->pos.col = 1;
    }

    return c;
}

char compile_process_pick_char(struct lex_process* lex_process)
{
    struct compile_process*  compiler = lex_process->compiler;
    char                     c        = getc(compiler->cfile.ifile);
    // it will push_back to the file stream
    ungetc(c, compiler->cfile.ifile);
    return c;
}

void compile_process_push_char(struct lex_process* lex_process, char c)
{
    struct compile_process* compiler = lex_process->compiler;
    ungetc(c, compiler->cfile.ifile);
}
