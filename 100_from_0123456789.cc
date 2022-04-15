#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <vector>
using namespace std;

const int NUMBER_OF_EXPRESSIONS = 2 * 3 * 3 * 3 * 3 * 3 * 3 * 3 * 3;
const int NUMBER_OF_DIGITS = 9;

class Expression {
private:
    enum Op { ADD, SUB, JOIN };
    vector<int> code;
public:
    Expression() : code(NUMBER_OF_DIGITS, ADD){
    }
    Expression& operator++(int) {
        for (int i = 0; i < NUMBER_OF_DIGITS; i++)
            if (++code[i] > JOIN) code[i] = ADD;
            else break;
        return *this;
    }
    operator int() const {
        int value = 0, number = 0, sign = (+1);
        for (int digit = 1; digit <= 9; digit++)
            switch (code[NUMBER_OF_DIGITS - digit]) {
            case ADD: value += sign * number; number = digit; sign = (+1); break;
            case SUB: value += sign * number; number = digit; sign = (-1); break;
            case JOIN:                      number = 10 * number + digit;  break;
            }
        return value + sign * number;
    }
    operator string() const {
        string s;
        for (int digit = 1; digit <= NUMBER_OF_DIGITS; digit++) {
            switch (code[NUMBER_OF_DIGITS - digit]) {
            case ADD: if (digit > 1) s.push_back('+'); break;
            case SUB:                  s.push_back('-'); break;
            }
            s.push_back('0' + digit);
        }
        return s;
    }
};


ostream& operator<< (ostream& os, Expression& ex) {
    ios::fmtflags oldFlags(os.flags());
    os << setw(9) << right << static_cast<int>(ex) << " = "
        << setw(0) << left << static_cast<string>(ex) << endl;
    os.flags(oldFlags);
    return os;
}

struct Stat {
    map<int, int> countSum;
    map<int, set<int> > sumCount;
    Stat() {
        Expression expression;
        for (int i = 0; i < NUMBER_OF_EXPRESSIONS; i++, expression++)
            countSum[expression]++;
        for (auto it = countSum.begin(); it != countSum.end(); it++)
            sumCount[it->second].insert(it->first);
    }
};

void print(int givenSum) {
    Expression expression;
    for (int i = 0; i < NUMBER_OF_EXPRESSIONS; i++, expression++)
        if (expression == givenSum)
            cout << expression;
}

int main() {
    Stat stat;

    cout << endl << "Show all solutions that sum to 100" << endl << endl;
    const int givenSum = 100;
    print(givenSum);

    return 0;
}
