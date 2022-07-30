#include <stdio.h >
void main (void) {
    long int pre_load_val;
    unsigned short int *global_vals;

//    unsigned int *list_size;
//    unsigned int *SHIFTBITS;
//    unsigned int *CONSTANT;
//    unsigned int *FIXEDBASE;

    global_vals =(unsigned short int *)(&pre_load_val);
    pre_load_val=0x09B7000c;
//
//    short *list_size = &global_vals;
//
//    printf ("list_size=%x\n" , list_size );




    printf ("pre_load_val=%x\n" , pre_load_val );
    printf ("global_vals=%d %d\n" , global_vals[0] , global_vals[1]);

//    int a;
//    char *b;
//    b = (unsigned char *)(& a );
//    a = 0x00000000;
//    printf ("a=%08X\n" , a );
//    printf ("b=%dX%dX%dX%d\n" , b [0] , b [1] ,b [2] , b [3]);
}

