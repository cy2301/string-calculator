#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"
#include "./calculator.h"

using std::cout, std::endl, std::cin, std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"Q\",\"q\"\"Quit\", or \"quit\" or ctrl+d to exit" << endl;
    string fullExpression;
    string line;
    string answer;
	cout << ">>  ";
	while (true)
    {
        getline(cin, fullExpression);
        if (fullExpression == "Q" || fullExpression == "q" || fullExpression == "Quit" || fullExpression == "quit")
            break;
        else if (fullExpression == "")
            continue;
        else
        {
            fullExpression = standardize(fullExpression);
            if (!validate(fullExpression))
            {
                cout << "Invalid expression. Try again: \n>>  ";
                continue;
            }
            fullExpression = postfix(fullExpression);
            try 
            {
                answer = calculate(fullExpression);
            }
            catch (const std::exception& error) 
            {
                cout << error.what() << " Try again: \n>>  ";
                continue;
            }
            cout << "ans =" << endl << endl;
            cout << "    " << answer << endl << endl;
            cout << ">>  ";
        }
    }
	cout << endl;
	cout << "farvel!" << endl;
	cout << endl;
}

