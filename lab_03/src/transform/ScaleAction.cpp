#include "ScaleAction.h"
#include "ShiftAction.h"

ScaleAction::ScaleAction(double mx, double my, double mz) : TransformAction()
{
    _matrix[0][0] = mx;
    _matrix[1][1] = my;
    _matrix[2][2] = mz;
    _matrix[3][3] = 1;
}

ScaleAction::ScaleAction(double m)
{
    _matrix[0][0] = m;
    _matrix[1][1] = m;
    _matrix[2][2] = m;
    _matrix[3][3] = 1;
}

ScaleAction::ScaleAction(const Point &center, double mx, double my, double mz) : TransformAction()
{
    ShiftAction toCenter(Point(-center.GetX(), -center.GetY(), -center.GetZ()));
    ScaleAction scale(mx, my, mz);
    ShiftAction fromCenter(center);

    _matrix = fromCenter.GetMatrix() * scale.GetMatrix() * toCenter.GetMatrix();
}

ScaleAction::ScaleAction(const Point &center, double m)
{
    ShiftAction toCenter(Point(-center.GetX(), -center.GetY(), -center.GetZ()));
    _matrix *= toCenter.GetMatrix();
    ScaleAction scale(m);
    _matrix *= scale.GetMatrix();
    ShiftAction fromCenter(center);
    _matrix *= fromCenter.GetMatrix();
}
