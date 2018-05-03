#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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

int main(int argc, char* argv[]) {
    char *source;

    printf("argc: %d\n", argc);
    if (argc > 0) {
        for (int i = 0; i < argc; i++) {
            printf("argv[%d]: %s\n", i, argv[i]);
        }
    }

    if (!(source = read_source(argv[1]))) {
        printf("failed reading source file\n");
    }
    printf("source:\n%s\n", source);

    free(source);
    return 0;
}
