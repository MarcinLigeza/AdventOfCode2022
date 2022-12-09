#include <iostream>
#include <algorithm>

#include "../utils.h"

using namespace std;

char find_first_common_char(const std::string & s1, const std::string & s2)
{
    for(const auto & c1: s1)
    {
        for(const auto & c2 : s2)
        {
            if (c1 == c2)
            {
                return c1;
            }
        }
    }
    return 'a';
}

uint64_t first_stage(vector<string> data)
{
    uint64_t sum {0};

    for(const auto & line : data)
    {
        auto first_half = line.substr(0, line.length()/2);
        auto second_half = line.substr(line.length()/2);
       
        auto c = find_first_common_char(first_half, second_half);

        sum += (std::isupper(c) ? (c - 'A' + 26 + 1) : (c - 'a' + 1));
    }
    return sum;
}

char find_common_char(const std::string & s1,
                      const std::string & s2,
                      const std::string & s3)
{
    for(const auto & c1: s1)
    {
        for(const auto & c2 : s2)
        {
            for(const auto & c3 : s3)
            {
                if (c1 == c2 && c2 == c3)
                {
                    return c1;
                }
            }
        }
    }
    return 'a';    
}

int main()
{
    auto data = load_data("data.txt");

    uint64_t sum {0};

    for (auto it = data.begin(); it < data.end(); it += 3)
    {
        auto c = find_common_char(*it, *(it+1), *(it+2));

        sum += (std::isupper(c) ? (c - 'A' + 26 + 1) : (c - 'a' + 1));        
    }

    cout << sum << endl;
}