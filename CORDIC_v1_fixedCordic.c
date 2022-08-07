#include <stdio.h>
#include <stdlib.h>

int list_size = 16;
int SHIFTBITS = 12;
int CONSTANT = 2487;
double FIXEDBASE = 4096.0;

int arctan_engle_2[] = {
    184320, //
    108810,
    57492,
    29184,
    14648,
    7331,
    3666,
    1833,
    916,
    458,
    229,
    114,
    57,
    28,
    14,
    7,
};

typedef enum MODE
{
    COS,
    SIN,
    ARCTAN
} MODE;

int float_to_fixed(double flt)
{
    return (int)(flt * FIXEDBASE);
}

double fixed_to_float(int fixed)
{
    return fixed / FIXEDBASE;
}

int ModeDecision(MODE mode, int y, int angle)
{
    if (mode == ARCTAN && y < 0)
        return 1;
    else if (mode != ARCTAN && angle > 0)
        return 1;
    else
        return 0;
}

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
            theta = theta - arctan_engle_2[i];
        }
        else
        {
            temp_a = a + (b >> i);
            temp_b = b - (a >> i);
            theta = theta + arctan_engle_2[i];
        }
        a = temp_a;
        b = temp_b;
    }

    if (mode == SIN)
        result = (b * CONSTANT) >> 12;

    else if (mode == COS)
        result = (a * CONSTANT) >> 12;

    else
        result = theta;

    return fixed_to_float(result);
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