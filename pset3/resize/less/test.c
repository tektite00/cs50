#include <cs50.h>
#include<stdio.h>
#include <ctype.h>
#include<string.h>


int main (void)
{
    // char* name = "Lloyd";
    // int *val;
    // val = malloc(sizeof(int));
    // *val = 12;
    // printf("val is: %d\n", *val);
    // printf("addres of val is: %p\n", val);
    // int a = 10;
    // printf("created int a, addrs of a is: %p\n", &a);
    // val = &a;
    // printf("addres of val is: %p\n", val);


    // int k;
    // k = 5;
    // int *pk = NULL;
    // pk = &k;
    // *pk = 35;
    // int m;
    // m = 4;
    // pk = &m;
    int m;
    int *a;
    int *b = malloc(sizeof(int));
    a = &m;
    a = b;
    m = 10;
    *b = m + 2;
    free(b);
    *a = 11;



}

