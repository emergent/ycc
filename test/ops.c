#include <stdio.h>

void add(int* x) {
    *     x = 100;
}

int main() {
    // number
    int x = 1;
    int y = 2;
    int z = x + 7809808;
    x = y/x;
    y = y % z  ;
    y = y - 1;
    z = z - (-1);
    double a = z / 1;
    float b = z / 100L;
    y = 0;
    y = + 1 ;
    printf("y = %d\n", y);
    y  ++;
    printf("y = %d\n", y);
    ++     y;
    printf("y = %d\n", y);
    y   --;
    printf("y = %d\n", y);
    --  y;
    printf("y = %d\n", y);
    y += - - -1;
    printf("y = %d\n", y);
    y = y > 0 ? 5 : 2;
    printf("y = %d\n", y);
    y = y | 1;
    printf("y = %d\n", y);
    y = 7 & y;
    printf("y = %d\n", y);
    

    add( & x);
    printf("x = %d\n", x);

    printf("%f\n", a+b);

    // this is comment
    /* this is
            comment, 
         too. 
     */
    return 0;
}
