#include <iostream>
namespace monster {
    enum MonsterType {
        orc,
        goblin,
        troll,
        ogre,
        skeleton
    };
}

int main() 
{
    monster::MonsterType monsterType {static_cast<monster::MonsterType>(10)};
    std::cout << monsterType << std::endl;
}