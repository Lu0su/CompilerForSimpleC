#ifndef LUOSUCOMPILE_H
#define LUOSUCOMPILE_H
#include <stdio.h>
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
// struct compiler_process store the info we need for compile
struct compile_process* compile_process_create(const char* filename, const char* filename_out,
                                               int flags);
#endif
