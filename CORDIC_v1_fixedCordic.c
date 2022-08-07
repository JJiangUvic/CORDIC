#include <stdio.h>
#include <stdlib.h>

//global variable
int list_size = 16; // Size of the check list
int SHIFTBITS = 12; // 12bits magnitude
int CONSTANT = 2487; // constant for calculate the output (0.6072529351031395 Fixed)
double FIXEDBASE = 4096.0; // 2^12

// Check List
int arctan_angle[] = {
    184320, // 45.0
    108810, // 26.56505117707799
    57492,  // 14.036243467926479
    29184,  // 7.125016348901798
    14648,  // 3.576334374997351
    7331,   // 1.7899106082460694
    3666,   // 0.8951737102110744
    1833,   // 0.4476141708605531
    916,    // 0.22381050036853808
    458,    // 0.1119056770662069
    229,    // 0.055952891893803675
    114,    // 0.027976452617003676
    57,     // 0.013988227142265016
    28,     // 0.006994113675352919
    14,     // 0.003497056850704011
    7,      // 0.0017485284269804495
};

// Define a data type to indicate the mode of the CORDIC function
typedef enum MODE
{
    COS,
    SIN,
    ARCTAN
} MODE;


// covert float to fixed
int float_to_fixed(double flt)
{
    return (int)(flt * FIXEDBASE);
}

// convert fixed to float
double fixed_to_float(int fixed)
{
    return fixed / FIXEDBASE;
}

// based on the mode indicator, and the value of y or theta to make the decision tree
int ModeDecision(MODE mode, int y, int angle)
{
    if (mode == ARCTAN && y < 0)
        return 1;
    else if (mode != ARCTAN && angle > 0)
        return 1;
    else // Rotation mode and y>0 or Vector mode and angle<0
        return 0;
}

/*
    CORDIC
    Input double x,y, theta, and mode
    Step 1: convert the double x,y to 12 bits Fixed-point number
    Step 2: Calculate the output
    Step 3: Choose the output value based on the mode
    Step 4: Convert the fixed-point output into float(double)
*/
double cordic(double x, double y, double angle, MODE mode)
{
    int temp_a, temp_b, a, b, result;
    int theta = float_to_fixed(angle);

    a = float_to_fixed(x);
    b = float_to_fixed(y);
    int i = 0;
    for (; i < list_size; i++)
    {
        if (ModeDecision(mode, b, theta))
        {
            temp_a = a - (b >> i);
            temp_b = b + (a >> i);
            theta = theta - arctan_angle[i];
        }
        else
        {
            temp_a = a + (b >> i);
            temp_b = b - (a >> i);
            theta = theta + arctan_angle[i];
        }
        a = temp_a;
        b = temp_b;
    }

    if (mode == SIN)
        result = (b * CONSTANT) >> SHIFTBITS;

    else if (mode == COS)
        result = (a * CONSTANT) >> SHIFTBITS;

    else
        result = theta;

    return fixed_to_float(result);
}

int main(int argc, char const *argv[])
{
    // test values
    double test_sin = cordic(1, 0, 70, SIN);
    printf("sin 70 = %f\n", test_sin);

    double test_cos = cordic(1, 0, 70, COS);
    printf("cos 70 = %f\n", test_cos);

    double test_acrtan = cordic(4, 5, 0, ARCTAN);
    printf("arctan 5/4 = %f\n", test_acrtan);

    return 0;
}