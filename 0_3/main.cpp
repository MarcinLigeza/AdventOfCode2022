#include <iostream>
#include <algorithm>

#include "../utils.h"

using namespace std;

char find_first_common_char(const std::string & s1, const std::string & s2)
{
    for(const auto & c1: s1)
    {
        for(const auto)
    }
}

int main()
{
    auto data = load_data("data.txt");

    for(const auto & line : data)
    {
        auto first_half = line.substr(0, line.length()/2);
        auto second_half = line.substr(line.length()/2);

        std::sort(first_half.begin(), first_half.end());
        std::sort(second_half.begin(), second_half.end());

        std::string result;
        std::set_intersection(first_half.begin(), first_half.end(),
                                second_half.begin(), second_half.end(),
                                std::back_inserter(result));

        std::cout << first_half << " " << second_half << " " <<  result << endl;
    }

}