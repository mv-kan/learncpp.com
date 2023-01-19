#include <iostream>
#include <array>

#include <ctime>   // for time()
#include <cstdlib> // for rand() and srand()

class Monster
{

public:
    enum class Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        max_monter_types
    };
    static std::string_view typeToString(Type type)
    {
        constexpr std::array monsters{"Dragon", "Goblin", "Ogre", "Orc", "Skeleton", "Troll", "Vampire", "Zombie"};
        return monsters[static_cast<size_t>(type)];
    }

private:
    Type m_type{};
    std::string m_name{};
    std::string m_roar{};
    int m_hitPoints{};

public:
    Monster(Type type, const std::string &name, const std::string &roar, int hitPoints) : m_type{type}, m_name{name}, m_roar{roar}, m_hitPoints{hitPoints}
    {
    }

    void print()
    {

        printf("%s the %s has %d hit points and says %s\n", m_name.c_str(), typeToString(m_type).data(), m_hitPoints, m_roar.c_str());
    }
};

class MonsterGenerator
{
    // Generate a random number between min and max (inclusive)
    // Assumes srand() has already been called
    static int getRandomNumber(int min, int max)
    {
        static constexpr double fraction{1.0 / (static_cast<double>(RAND_MAX) + 1.0)}; // static used for efficiency, so we only calculate this value once
        // evenly distribute the random number across our range
        return static_cast<int>(std::rand() * fraction * (max - min + 1) + min);
    }

public:
    static Monster generateMonster()
    {
        Monster::Type type = static_cast<Monster::Type>(getRandomNumber(0, static_cast<int>(Monster::Type::max_monter_types) - 1));
        int hitPoints = getRandomNumber(1, 100);
        // If your compiler is not C++17 capable, use std::array<const char*, 6> instead.
        static constexpr std::array s_names{"Blarg", "Moog", "Pksh", "Tyrn", "Mort", "Hans"};
        static constexpr std::array s_roars{"*ROAR*", "*peep*", "*squeal*", "*whine*", "*hum*", "*burp*"};

        // Without the cast, compilers with a high warning level complain about
        // an implicit cast from a signed to an unsigned integer.
        auto name{s_names[getRandomNumber(0, static_cast<int>(s_names.size() - 1))]};
        auto roar{s_roars[getRandomNumber(0, static_cast<int>(s_roars.size() - 1))]};

        return Monster(type, name, roar, hitPoints);
    }
};

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock

    Monster m{MonsterGenerator::generateMonster()};
    m.print();

    return 0;
}