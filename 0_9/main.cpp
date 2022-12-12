#include <iostream>
#include <set>

#include "../utils.h"

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void move_head(pair<int, int>& head_position, char direction)
{
    switch (direction)
    {
    case 'U':
        ++head_position.second;
        break;
    case 'D':
        --head_position.second;
        break;
    case 'R':
        ++head_position.first;
        break;
    case 'L':
        --head_position.first;
        break;
    default:
        cout << "ERROR: unknown direction: " << direction << endl;
        break;
    }
}

void move_tail(pair<int, int> & tail, const pair<int, int> head)
{
    int diff_x = head.first - tail.first;
    int diff_y = head.second - tail.second;

    if(abs(diff_x) > 1)
    {
        tail.first += sgn(diff_x);
        if (diff_y != 0)
        {
            tail.second += sgn(diff_y);
        }
    }
    else if (abs(diff_y) > 1)
    {
        tail.second += sgn(diff_y);
        if (diff_x != 0)
        {
            tail.first += sgn(diff_x);
        }                
    }
}

int main()
{
    auto data = load_data("data.txt");

    set<pair<int, int>> visited_cooridnates;

    pair<int, int> head_pos(0,0);
    vector<pair<int,int>> knots(9, {0,0});
    pair<int, int> & tail_pos = knots[8];

    for(const auto & line : data)
    {
        auto direction = line[0];
        uint steps = stoi(line.substr(2));

        for(auto i = 0; i < steps; ++i)
        {
            move_head(head_pos, direction);
            move_tail(knots[0], head_pos);
            for(auto i = 1; i < 9; ++i)
            {
                move_tail(knots[i], knots[i-1]);
            }

            // move_tail(tail_pos, head_pos);
            visited_cooridnates.emplace(tail_pos);
        }
    }

    cout << visited_cooridnates.size() << endl;
}