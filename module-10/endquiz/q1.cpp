#include <iostream>
using namespace std;

enum class MonsterType {
    ogre,
    dragon,
    orc,
    giantSpider,
    slime,
};

string_view getString(MonsterType type) {
    using enum MonsterType;
    switch (type)
    {
    case ogre:
        return "Ogre";
        break;
    case dragon:
        return "dragon";
        break;
    case orc:
        return "orc";
        break;
    case giantSpider:
        return "giantSpider";
        break;
    case slime:
        return "slime";
        break;
    default:
        return "undefinedMonster";
        break;
    }
}

struct Monster {
    MonsterType type{};
    int health{};
    string_view name{};
};

void printMonster(Monster monster){
    cout << "This "<< getString(monster.type) << " is named " << monster.name << " and has " << monster.health << " health." << endl;

}

int main() {
    Monster john{MonsterType::dragon, 200, "JohnTheMonster"};
    Monster bob{MonsterType::slime, 2000, "BobTheMonster"};

    printMonster(bob);
    printMonster(john);
}