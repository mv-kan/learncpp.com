#include <iostream>

class Fruit
{
public:
	// Note: we've moved FruitType inside the class, under the public access specifier
	// We've also changed it from an enum class to an enum
	enum FruitType
	{
		apple,
		banana,
		cherry
	};

private:
	FruitType m_type {};
	int m_percentageEaten { 0 };

public:
	Fruit(FruitType type) :
		m_type { type }
	{
	}

	FruitType getType() const { return m_type; }
	int getPercentageEaten() const { return m_percentageEaten; }
};

int main()
{
	// Note: we access the FruitType via Fruit now
	Fruit apple { Fruit::apple };

	if (apple.getType() == Fruit::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

	return 0;
}