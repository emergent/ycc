#include <stdio.h>
#include <string.h>

/* punctuators
[ ] ( ) { } . ->
++ -- & * + - ~ !
/ % << >> < > <= >= == != ^ | && || ? : ; ...
= *= /= %= += -= <<= >>= &= ^= |=
, # ##
<: :> <% %> %: %:%:
*/
size_t len_punctuator_check(const char* p, char** punc, size_t arrsize) {//, size_t cmpsize) {
    //size_t arrsize = sizeof(punc)/sizeof(punc[0]);
    size_t cmpsize = strlen(punc[0]);

    printf("%zu, %zu\n", arrsize, cmpsize);

    for (int i=0; i < arrsize; i++, punc++) {
        printf("[%02d] %s\n", i, *punc);
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
    char* len_one     = "[](){}.&*+-~!/%<>^|?:;=#";

    printf("%zu, %zu, %zu, %s\n", sizeof(len_four), sizeof(len_four[0]), strlen(len_four[0]), len_four[0]);
    printf("%zu, %zu, %zu, %s\n", sizeof(len_three), sizeof(len_three[0]), strlen(len_three[0]), len_three[0]);
    printf("%zu, %zu, %zu, %s\n", sizeof(len_two), sizeof(len_two[0]), strlen(len_two[0]), len_two[0]);
    
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
    
   return 0;
}

int main() {
    char *a = ">%==CCC";
    printf("%s, %zu\n", a, len_punctuator(a));
    return 0;
}