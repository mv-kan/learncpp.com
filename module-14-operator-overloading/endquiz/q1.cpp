#include <iostream>

class Point
{
public:
    Point(int x = 0, int y = 0) : m_x{x}, m_y{y}
    {
    }
    Point operator+(const Point &that);

    Point operator-();

    friend std::ostream &operator<<(std::ostream &out, const Point &p);

private:
    int m_x;
    int m_y;
};
std::ostream &operator<<(std::ostream &out, const Point &p)
{
    out << "<" << p.m_x << " " << p.m_y << ">";
    return out;
}

Point Point::operator-()
{
    return Point{-m_x, -m_y};
}

Point Point::operator+(const Point &that)
{
    return Point{m_x + that.m_x, m_y + that.m_y};
}

int main()
{
    using std::cout;
    Point p1{10, 10};
    Point p2{5, 5};

    cout << p1 << std::endl;
    cout << p2 << std::endl;
    cout << p1 + p2 << std::endl;
    cout << -p1 << std::endl;
    p1 = 5;
    cout << p1 << std::endl;
    cout << p2 << std::endl;
    return 0;
}