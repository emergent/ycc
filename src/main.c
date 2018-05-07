#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "ycc.h"

#define BUFSIZE 256

size_t get_file_size(char* filename) {
    struct stat st;
    if(stat(filename, &st) == -1) {
        return -1L;
    }
    return st.st_size;
}

char* read_source(char* filename) {
    FILE *fp;
    char *data = NULL, *p;
    char buf[BUFSIZE];
    size_t len = 0, datasize;

    printf("filename: %s\n", filename);
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "failed opening source file: %s\n", filename);
        return NULL;
    }
    datasize = sizeof(char)*get_file_size(filename);
    data = (char*)malloc(datasize);
    if (!data) {
        fprintf(stderr, "failed malloc size: %zu\n", datasize);
        return NULL;
    }
    p = data;
    while (fgets(buf, BUFSIZE, fp)) {
        len = strlen(buf);
        printf("%3zu| %s", len, buf);
        strncpy(p, buf, len);
        p += len; 
    }
    fclose(fp);

    return data;
}

int preprocess(List* directives, char **dst, const char* src) {
    /*
    * - process directives
    * - skip comments
    */

    *dst = (char*)src; // temporary

    return 0;
}

/**
 * frontend:
 * - lexical analysis
 * - parsing, syntax analysis
 * - semantic analysis
 * 
 * backend:
 * - code optimizetion
 * - generate assembly code
 */
int process(char* srcfiles[], char* dst) {
    char* srcfile = srcfiles[0];
    char* source;

    if (!(source = read_source(srcfile))) {
        printf("failed reading source file: %s\n", srcfile);
        return -1;
    }
    
    List *tokens, *directives;
    if (!(tokens = list_create()) || !(directives = list_create())) {
        return -1;
    }

    int err;
    // preprocessor
    char* src_pped = NULL;
    err = preprocess(directives, &src_pped, source);

    // lex
    err = lex(tokens, directives, source);

    // throw away original source
    free(source);

    list_destroy(tokens);
    list_destroy(directives);
    
    return 0;
}

int main(int argc, char* argv[]) {
    char* sources[10];

    /* parse options */
    printf("argc: %d\n", argc);
    if (argc > 0) {
        for (int i = 0; i < argc; i++) {
            printf("argv[%d]: %s\n", i, argv[i]);
        }
    }
    sources[0] = argv[1]; // temporary

    int ret = process(sources, NULL);
    
    return ret;
}
