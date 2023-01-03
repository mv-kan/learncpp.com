#include <iostream>
#include <array>
#include <random>
#include <algorithm>
#include <vector>
namespace coolinput
{
// include in namespace is TERRIBLE idea
// do not repeat
#include <iostream>
#include <limits>
    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    template <typename T>
    T *getInput()
    {
        T obj{};
        T *result{nullptr};
        std::cin >> obj;
        if (!std::cin)
        {
            std::cin.clear();
            ignoreLine();
            return result;
        }
        else
        {
            ignoreLine();
            // QUESTION: this is messed up, earlier I just saved address of obj to result
            // IT WORKED!!! but it shouldn't.
            result = new T{obj};
            return result;
        }
    }

    template <>
    std::string *getInput()
    {
        std::string obj{};
        std::string *result{nullptr};
        std::getline(std::cin >> std::ws, obj);
        if (!std::cin)
        {
            std::cin.clear();
            return result;
        }
        else
        {
            result = new std::string{obj};
            return result;
        }
    }

    template <typename T>
    T pleaseEnter(std::string_view message)
    {
        while (true)
        {
            std::cout << message;
            T *result{getInput<T>()};

            if (result != nullptr)
            {
                // convert dynamic to static
                T staticResult{*result};
                // QUESTION: is it like viable solution, or bad practice?
                delete result;
                return staticResult;
            }
        }
    }
}

namespace card
{
    enum class Rank
    {
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
    enum class Suit
    {
        clubs,
        diamonds,
        hearts,
        spades,
        numOfSuits
    };

    char toLetterCode(Suit s)
    {
        switch (s)
        {
        case Suit::clubs:
            return 'C';
            break;
        case Suit::diamonds:
            return 'D';
            break;
        case Suit::hearts:
            return 'H';
            break;
        case Suit::spades:
            return 'S';
            break;
        default:
            return '?';
            break;
        }
    };
    char toLetterCode(Rank r)
    {
        constexpr int asciiDigOffset{48};
        constexpr int enumOffset{2};
        switch (r)
        {
        case Rank::c2:
        case Rank::c3:
        case Rank::c4:
        case Rank::c5:
        case Rank::c6:
        case Rank::c7:
        case Rank::c8:
        case Rank::c9:
            return static_cast<char>(asciiDigOffset + static_cast<int>(r) + enumOffset);
            break;
        case Rank::c10:
            return 'T';
            break;
        case Rank::jack:
            return 'R';
            break;
        case Rank::queen:
            return 'Q';
            break;
        case Rank::king:
            return 'K';
            break;
        case Rank::ace:
            return 'A';
            break;
        default:
            return '?';
            break;
        }
    };

    struct Card
    {
        Rank rank{};
        Suit suit{};
    };
    void printCard(const Card &c)
    {
        std::cout << toLetterCode(c.rank) << toLetterCode(c.suit);
    };
    using Deck = std::array<Card, 52>;
    Deck createDeck()
    {
        std::array<Card, 52> deck;
        size_t i{};
        // create all suits
        for (size_t suit = 0; suit < static_cast<size_t>(Suit::numOfSuits); suit++)
        {
            // create all ranks
            for (size_t rank = 0; rank < static_cast<size_t>(Rank::numOfRanks); rank++)
            {
                Card &card{deck.at(i)};
                i++;
                card.rank = static_cast<Rank>(rank);
                card.suit = static_cast<Suit>(suit);
            }
        }
        return deck;
    };
    void printDeck(const Deck &deck)
    {
        for (const Card &card : deck)
        {
            printCard(card);
            std::cout << " ";
        }
        std::cout << std::endl;
    }

    void shuffleDeck(Deck &deck)
    {
        static std::random_device rd;
        static std::mt19937 mt(rd());

        std::shuffle(deck.begin(), deck.end(), mt);
    }

    int getCardValue(Card card)
    {
        switch (card.rank)
        {
        case Rank::c2:
            return 2;
            break;
        case Rank::c3:
            return 3;
            break;
        case Rank::c4:
            return 4;
            break;
        case Rank::c5:
            return 5;
            break;
        case Rank::c6:
            return 6;
            break;
        case Rank::c7:
            return 7;
            break;
        case Rank::c8:
            return 8;
            break;
        case Rank::c9:
            return 9;
            break;
        case Rank::c10:
        case Rank::jack:
        case Rank::queen:
        case Rank::king:
            return 10;
            break;
        case Rank::ace:
            return 11;
            break;
        default:
            return -1;
            break;
        }
    }

    std::string getCardCode(Card card) {
        std::string result{};
        result += toLetterCode(card.rank);
        result += toLetterCode(card.suit);
        return result;
    }

}

namespace blackjack
{
    using Hand = std::vector<card::Card>;
    constexpr int scoreToWin{21};
    constexpr int dealerRiskThreshold{17};

    // changing top card index we can "cut off" cards in array
    // user manages top card index in shuffled deck
    // example: giveTopCardToHand(playersHand, shuffledDeck, topCardIndex++);
    void giveTopCardToHand(Hand& hand,const card::Deck& deck, size_t topCardIndex) {
        hand.push_back(deck.at(topCardIndex));
    }

    int getScore(const Hand& hand) {
        int score{};
        // ace can be 11 or 1 depending on what is the best option
        constexpr int aceLowestScore{1};
        constexpr int aceHighestScore{11};
        int numOfAces{};
        for (const card::Card& card : hand) {
            if (card.rank == card::Rank::ace) {
                numOfAces++;
            } else {
                score += card::getCardValue(card);
            }
        }
        for (int i = 0; i < numOfAces; i++) {
            if (score + aceHighestScore > scoreToWin) {
                score += aceLowestScore;
            } else {
                score += aceHighestScore;
            }
        }
        return score;
    }

    std::string getStringHand(const Hand& hand) {
        std::string result{};
        for (card::Card card : hand) {
            result += card::getCardCode(card) + " ";
        }
        return result;
    }

    

    void showGameStats(const Hand& player,const Hand& dealer) {
        std::cout << "Player's hand: " << getStringHand(player) << "\n\tscore: " << getScore(player) << std::endl;
        std::cout << "Dealer's hand: " << getStringHand(dealer) << "\n\tscore: " << getScore(dealer) << std::endl;
    }

    // int states:
    // -1 dealer wins
    // 0 stalemate
    // 1 player wins
    // it would be better to use enum for this. Ye my bad.
    int play(card::Deck deck)
    {
        
        // begin
        // player's hand
        Hand player;
        // dealer's hand
        Hand dealer;

        // top card in the deck
        size_t topCard{};

        // dealer gets one card
        giveTopCardToHand(dealer, deck, topCard++);

        // player gets two
        giveTopCardToHand(player, deck, topCard++);
        giveTopCardToHand(player, deck, topCard++);
        
        // player can hit or stand
        // players turn
        char input{};
        while (input != 's') {
            std::cout << "Your hand: " << getStringHand(player) << std::endl;
            input = coolinput::pleaseEnter<char>(std::to_string(getScore(player)) + " is your current score. hit or stand? (h/s): ");
            // if hit we add to player another card from deck
            if (input == 'h') {
                giveTopCardToHand(player, deck, topCard++);
            }
        }
        // if stand score for player is calculated
        int playerScore{getScore(player)};
        // if players score is higher than 21, he loses immediately
        if (playerScore > scoreToWin) {
            showGameStats(player, dealer);
            return -1;
        }
        
        // after that dealer comes in
        // dealer takes cards until score higher or equal 17
        int dealerScore{getScore(dealer)};
        while (dealerScore < dealerRiskThreshold) {
            giveTopCardToHand(dealer, deck, topCard++);
            // update score 
            dealerScore = getScore(dealer);
        }
        // if dealer more than 21 he loses immediately

        if (dealerScore > scoreToWin) {
            showGameStats(player, dealer);
            return 1;
        }

        // compare scores, whoever has higher score wins. Tie means win for dealer
        // return true if player wins, false if dealer wins
        showGameStats(player, dealer);
        if (playerScore == dealerScore) 
            return 0;
        else 
            return (playerScore > dealerScore) ? 1 : -1;
    }
}

int playBlackjack() {
    auto deck = card::createDeck();
    card::shuffleDeck(deck);

    return blackjack::play(deck);
}

int playBlackjackAceStart() {
    auto deck = card::createDeck();
    card::shuffleDeck(deck);

    deck.at(0) = card::Card{card::Rank::ace, card::Suit::clubs};
    deck.at(1) = card::Card{card::Rank::ace, card::Suit::clubs};
    deck.at(2) = card::Card{card::Rank::ace, card::Suit::clubs};

    return blackjack::play(deck);
}

int main()
{
    switch (playBlackjackAceStart())
    {
    case 1:
        std::cout << "You WON!!!" << std::endl;
        break;
    case 0:
        std::cout << "IT'S TIE!!!" << std::endl;
        break;    
    case -1:
        std::cout << "You LOSE!!!" << std::endl;
        break;
    default:
        break;
    }
}