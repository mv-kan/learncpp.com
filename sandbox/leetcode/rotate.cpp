#include <iostream>
#include <vector>

using namespace std;

void rotate(vector<int> &nums, int k)
{
    int i{};
    int i_origin{i};
    int prev{nums[0]};
    int tmp{prev};

    for (int i_ = 0; i_ < nums.size(); i_++) {
        if (i + k + 1 > nums.size()) {
            i = (i + k) % nums.size();
        } else {
            i += k;
        }
        tmp = nums[i];
        nums[i] = prev;
        prev = tmp;
        if (i_origin == i && i_ > 0) {
            i++;
            i_origin = i;
            prev = nums[i];
        }
    }
}

int main() {
    // vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    vector<int> v = {1, 2, 3, 4};
    rotate(v, 2);
}