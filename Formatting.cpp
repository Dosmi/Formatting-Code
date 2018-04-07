/*
    Formatting
    by Domantas Dilys
    done for programming lessons 'Informikas'
    2016

*/
#include<iostream>
#include<fstream> // Input from a file
#include<iomanip> // Input from a file
#include<cmath>
#include <string.h>
#include <cstdlib>
using namespace std;

// Global variables

const char FD[] = "Code.txt"; // Initial input file variable
const char FR[] = "Output.txt"; // Output file variable



void ReplaceSpaces(string &s)
{
    int position = s.find_first_not_of(" \t"); // finds first position of no longer the escape sequence for a tab
    s.erase(0, position);

    position = s.find_last_not_of(" \t");
    if (position != -1)
        s.erase(position+1);
}

string ReadCode()
{
    // function to read the input
    ifstream File(FD);
    string code = "";
    string eilute;

    while (getline(File, eilute))
    {
        ReplaceSpaces(eilute);
        code += eilute + "\n";
    }
    File.close();
    return code;
}


void Output(string code)
{
    ofstream Output (FR);

    Output << code;

    Output.close();
}

void MoveParenthesis (string &code)
{   // function that moves parenthesis to different lines
    int position;

    position = code.find_first_of("{}");
    while (position != -1)
    {
        if (code[position-1] != '\n')
        {
            code.insert(position,"\n");
            position = position + 2;
        }
        else
        position = position + 1;
        if (code[position] != '\n')
        {
            code.insert(position,"\n");
            position++;
        }

        position = code.find_first_of("{}",position+1);
    }
}

void MoveRows(string &code)
{   // function to indent code where appropriate
    int position = 0;
    int spaceIndicator = 0;

    while (position != -1)
    {
        if (position != 0) position++;
        if (code[position] == '}') spaceIndicator--;
        code.insert(position,spaceIndicator*4,' ');
        position = position + spaceIndicator*4;
        if (code[position] == '{') spaceIndicator++;
        position = code.find_first_of("\n",position);
    }
}

// Main function
int main()
{
    string code;

    code = ReadCode();
    MoveParenthesis (code);
    MoveRows(code);
    Output (code);

    return 0;
}
