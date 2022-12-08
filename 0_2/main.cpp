#include <iostream>
#include <map>

#include "../utils.h"

class Round
{
public:
    Round(const std::string &line)
    {
        mOpponentMove = line.at(0);
        mMyMove = line.at(2);
    }

    uint32_t GetResult()
    {
        uint32_t result = mMyMove - 'X' + 1;

        if((mMyMove == 'X' && mOpponentMove == 'C') 
            || (mMyMove == 'Y' && mOpponentMove == 'A') 
            || (mMyMove == 'Z' && mOpponentMove == 'B'))
        {
            result += 6;
        }
        else if((mMyMove == 'X' && mOpponentMove == 'A') 
                || (mMyMove == 'Y' && mOpponentMove == 'B') 
                || (mMyMove == 'Z' && mOpponentMove == 'C'))
        {
            result += 3;
        }

        return result;
    }

private:
    char mOpponentMove;
    char mMyMove;
};


class PredictRound
{
public:
    PredictRound(const std::string & line)
    {
        mOpponentMove = line.at(0);
        mResult = line.at(2);
    }

    uint32_t GetResult()
    {
        uint32_t result = mResult == 'X' ? 0 : mResult == 'Y' ? 3 : 6;

        result += Pair2Result.at(std::make_pair(mOpponentMove, mResult));

        return result;
    }

private:
    char mOpponentMove;
    char mResult;

    const std::map<std::pair<char, char>, int> Pair2Result {
    {{'B', 'Z'}, 3}, {{'C', 'Y'}, 3}, {{'A', 'X'}, 3},
    {{'B', 'Y'}, 2}, {{'C', 'X'}, 2}, {{'A', 'Z'}, 2},
    {{'B', 'X'}, 1}, {{'C', 'Z'}, 1}, {{'A', 'Y'}, 1},
};
};

int main()
{
    auto data = load_data("data.txt");

    uint32_t first_result {0};
    uint32_t second_result {0};

    for(const auto & line : data)
    {
        Round tmp(line);
        PredictRound pr(line);
        first_result += tmp.GetResult();
        second_result += pr.GetResult();
    }

    std::cout << first_result << std::endl;
    std::cout << second_result << std::endl;
}