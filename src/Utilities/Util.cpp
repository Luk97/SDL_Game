#include "Util.h"


int Util::clamp(int val, int min, int max)
{
    if (val < min) val = min;
    if (val > max) val = max;
    return val;
}
