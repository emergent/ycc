#ifndef _YCC_H_
#define _YCC_H_

/**
 * keywords:
 * auto     double  int      struct
 * break    else    long     switch
 * case     enum    register typedef
 * char     extern  return   union
 * const    float   short    unsigned
 * continue for     signed   void
 * default  goto    sizeof   volatile
 * do       if      static   while
 */





// for reader
int lex(char** tokens, const char* src);

// for list
typedef struct _cell {
    void *data;
    struct _cell *next;
} Cell;

typedef struct _list {
    Cell *top;
    Cell *last;
} List;

List* list_create();
List* list_append(List* list, void* data);
void  list_destroy(List *l);

#endif
