#include <iostream>
using namespace std;
struct AdStats {
    int shownAd{};
    double percentOfClickedAd{};
    double earnedOnAverage{};
};

void readIn(AdStats& stats) {
    cin >> stats.shownAd;
    cin >> stats.percentOfClickedAd;
    cin >> stats.earnedOnAverage;
};

void printAndCalc(AdStats stats) {
    cout << "Shown ad:\t" << stats.shownAd << endl;
    cout << "Percent clicked:\t" << stats.percentOfClickedAd << endl;
    cout << "earned on average:\t" << stats.earnedOnAverage << endl;
    cout << "earned today:\t" << stats.shownAd * stats.percentOfClickedAd * stats.earnedOnAverage << endl;
};

int main() {
    AdStats stats{};
    cout << "Enter value with spaces (shownad percent onaverage): \n";
    readIn(stats);
    printAndCalc(stats);
    return 0;
}