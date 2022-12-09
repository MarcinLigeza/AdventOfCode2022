#include <iostream>
#include <stack>
#include <algorithm>
#include <sstream>

#include "../utils.h"

using namespace std;

class Crate
{
public:
    Crate(char _name) : name(_name) {};
    char get_name() { return name; }

private:
    char name;
};

class Warehouse
{
public:
    Warehouse(int number_of_stacks)
    {
        stacks.resize(number_of_stacks);
    }

    void set_element(Crate crate, int stack)
    {
        stacks[stack-1].push(crate);
    }

    void move_element(int from_stack, int to_stack)
    {
        auto tmp = stacks[from_stack-1].top();
        stacks[from_stack-1].pop();
        stacks[to_stack-1].push(tmp);
    }

    void make_move(int how_many, int from, int to)
    {
        for (int i = 0; i < how_many; ++i)
        {
            move_element(from, to);
        }
    }

    void move_element(stack<Crate>& from, stack<Crate>& to)
    {
        auto tmp = from.top();
        from.pop();
        to.push(tmp);
    }

    void make_move_9001(int how_many, int from, int to)
    {
        for(auto i = 0; i < how_many; ++i)
        {
            move_element(stacks[from-1], helper_stack);
        }
        
        for(auto i = 0; i < how_many; ++i)
        {
            move_element(helper_stack, stacks[to-1]);
        }
    }

    void first_crate_on_stacks()
    {
        for(auto & s : stacks)
        {
            cout << s.top().get_name();
        }
        cout << endl;
    }

private:
    vector<stack<Crate>> stacks;

    stack<Crate> helper_stack;
};

class WarehouseBuilder
{
public:
    WarehouseBuilder(const std::vector<std::string> _structure) : 
        structure(_structure)
    {

    }

    Warehouse build_warehouse()
    {
        auto last_line = structure.back();
        int stacks_number =  std::stoi(last_line.substr(last_line.find_last_of(' ', last_line.length()-2)));

        Warehouse warehouse(stacks_number);

        for(auto line = structure.end()-2; line >= structure.begin(); --line)
        {
            for (auto i = 0; i < stacks_number; ++i)
            {
                char current = (*line)[1+i*4];
                if(current != ' ')
                {
                    warehouse.set_element(Crate(current), i+1);
                }
            }
        }

        return warehouse;
    }

private:
    std::vector<std::string> structure;
};

std::vector<int> parse_move(const std::string &line)
{
    std::vector<int> result(3,0);
    std::stringstream ss(line);

    string tmp;
    ss >> tmp >> result[0] >> tmp >> result[1] >> tmp >> result[2];

    cout << result[0] << ' ' << result[1] << ' ' << result[2] << endl;

    return result;
}

int main()
{
    auto data = load_data("data.txt");

    auto empty_line_iterator = std::find_if(data.begin(), data.end(), [](std::string s) {return s.empty();});

    std::vector<std::string> warehouse_structure = std::vector<std::string>(data.begin(), empty_line_iterator);
    std::vector<std::string> moves = std::vector<std::string>(empty_line_iterator+1, data.end());

    WarehouseBuilder builder(warehouse_structure);
    auto warehouse = builder.build_warehouse();

    for(const auto & line : moves)
    {
        auto move = parse_move(line);
        warehouse.make_move_9001(move[0], move[1], move[2]);
    }

    warehouse.first_crate_on_stacks();
}