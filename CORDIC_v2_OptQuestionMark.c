#include <stdio.h>
#include <stdlib.h>

int list_size = 16;
int SHIFTBITS = 12;
int CONSTANT = 2487;       // 0.6072529351031395
double FIXEDBASE = 4096.0; // 2^12

// pre store the arctan value and form a check list
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

// define the indictor for different mode of cordic
typedef enum MODE
{
    COS,
    SIN,
    ARCTAN
} MODE;

// Transfer float to fixed
int floatToFixed(double flt)
{
    return (int)(flt * FIXEDBASE);
}

// Transfer fixed to float
double fixedToFloat(int fixed)
{
    return fixed / FIXEDBASE;
}

// determine the situation based on
int ModeDecision(MODE mode, int y, int angle)
{
    return (mode == ARCTAN) ? (y<0 ? 1:0):(angle>0 ? 1:0);

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
    int temp_a, temp_b, a, b, result, theta;

    theta = floatToFixed(angle);
    a = floatToFixed(x);
    b = floatToFixed(y);
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

    return fixedToFloat(result);
}

int main(int argc, char const *argv[])
{
    double test_sin = cordic(1, 0, 70, SIN);
    printf("sin 70 = %f\n", test_sin);

    double test_cos = cordic(1, 0, 70, COS);
    printf("cos 70 = %f\n", test_cos);

    double test_acrtan = cordic(4, 5, 0, ARCTAN);
    printf("arctan 5/4 = %f\n", test_acrtan);

    return 0;
}