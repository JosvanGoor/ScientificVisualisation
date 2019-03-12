#include "utility.ih"

inline int bound(int value, size_t gridsize)
{
    if (value < 0)
        return gridsize - value;    
    return value % gridsize;
}

float linterp(double *data, size_t range, size_t gridsize, size_t pivx, size_t pivy)
{
    float value = 0.0f;
    size_t count = 0;

    int col = static_cast<int>(pivx) - range;
    int row = static_cast<int>(pivy) - range;

    int colmax = static_cast<int>(pivx + range);
    int rowmax = static_cast<int>(pivy + range);

    for (; col <= colmax; ++col)
    {
        for (; row <= rowmax; ++row)
        {
            size_t index = (bound(row, gridsize) * gridsize) + bound(col, gridsize);
            value += data[index];
            ++count;
        }
    }

    return value / count;
}