#include <iostream>

class Ball {
    std::string m_color{};
    double m_radius{};
public:
    Ball() = default;
    Ball(std::string_view color = "black", double radius = 10) {
        m_color = color;
        m_radius = radius;
    }
    Ball(double radius) {
        m_radius = radius;
    }
    void print() {
        std::printf("color: %s, radius: %#2f\n", m_color.c_str(), m_radius);
    }
};

int main()
{
	Ball def{};
	def.print();

	Ball blue{ "blue" };
	blue.print();

	Ball twenty{ 20.0 };
	twenty.print();

	Ball blueTwenty{ "blue", 20.0 };
	blueTwenty.print();

	return 0;
}