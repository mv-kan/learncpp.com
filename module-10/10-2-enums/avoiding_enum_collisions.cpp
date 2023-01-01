namespace color
{
    // The names Color, red, blue, and green are defined inside namespace color
    enum Color
    {
        red,
        green,
        blue,
    };
}

namespace feeling
{
    enum Feeling
    {
        happy,
        tired,
        blue, // feeling::blue doesn't collide with color::blue
    };
}

int main()
{
    color::Color paint { color::blue };
    feeling::Feeling me { feeling::blue };

    return 0;
}