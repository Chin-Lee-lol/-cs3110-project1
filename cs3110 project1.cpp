// cs3110 project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

float FPLConvertor(string input)
{
    bool negative = false;
    float output = 0;
    if (input.at(0) == '-') // check negative sign
    {
        negative = true;
        input.erase(0,1); // remove - sign
    }
    if (input.substr(0, 2).compare("0x") == 0) //check if is hexadecimal
    {
        input.erase(0, 2); // remove 0x from the string
        int n = input.size() - 1, temp; // to help calculate position
        for (int i = 0; i < input.size(); i++)
        {
            switch (input.at(i)) // assign value corresponsively to the character
            {
            case 'f': temp = 15; break;
            case 'e': temp = 14; break;
            case 'd': temp = 13; break;
            case 'c': temp = 12; break;
            case 'b': temp = 11; break;
            case 'a': temp = 10; break;
            default: temp = stoi(input.substr(i, 1));
            };
            output += temp * pow(16, n); // multiply value with 16 power to the position
            n--;
        }
        if (negative)
            output *= -1;
        return output;
    }
    else // it is not hexadecimal
    {
        int e = input.find('e'), E = input.find('E'), index; // check if theres e/E notation in string
        if (e != -1 || E != -1)
        {
            if (e != -1)
                index = e;
            else
                index = E;
            input.erase(index, 1); // remove e/E notation
            e = stoi(input.substr(index, input.size()-1)); // store integer after e/E
            input.erase(index, input.size() - 1); // remove integer after e/E
            output = stof(input) * pow(10,e);
            if (negative)
                output *= -1;
            return output;
        }
        output = stof(input);
        if (negative)
            output *= -1;
        return output;
    }
}

int main()
{
    string input;
    float output;
    while (true)
    {
        cout << "\nPlease enter a floating-point literal number (enter q to quit): ";
        cin >> input; // assume that input is less than or equal 20
        if (input.compare("q") == 0) // terminate input
            break;
        output = FPLConvertor(input);
        cout << "\nThe decimal value is " << output;
        cout << endl;
    }
    cout << "\nProgram terminated\n";
    system("pause");
    return 0;
}
