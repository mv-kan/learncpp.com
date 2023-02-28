#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int removeDuplicates(vector<int> &nums)
{
    size_t final_size{nums.size()};
    int prev{nums[0]};
    int offset{};
    for (int i = 1; i < final_size; i++)
    {
        if (nums[i] == prev)
        {
            offset++;
        }
        // on last iter also
        // run this if offset bigger than 0 and this num[i] is not prev OR on last iteration
        if ((offset > 0 && nums[i] != prev) || i + 1 == final_size)
        {
            for (int j = i - offset; j < final_size && j + offset < final_size; j++)
            {
                nums[j] = nums[j + offset];
            }
            final_size -= offset;
            i -= offset;
            offset = 0;
        }
        prev = nums[i];
    }
    return final_size;
}

int main() {
    auto v{
        vector<int> { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 }
    };
    std::cout << removeDuplicates(v) << std::endl;
}