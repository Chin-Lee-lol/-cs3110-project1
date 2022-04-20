// cs3110 project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>

using namespace std;
string LetterCheck(string input, char check, int size)
{
    int a = input.find(check);
    if (a != -1)
    {
        cout << "\Decimal number cannot contain " << check << " letter\n";
        return "";
    }
    return input;
}
string FloatTypeSuffixChecker(string input, char check, int size)
{
    int f = input.find(check); // simply remove f F d D from the string
    if (f != -1)
        if (f == size - 1) // if f is last char, then cool
            input.erase(f, 1);
        else
        {
            cout << "\nThe " << check << " notation in wrong location\n";
            return ""; // wrong notation
        }
    f = input.find(check); // simply remove f F d D from the string
    if (f != -1)
    {
        cout << "\nThere are multiple " << check << " notation in the string\n";
        return "";
    }
    return input; // cool
}

float StringToFloat(string input, bool hex)
{
    float sum = 0; bool period = false;
    int dot = input.find('.');
    if (dot != -1) // deal with .
    {
        input.erase(dot, 1);
        period = true;
    }
    int dotpos = dot;
    dot = input.find('.');
    if (dot != -1) // if theres one more . in string => nono
    {
        cout << "\nString contains more than one '.'\n";
        return 0;
    }
    int n = input.size() - 1, temp; // to help calculate position
    for (int i = 0; i < input.size(); i++)
    {
        switch (input.at(i)) // assign value corresponsively to the character
        {
        case 'f': case 'F':temp = 15; break;
        case 'e': case 'E':temp = 14; break;
        case 'd': case 'D':temp = 13; break;
        case 'c': case 'C':temp = 12; break;
        case 'b': case 'B':temp = 11; break;
        case 'a': case 'A':temp = 10; break;
        case '9': temp = 9; break;
        case '8': temp = 8; break;
        case '7': temp = 7; break;
        case '6': temp = 6; break;
        case '5': temp = 5; break;
        case '4': temp = 4; break;
        case '3': temp = 3; break;
        case '2': temp = 2; break;
        case '1': temp = 1; break;
        case '0': temp = 0; break;
        default: cout << "\nThe '" << input.at(i) << "' character is not valid\n";
            return 0;
        };
        if (hex) // if it is hexadecimal multiply 16 for position else 10
            sum += temp * pow(16, n);
        else
            sum += temp * pow(10, n);
        n--;
    }
    if (period) // if theres dot, divide according to dot position
        sum /= pow(10, input.length() - dotpos);
    return sum;
}

float FPLConvertor(string input)
{
    bool negative = false;
    float output = 0;
    int n = input.length();
    int underscore = input.find('_');
    while (underscore != -1) // simply remove _ notation
    {
        if (underscore == 0 || underscore == input.length() - 1 ||input.at(underscore - 1) == ('.') || 
            input.at(underscore - 1) == ('e') || input.at(underscore - 1) == ('E') || input.at(underscore - 1) == ('f') || 
            input.at(underscore - 1) == ('F') || input.at(underscore - 1) == ('d') || input.at(underscore - 1) == ('D') || 
            input.at(underscore - 1) == ('e') || input.at(underscore - 1) == ('+') || input.at(underscore - 1) == ('-') ||
            input.at(underscore + 1) == ('.') || input.at(underscore + 1) == ('e') || input.at(underscore - 1) == ('E') ||
            input.at(underscore + 1) == ('f') || input.at(underscore + 1) == ('F') || input.at(underscore + 1) == ('d') ||
            input.at(underscore + 1) == ('D') || input.at(underscore + 1) == ('e') || input.at(underscore + 1) == ('+') ||
            input.at(underscore + 1) == ('-') )
        {
            cout << "\nThe '_' is in invalid position\n";
            return 0;
        }
        input.erase(underscore, 1);
        underscore = input.find('_');
    }
    if (input.at(0) == '-') // check negative sign
    {
        negative = true;
        input.erase(0,1); // remove - sign
    }
    if (input.substr(0, 2).compare("0x") == 0) //check if is hexadecimal
    {
        input.erase(0, 2); // remove 0x from the string
        output = StringToFloat(input, true);
    }
    else // it is not hexadecimal
    {
        bool Echeck = false;
        bool Eneg = false;
        float power = 0;
        input = FloatTypeSuffixChecker(input, 'f', n);
        input = FloatTypeSuffixChecker(input, 'd', n);
        input = FloatTypeSuffixChecker(input, 'D', n);
        input = FloatTypeSuffixChecker(input, 'F', n);
        input = LetterCheck(input, 'a', n);
        input = LetterCheck(input, 'A', n);
        input = LetterCheck(input, 'b', n);
        input = LetterCheck(input, 'B', n);
        input = LetterCheck(input, 'c', n);
        input = LetterCheck(input, 'C', n);
        if (input.compare("") == 0)
            return 0;

        int e = input.find('e'), E = input.find('E'), index; // check if theres e/E notation in string
        if (e != -1 || E != -1)
        {
            string exponent;
            if (e != -1)
                index = e;
            else
                index = E;
            input.erase(index, 1); // remove e/E notation
            if (input.at(index) == '+')
                input.erase(index, 1);
            if (input.at(index) == '-')
            {
                input.erase(index, 1);
                Eneg = true;
            }
            e = input.find('e');
            E = input.find('E');
            if (e != -1 || E != -1) // if theres more than 1 e/E => nono
            {
                cout << "\nThere are more than one e notation in the string\n";
                return 0;
            }
            exponent = input.substr(index, input.size() - index); // store number after e/E in another string
            input.erase(index, input.size() - index); // erase number in exponent part    
            int dot = exponent.find('.');
            if (dot != -1) // if theres a dot in exponential part => nono
            {
                cout << "\nThere is '.' in the exponential part\n";
                return 0;
            }
            power = StringToFloat(exponent, false);
            if (Eneg)
                power *= -1;
        }
        output = StringToFloat(input, false);
        output = output * pow(10, power);
    }
    if (negative)
        output *= -1;
    return output;
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
    return 0;
}
