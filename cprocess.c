// charge for the complie text.c file and output it
#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
struct compile_process* compile_process_create(const char* filename, const char* filename_out,
                                               int flags)
{
    printf("into comile_process func");
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
