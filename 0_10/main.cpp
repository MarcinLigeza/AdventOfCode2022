#include <iostream>

#include "../utils.h"

using namespace std;

int main()
{
    auto data = load_data("data.txt");

    int x{1};

    auto current_line = data.begin();
    bool busy{false};
    int value_to_add;

    int signal_strengths{0};

    for(int cycle_number = 1; cycle_number <= 240; ++cycle_number)
    {
        auto current_crt_position = (cycle_number-1) % 40;
        if(current_crt_position == 0)
        {
            cout << endl;
        }
        if(abs(x-current_crt_position) <= 1)
        {
            cout << "# ";
        }
        else
        {
            cout << "  ";
        }


        if(((cycle_number - 20) % 40) == 0)
        {
            signal_strengths += (x*cycle_number);
        }

        if(!busy)
        {
            auto operation = current_line->substr(0,4);
            if(operation == "addx")
            {
                value_to_add = stoi(current_line->substr(5));
                busy = true;
            }
            ++current_line;
        }
        else
        {
            busy = false;
            x += value_to_add;
        }
    } 

    cout << signal_strengths << endl;

}