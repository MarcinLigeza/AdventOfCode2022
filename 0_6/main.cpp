#include <iostream>

#include "../utils.h"

using namespace std;

static const int marker_length = 14;

bool are_unique(std::string::const_iterator b, std::string::const_iterator e)
{
    for (auto it = b; it != e; ++it)
    {
        for(auto jt = it+1; jt<= e; ++jt)
        {
            if (*it == *jt)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    auto data = load_data("data.txt");
    auto line = data[0];

    for(auto i = 0; i < (line.length()-marker_length); ++i)
    {
        if(are_unique(line.begin()+i, line.begin()+i+marker_length-1))
        {
            cout << i+marker_length << endl;
            break;
        }
    }

}