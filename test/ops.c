#include <stdio.h>
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

    printf("%f\n", a+b);


    // this is comment
    /* this is
            comment, 
         too. 
     */
    return 0;
}
