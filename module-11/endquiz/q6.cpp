#include <iostream>
#include <array>
#include <random>
#include <algorithm>
namespace card {
    enum class Rank {
        c2,
        c3,
        c4,
        c5,
        c6,
        c7,
        c8,
        c9,
        c10,
        jack,
        queen,
        king,
        ace,
        numOfRanks
    };
    enum class Suit {
        clubs,
        diamonds,
        hearts,
        spades,
        numOfSuits
    };
    
    char toLetterCode(Suit s) {
        using enum Suit;
        switch (s)
        {
        case clubs:
            return 'C';
            break;
        case diamonds:
            return 'D';
            break;
        case hearts:
            return 'H';
            break;
        case spades:
            return 'S';
            break;
        default:
            return '?';
            break;
        }
    };
    char toLetterCode(Rank r) {
        using enum Rank;
        constexpr int asciiDigOffset{48};
        constexpr int enumOffset{2};
        switch (r)
        {
        case c2:
        case c3:
        case c4:
        case c5:
        case c6:
        case c7:
        case c8:
        case c9:
            return static_cast<char>(asciiDigOffset + static_cast<int>(r) + enumOffset);
            break;
        case c10:
            return 'T';
            break;
        case jack:
            return 'R';
            break;
        case queen:
            return 'Q';
            break;
        case king:
            return 'K';
            break;
        case ace:
            return 'A';
            break;
        default:
            return '?';
            break;
        }
    };
    
    struct Card {
        Rank rank{};
        Suit suit{};
    };
    void printCard(const Card& c) {
        std::cout << toLetterCode(c.rank) << toLetterCode(c.suit);
    };
    using Deck = std::array<Card, 52>;
    Deck createDeck() {
        std::array<Card, 52> deck;
        size_t i{};
        // create all suits
        for (size_t suit = 0; suit < static_cast<size_t>(Suit::numOfSuits); suit++)
        {
            // create all ranks
            for (size_t rank = 0; rank < static_cast<size_t>(Rank::numOfRanks); rank++)
            {
                Card& card{deck.at(i)};
                i++;
                card.rank = static_cast<Rank>(rank);
                card.suit = static_cast<Suit>(suit);
            }
            
        }
        return deck;
    };
    void printDeck(const Deck& deck) {
        for (const Card& card : deck)
        {
            printCard(card);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    

    void shuffleDeck(Deck& deck) {
        static std::random_device rd;
        static std::mt19937 mt(rd());

        std::shuffle(deck.begin(), deck.end(), mt);
    }

    int getCardValue(Card card) {
        using enum Rank;
        switch (card.rank)
        {
        case c2:
            return 2;
            break;
        case c3:
            return 3;
            break;
        case c4:
            return 4;
            break;
        case c5:
            return 5;
            break;
        case c6:
            return 6;
            break;
        case c7:
            return 7;
            break;
        case c8:
            return 8;
            break;
        case c9:
            return 9;
            break;
        case c10:
        case jack:
        case queen:
        case king:
            return 10;
            break;
        case ace:
            return 11;
            break;
        default:
            return -1;
            break;
    }

}

int main() {
    auto deck = card::createDeck();
    card::shuffleDeck(deck);
    card::printDeck(deck);
}