#include <iostream>
#include <sstream>
#include <algorithm>

#include "../utils.h"

using namespace std;

bool does_contain(std::pair<int, int> first_region, 
                  std::pair<int, int> second_region)
{
    if(first_region.first <= second_region.first)
    {
        if(first_region.second >= second_region.second)
        {
            return true;
        }
    }
    return false;
}

bool does_overlap(std::pair<int, int> first_region, 
                  std::pair<int, int> second_region)
{    
    if (first_region.second < second_region.first)
    {
        return false;
    }
    else if (first_region.first > second_region.second)
    {
        return false;
    }
    return true;
}


int main()
{
    auto data = load_data("data.txt");

    uint result{0};
    uint result2{0};

    for (const auto & line : data)
    {

        std::stringstream ss(line);
        char tmp;

        std::pair<int, int> first_region;
        std::pair<int, int> second_region;
        ss >> first_region.first;
        ss.get(tmp);
        ss >> first_region.second;
        ss.get(tmp);
        ss >> second_region.first;
        ss.get(tmp);
        ss >> second_region.second;

        // first stage
        if(does_contain(first_region, second_region))
        {
            ++result;
        }
        else if(does_contain(second_region, first_region))
        {
            ++result;
        }

        //second stage
        if (does_overlap(first_region, second_region))
        {
            ++result2;
        }

    }

    cout << result << endl;
    cout << result2 << endl;
}