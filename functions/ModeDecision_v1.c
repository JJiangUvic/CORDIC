#include <stdio.h>
#include <stdlib.h>

typedef enum MODE
{
    COS,
    SIN,
    ARCTAN
} MODE;

int ModeDecision(MODE mode, int y, int angle)
{
    if (mode == ARCTAN && y < 0)
        return 1;
    else if (mode != ARCTAN && angle > 0)
        return 1;
    else // Rotation mode and y>0 or Vector mode and angle<0
        return 0;
}