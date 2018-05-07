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

char* skip_line(const char* p) {
    return strchr(p, '\n') + 1;
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

size_t len_string(const char* p) {
    size_t ret_len = strcspn(p+1, "\""); // TODO: not concerned \" and error
    return 1 + ret_len + 1;
}

size_t len_char(const char* p) {
    size_t ret_len = strcspn(p+1, "'"); // TODO: not concerned \' and error
    return 1 + ret_len + 1;
}

/* punctuators
[ ] ( ) { } . ->
++ -- & * + - ~ !
/ % << >> < > <= >= == != ^ | && || ? : ; ...
= *= /= %= += -= <<= >>= &= ^= |=
, # ##
<: :> <% %> %: %:%:
*/
size_t len_punctuator_check(const char* p, char** punc, size_t arrsize) {//, size_t cmpsize) {
    size_t cmpsize = strlen(punc[0]);

    for (int i=0; i < arrsize; i++, punc++) {
        if (strncmp(*punc, p, cmpsize) == 0) {
            return cmpsize;
        }
    }
    return 0;
}

#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

size_t len_punctuator(const char* p) {
    char* len_four[]  = { "%:%:" };
    char* len_three[] = { "...", "<<=", ">>=" };
    char* len_two[]   = { "->", "++", "--", "<<", ">>",
                          "<=", ">=", "==", "!=", "&&",
                          "||", "*=", "/=", "%=", "+=", 
                          "-=", "&=", "^=", "|=", "##",
                          "<:", ":>", "<%", "%>", "%:"};
    char* len_one     = "[](){}.&*+-~!/%<>^|?:;=,#";

    // TODO: dasai
    if (len_punctuator_check(p, len_four, ARRAYSIZE(len_four)) > 0) {
        return 4;
    } else if (len_punctuator_check(p, len_three, ARRAYSIZE(len_three)) > 0) {
        return 3;
    } else if (len_punctuator_check(p, len_two, ARRAYSIZE(len_two)) > 0) {
        return 2;
    } else if (strchr(len_one, *p)) {
        return 1;
    } else {
        return 0;
    }
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
// TODO: fix infinite loop when len_* returns 0

int read_tokens(List* tkn, List* drct, const char* p) {
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
        case '%':
        case '&':
        case '*':
        case '+':
        case '-':
        case ':':
        case '<':
        case '=':
        case '>':
        case '?':
        case '^':
        case '|':
        case '~':
            p = add_token(tkn, p, len_punctuator(p)); break;
        case '\'':
            p = add_token(tkn, p, len_char(p));    break;
        case '"':
            p = add_token(tkn, p, len_string(p));    break;
        case '#':
            // TODO: 
            // when arrived here, i think that leaked preprocessing directives out
            p = skip_line(p+1); break;
        case '/':
            switch (*(p+1)) {
                case '/': p = skip_comment_line(p+2);  break;
                case '*': p = skip_comment_range(p+2); break;
                default:  p = add_token(tkn, p, len_punctuator(p)); break;
            }
            break;
        case '\\':
        case '`':
        case '$':
        case '@':
            // unused error
            return -1;
        case '\0': // end of file
            return 0;
        case '_':
        default:
            if (IS_LETTER(*p) || *p == '_') { // symbol
                p = add_token(tkn, p, len_symbol(p));
            } else if (IS_DIGIT(*p)) {
                p = add_token(tkn, p, len_number(p));
            } else {
                return -1;
            }
            break;
    }

    p = skip_spaces(p);
    printf("===rest===\n%s", p);
    return read_tokens(tkn, drct, p);
}

int lex(List* tokens, List* directives, const char* source) {
    int err;

    if (!tokens || !directives) { return -1; }

    err = read_tokens(tokens, directives, source);
    if (err < 0) {
        fprintf(stderr, "something failed: %d\n", err);
    }
    print_tokens(tokens);
    print_tokens(directives);

    return 0;
}
