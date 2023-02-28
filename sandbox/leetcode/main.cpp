#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s)
{
    vector<int> lengths{};
    lengths.push_back(0);
    size_t current{};
    string seenChars{};
    for (size_t i = 0; i < s.length(); i ++) {
        size_t pos = seenChars.find(s[i]);
        if (pos == string::npos) {
            seenChars.push_back(s[i]);
            lengths[current]++;
        } else {
            if (seenChars[seenChars.length() - 1] == s[i])
                seenChars.push_back(s[i]);
            else 
                i--;
            seenChars.erase(0, pos + 1);
            current++;
            // add this iteration
            lengths.push_back(seenChars.length());
        }
    }
    return *max_element(lengths.begin(), lengths.end());
}

int main() {
    // std::cout << lengthOfLongestSubstring("abcabcba") << std::endl;
    std::cout << lengthOfLongestSubstring("aab") << std::endl;
    // std::cout << lengthOfLongestSubstring("dvdf") << std::endl;
    // std::cout << lengthOfLongestSubstring("pwwkew") << std::endl;
    std::cout << lengthOfLongestSubstring("anviaj") << std::endl;
    std::cout << lengthOfLongestSubstring("wobgrovw") << std::endl;
}