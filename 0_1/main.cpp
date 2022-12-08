#include <iostream>
#include <deque>
#include <algorithm>
#include <numeric>

#include "../utils.h"

using namespace std;

int main()
{
    auto data = load_data("data.txt");

    deque<uint64_t> top3{0ULL, 0ULL, 0ULL};
    uint64_t current{0ULL};

    for (const auto &line : data)
    {
        if (line.empty())
        {
            auto is_greater = [current](uint64_t max)
            {
                return (current > max);
            };

            auto it = find_if(begin(top3), end(top3), is_greater);

            if (it != end(top3))
            {
                top3.insert(it, current);
                top3.pop_back();

                cout << "Inserting new max: " << current << ". Current top 3: " << top3.at(0) << ", " << top3.at(1) << ", " << top3.at(2) << endl;
            }
            current = 0ULL;
        }
        else
        {
            current += stoi(line);
        }
    }

    auto sum = reduce(top3.begin(), top3.end());

    cout << sum << endl;
}