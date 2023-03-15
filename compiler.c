#include "compiler.h"
//point the file name that need to be compile and the output filename
//flags show how we should compile the text.c file
int compile_file(const char* filename, const char* output_filename, int flags){
    struct compile_process* process = compile_process_create(filename, output_filename, flags);
    if (!process) {
        return COMPILER_FALSE_WITH_ERROR;
    }

    // lexical analyzer

    return COMPILER_FILE_COMPILE_OK;
}
