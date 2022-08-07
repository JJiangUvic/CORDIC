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
    return (mode == ARCTAN) ? (y<0 ? 1:0):(angle>0 ? 1:0);

}