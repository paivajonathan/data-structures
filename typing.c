#include <stdio.h>
#include <stdbool.h>

int main() {
    char c = 'A'; // 1 byte, %c
    unsigned char uc = 'B'; // 1 byte %c

    bool b = true; // 1 byte, %i
    
    short s = 32767; // 2 bytes, %hi
    unsigned short us = 65535; // 2 bytes, %hu
    
    int i = 2147483647; // 4 bytes, %i
    unsigned int ui = 4294967295; // 4 bytes, %u
    float f = 3.141592; // 4 bytes, %f

    long long int lli = 9223372036854775807; // 8 bytes, %lli
    unsigned long long int ulli = 18446744073709551615U; // 8 bytes, %llu
    double d = 3.141592653589793; // 8 bytes, %lf

    char string[] = "Hello World"; // ? bytes, %s

    return 0;
}