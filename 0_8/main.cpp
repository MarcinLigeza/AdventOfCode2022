#include <iostream>

#include "../utils.h"

using namespace std;

bool visible(const vector<string> & data, int x, int y, int value)
{
    bool from_left{true}, from_top{true}, from_right{true}, from_bottom{true};
    for(auto i = 0; i < x; i++)
    {
        if(data[i][y] >= value)
        {
            from_left = false;
            break;
        }
    }

    for(auto i = x+1; i < data.size(); ++i)
    {
        if(data[i][y] >= value)
        {
            from_right = false;
            break;
        }     
    }

    for(auto i = 0; i < y; ++i)
    {
        if(data[x][i] >= value)
        {
            from_top = false;
            break;
        }
    }

    for(auto i = y+1; i < data.at(0).size(); ++i)
    {
        if(data[x][i] >= value)
        {
            from_bottom = false;
            break;
        }        
    }

    return from_top || from_left || from_right || from_bottom;
}

uint64_t calculate_scenic_score(const vector<string> & data, int x, int y)
{
    auto value = data[x][y];

    uint64_t score = 1;

    uint64_t tmp_counter = 0;

    for(auto i = x-1; i >= 0; --i)
    {
        ++tmp_counter;
        if(data[i][y] >= value)
        {
            break;
        }
    }

    score *= tmp_counter;
    tmp_counter = 0;

    for(auto i = x+1; i < data.size(); ++i)
    {
        ++tmp_counter;
        if(data[i][y] >= value)
        {
            break;
        }     
    }

    score *= tmp_counter;
    tmp_counter = 0;

    for(auto i = y-1; i >= 0; --i)
    {
        ++tmp_counter;
        if(data[x][i] >= value)
        {
            break;
        }
    }
    
    score *= tmp_counter;
    tmp_counter = 0;

    for(auto i = y+1; i < data.at(0).size(); ++i)
    {
        ++tmp_counter;
        if(data[x][i] >= value)
        {
            break;
        }        
    }
    
    score *= tmp_counter;

    return score;
}

int main()
{
    const auto data = load_data("data.txt");

    uint32_t result = data.size() * 2 + (data.at(0).size()-2) * 2;

    for(auto x = 1U; x < (data.size()-1); ++x)
    {
        for(auto y = 1U; y < (data.at(0).size()-1); ++y)
        {
            if(visible(data, x, y, (data[x][y])))
            {
                ++result;
            }
        }
    }

    cout << result << endl;


    uint64_t max{0ULL};

    for(auto x = 1U; x < (data.size()-1); ++x)
    {
        for(auto y = 1U; y < (data.at(0).size()-1); ++y)
        {
            auto current_score = calculate_scenic_score(data, x ,y);
            if (max < current_score)
            {
                max = current_score;
            }
        }
    }


    cout << max << endl;


}