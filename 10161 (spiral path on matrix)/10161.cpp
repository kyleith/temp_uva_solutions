#include <cstdio>
#include <iostream>
#include <cmath>

#define ONLINE_JUDGE 1

struct GridCell
{
    GridCell(): m_x(0), m_y(0) {};
    GridCell(const long & x, const long & y): m_x(x), m_y(y) {};
    long m_x, m_y;
};

void processInput ();
void processCase (const long & time);
GridCell findCell (const GridCell & diag, const long & offset);

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    processInput();

    return 0;
}

void processInput ()
{
    long n = -1;

    std::cin >> n;
    while (n != 0)
    {
        processCase(n);
        std::cin >> n;
    }
}

void processCase (const long & currentTime)
{
    long root = ceil(sqrt(currentTime));
    long rootTime = ((root - 1) * (root - 1)) + root;
    long offset = currentTime - rootTime;

    GridCell diagCell(root, root);
    GridCell foundCell = findCell(diagCell, offset);

    std::cout << foundCell.m_x << " " << foundCell.m_y << "\n";
}

GridCell findCell (const GridCell & diag, const long & offset)
{
    GridCell result;
    if (offset == 0)
    {
        result.m_x = diag.m_x;
        result.m_y = diag.m_y;
    }
    else
    {
        bool isOdd = (diag.m_x & 1);
        bool isEven = (!isOdd);
        bool isPositiveOffset = (offset > 0);
        bool isNegativeOffset = (offset < 0);

        bool isLeft = (isOdd && isPositiveOffset)
                    || (isEven && isNegativeOffset);

        bool isBottom  = (isOdd && isNegativeOffset)
                        || (isEven && isPositiveOffset);

        if (isLeft)
        {
            result.m_x = diag.m_x - abs(offset);
            result.m_y = diag.m_y;
        }
        else if (isBottom)
        {
            result.m_x = diag.m_x;
            result.m_y = diag.m_y - abs(offset);
        }
    }

    return result;
}