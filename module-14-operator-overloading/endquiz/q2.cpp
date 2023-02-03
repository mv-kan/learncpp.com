#include <iostream>

class Average
{
public:
    Average(double Sum = 0, double NumOfNum = 0) : sum{Sum}, numOfNum{NumOfNum}
    {
    }
    Average &operator+=(double num)
    {
        sum += num;
        numOfNum++;
        return *this;
    }
    double getAverage() const
    {
        return sum / numOfNum;
    }
    friend std::ostream &operator<<(std::ostream &out, const Average &ave)
    {
        out << ave.getAverage();
        return out;
    }

private:
    double sum = 0;
    double numOfNum = 0;
};

int main()
{
    Average avg{};

    avg += 4;
    std::cout << avg << '\n'; // 4 / 1 = 4

    avg += 8;
    std::cout << avg << '\n'; // (4 + 8) / 2 = 6

    avg += 24;
    std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

    avg += -10;
    std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

    (avg += 6) += 10;         // 2 calls chained together
    std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

    Average copy{avg};
    std::cout << copy << '\n';

    return 0;
}