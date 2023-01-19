#include <iostream>
#include <cmath>
class Point2d
{
    double m_x = 0.0;
    double m_y = 0.0;

public:
    Point2d(double x = 0.0, double y = 0.0) : m_x{x}, m_y{y} {}

    void print() const
    {
        printf("Point2d(%.2lf, %.2lf)\n", m_x, m_y);
    }
    double distanceTo(const Point2d &b) const;
    friend double distanceFrom(const Point2d &, const Point2d &);
};

double Point2d::distanceTo(const Point2d &b) const
{
    return std::sqrt((m_x - b.m_x) * (m_x - b.m_x) + (m_y - b.m_y) * (m_y - b.m_y));
}

double distanceFrom(const Point2d &a, const Point2d &b)
{
    return std::sqrt((a.m_x - b.m_x) * (a.m_x - b.m_x) + (a.m_y - b.m_y) * (a.m_y - b.m_y));
}
int main()
{
    Point2d first{};
    Point2d second{3.0, 4.0};
    first.print();
    second.print();
    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';
    std::cout << "Distance between two points: " << distanceFrom(first, second) << '\n';

    return 0;
}