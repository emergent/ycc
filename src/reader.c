#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ycc.h"

char* read_next(char* p) {
    return p+1;
}

char* string_new(const char* str, size_t len) {
    char* dst = (char*)malloc(sizeof(char)*len+1);
    memset(dst, '\0', len+1);
    memcpy(dst, str, len);
    return dst;
}

char* add_token(List* l, const char* p, size_t len) {
    char* str = string_new(p, len);
    list_append(l, (char*)str);
    printf("add token: %s\n", str);
    return (char*)(p + len);
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

char* skip_spaces(const char* p) {
    char *spaces = " \r\n\t";
    return (char*)(p + strspn(p, spaces));
}

char* skip_comment_line(const char* p) {
    return strchr(p, '\n') + 1;
}

char* skip_comment_range(const char* p) {
    const char* end = "*/";
    return strstr(p, end) + strlen(end);
}

size_t len_symbol(const char* p) {
    return 1 + strspn(p+1, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_");
}

size_t len_number(const char* p) {
    return 1 + strspn(p+1, "exL1234567890.");
}

size_t len_directive(const char* p) {
    return 1 + strspn(p+1, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

size_t len_string(const char* p) {
    size_t ret_len = strcspn(p+1, "\"");
    return 1 + ret_len + 1;
}

/*
    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
 2     !  "  #  $  %  &  '  (  )  *  +  ,  -  .  /
 3  0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ?
 4  @  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O
 5  P  Q  R  S  T  U  V  W  X  Y  Z  [  \  ]  ^  _
 6  `  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o
 7  p  q  r  s  t  u  v  w  x  y  z  {  |  }  ~  
  */
int read_tokens(List* list, const char* p) {
    switch (*p) {
        case '!':
        case '(':
        case ')':
        case ',':
        case ';':
        case '[':
        case ']':
        case '{':
        case '}':
        case '.':
            p = add_token(list, p, 1);
            break;
        case '"':
            p = add_token(list, p, len_string(p));    break;
        case '#':
            p = add_token(list, p, len_directive(p)); break;
        case '%':
        case '&':
        case '\'':
        case '*':
        case '+':
        case '-':
            // *** not impl ***
            p = add_token(list, p, 1);
            break;
        case '/':
            switch (*(p+1)) {
                case '/': p = skip_comment_line(p+2);  break;
                case '*': p = skip_comment_range(p+2); break;
                default:  p = add_token(list, p, 1); break;
            }
            break;
        case ':':
        case '<':
            
        case '=':
        case '>':
        case '?':
        case '\\':
        case '^':
        case '`':
        case '|':
        case '~':
            p = add_token(list, p, 1);
            break;
        case '$':
        case '@':
            // unused
            break;
        case '\0': // end of file
            return 0;
        default:
            if (IS_LETTER(*p)) { // symbol
                p = add_token(list, p, len_symbol(p));
            } else if (IS_DIGIT(*p)) {
                p = add_token(list, p, len_number(p));
            } else {
                return -1;
            }
            break;
    }

    p = skip_spaces(p);
    printf("===rest===\n%s", p);
    return read_tokens(list, p);
}

int lex(char** tokens, const char* source) {
    List* list = list_create();
    int err;

    if (!list) { return -1; }

    err = read_tokens(list, source);
    if (err < 0) {
        fprintf(stderr, "something failed: %d\n", err);
    }
    print_tokens(list);
    list_destroy(list);

    return 0;
}
