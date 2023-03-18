#include "compiler.h"
#include "helpers/vector.h"
#include <stdio.h>
void text1();
void text2();
int main(void)
{
    text2();
    exit(1);
}

void text1()
{
    printf("hello world \n");
    struct vector* vec = vector_create(sizeof(int));
    int            x   = 40;
    vector_push(vec, &x);
    x = 20;
    vector_push(vec, &x);
    vector_set_peek_pointer(vec, 0);
    int* ptr = (int*)vector_peek(vec);
    while (ptr) {
        printf("%i \n", *ptr);
        ptr = (int*)vector_peek(vec);   //++ptr
    }
    vector_pop(vec);   // pop_back one elem
    return;
}

void text2()
{
    int res = compile_file("./text.c", "text.txt", 0);
    if (res == COMPILER_FILE_COMPILE_OK) {
        printf("everything is ok\n");
    }
    else if (res == COMPILER_FALSE_WITH_ERROR) {
        printf("compile false\n");
    }
    else {
        printf("unknow expection\n");
    }

    return;
}
