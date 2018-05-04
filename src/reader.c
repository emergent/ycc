#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ycc.h"

char* read_next(char* p) {
    return p+1;
}

char* string_new(const char* str) {
    char* dst = (char*)malloc(sizeof(char)*strlen(str)+1);
    strncpy(dst, str, strlen(str));
    return dst;
}

void print_tokens(List* l) {
    if (l) {
        Cell* p;
        int count;
        for (count=0, p=l->top; p; count++,p=p->next) {
            printf("[%03d] %s\n", count, (char*)p->data);
        }

    }
}

int read_tokens(List* list, const char* p) {
    /* temporaly code */
    list_append(list, (void*)string_new("int"));
    list_append(list, (void*)string_new("main"));
    list_append(list, (void*)string_new("("));
    list_append(list, (void*)string_new(")"));
    list_append(list, (void*)string_new("{"));
    list_append(list, (void*)string_new("return"));
    list_append(list, (void*)string_new("0"));
    list_append(list, (void*)string_new(";"));
    list_append(list, (void*)string_new("}"));
    
    print_tokens(list);

    return 0;
}

int lex(char** tokens, const char* source) {
    List* list = list_create();
    int err;

    if (!list) { return -1; }

    err = read_tokens(list, source);
    list_destroy(list);

    return 0;
}
