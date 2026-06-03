#include "core/ConsoleUI.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;

// Initialize ANSI formatting Colors
const string ConsoleUI::RESET   = "\033[0;0m";
const string ConsoleUI::BOLD    = "\033[1m";
const string ConsoleUI::RED     = "\033[31m";
const string ConsoleUI::GREEN   = "\033[32m";
const string ConsoleUI::YELLOW  = "\033[33m";
const string ConsoleUI::BLUE    = "\033[34m";
const string ConsoleUI::CYAN    = "\033[36m";
const string ConsoleUI::WHITE   = "\033[37m";

// Initialize Configurable UI Colors
int ConsoleUI::HEADER_PADDING = 6;
int ConsoleUI::DIVIDER_LENGTH = 100;
string ConsoleUI::PRIMARY_COLOR = ConsoleUI::BLUE;
string ConsoleUI::SECONDARY_COLOR = ConsoleUI::WHITE;
string ConsoleUI::SUCCESS_COLOR = ConsoleUI::GREEN;
string ConsoleUI::ERROR_COLOR = ConsoleUI::RED;
string ConsoleUI::LABEL_COLOR = ConsoleUI::YELLOW;

void ConsoleUI::clearScreen() { cout << "\033[2J\033[1;1H" << flush; }

void ConsoleUI::printDivider() 
{
    cout << SECONDARY_COLOR;
    for (int i = 0; i < DIVIDER_LENGTH; ++i) { cout << "─"; }
    cout << RESET << endl;
}

void ConsoleUI::printHeader(const string& title) 
{
    int width = DIVIDER_LENGTH;
    
    cout << endl << SECONDARY_COLOR << BOLD;
    
    // Top border
    cout << "┌";
    for (int i = 0; i < width - 2; ++i) cout << "─";
    cout << "┐" << endl;
    
    // Main Project Title 
    string mainTitle = "UNIVERSITY TRANSPORT MANAGEMENT SYSTEM";

    // formula to center text
    int padTitle = (width - 2 - mainTitle.length()) / 2;
    if (padTitle < 0) padTitle = 0;


    cout << "│";
    // pad left side of text
    for (int i = 0; i < padTitle; ++i) cout << " ";
    
    cout << BOLD << PRIMARY_COLOR << mainTitle << RESET << SECONDARY_COLOR << BOLD;

    // pad right side of text
    int titlePrinted = padTitle + mainTitle.length();

    for (int i = 0; i < (width - 2 - titlePrinted); ++i) cout << " ";
    
    cout << "│" << endl;

    // Sub-header Centered (capitalized)
    string sub = title;
    for (auto& c : sub) c = toupper(c);

    int padSub = (width - 2 - sub.length()) / 2;
    if (padSub < 0) padSub = 0;

    
    cout << "│";
    // pad left side of text
    for (int i = 0; i < padSub; ++i) cout << " ";

    cout << RESET << SECONDARY_COLOR << sub << RESET << SECONDARY_COLOR << BOLD;

    // pad right side of text
    int subPrinted = padSub + sub.length();
    for (int i = 0; i < (width - 2 - subPrinted); ++i) cout << " ";
    
    cout << "│" << endl;

    // Bottom border of Header box
    cout << "└";
    for (int i = 0; i < width - 2; ++i) cout << "─";
    cout << "┘" << RESET << endl;
}

void ConsoleUI::pause() 
{
    cout << endl << LABEL_COLOR << "Press any key to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cin.get();
    cout << endl;
}

void ConsoleUI::printSuccess(const string& message) 
{
    cout << SUCCESS_COLOR << BOLD << "[ ✓ ] " << RESET << SUCCESS_COLOR << message << RESET << endl;
}

void ConsoleUI::printError(const string& message) 
{
    cout << ERROR_COLOR << BOLD << "[ ✗ ] " << RESET << ERROR_COLOR << message << RESET << endl;
}

void ConsoleUI::printInfo(const string& message) 
{
    cout << BLUE << BOLD << "[ i ] " << RESET << SECONDARY_COLOR << message << RESET << endl;
}

void ConsoleUI::printLabelValue(const string& label, const string& value) 
{
    cout << LABEL_COLOR << label << ": " << RESET << SECONDARY_COLOR << value << RESET << endl;
}

string ConsoleUI::promptString(const string& prompt, bool required) 
{
    string input;
    while (true) 
    {
        cout << LABEL_COLOR << prompt << ": " << RESET;
        if (!getline(cin, input)) 
        {
            cin.clear();
            continue;
        }
        
        // Remove potential trailing carriage returns from files/redirected inputs
        if (!input.empty() && input.back() == '\r') {
            input.pop_back();
        }

        if (required && input.empty()) {
            printError("This field cannot be empty. Please try again.");
            continue;
        }
        break;
    }
    return input;
}

int ConsoleUI::promptInt(const string& prompt, int minVal, int maxVal) 
{
    string line;
    int value;
    while (true) 
    {
        cout << LABEL_COLOR << prompt << " (" << minVal << " - " << maxVal << "): " << RESET;
        if (!getline(cin, line)) 
        {
            cin.clear();
            continue;
        }
        
        stringstream ss(line);
        // if value in in range and there is no other value
        if (ss >> value && ss.eof()) 
        {
            // check if value in in range
            if (value >= minVal && value <= maxVal) 
            {
                break;
            }
        }
        printError("Invalid integer input or out of bounds. Please try again.");
    }
    return value;
}

double ConsoleUI::promptDouble(const string& prompt, double minVal) 
{
    string line;
    double value;
    while (true) 
    {
        cout << LABEL_COLOR << prompt << " (Min: " << minVal << "): " << RESET;
        if (!getline(cin, line)) 
        {
            cin.clear();
            continue;
        }
        
        stringstream ss(line);
        if (ss >> value && ss.eof()) {
            if (value >= minVal) {
                break;
            }
        }
        printError("Invalid decimal value. Please try again.");
    }
    return value;
}

bool ConsoleUI::promptConfirm(const string& prompt) 
{
    while (true) 
    {
        string ans = promptString(prompt + " (y/n)", true);
        if (ans == "y" || ans == "Y" || ans == "yes" || ans == "Yes") 
        {
            return true;
        }
        if (ans == "n" || ans == "N" || ans == "no" || ans == "No") 
        {
            return false;
        }
        printError("Please enter 'y' for Yes or 'n' for No.");
    }
}

int ConsoleUI::showMenu(const string& menuTitle, const ClassArray<string>& options) 
{
    clearScreen();
    printHeader(menuTitle);
    
    int width = DIVIDER_LENGTH;

    // Top border of Menu Box
    cout << SECONDARY_COLOR << BOLD << "┌";
    for (int i = 0; i < width - 2; ++i) cout << "─";
    cout << "┐" << endl;

    cout << "│";
    for (int i = 0; i < width - 2; ++i) cout << " ";
    cout << "│" << endl;


    // loop till number of options
    for (int i = 0; i < options.getSize(); ++i) 
    {
        
        int textLen = 4 + to_string(i + 1).length() + options[i].length();
        
        cout << "│" << RESET << " " << SECONDARY_COLOR << BOLD << "[" << (i + 1) << "] " 
             << RESET << SECONDARY_COLOR << options[i];
             
        int spaces = width - 2 - textLen;
        if (spaces < 0) spaces = 0;
        for (int s = 0; s < spaces; ++s) cout << " ";
        cout << SECONDARY_COLOR << BOLD << "│" << endl;
    }

    // Bottom border of Menu Box
    cout << "│";
    for (int i = 0; i < width - 2; ++i) cout << " ";
    cout << "│" << endl;
    cout << "└";
    for (int i = 0; i < width - 2; ++i) cout << "─";
    cout << "┘" << RESET << endl;


    // Divider separating user input prompt
    printDivider();
    cout << endl;
    
    return promptInt("Select an option", 1, options.getSize());
}

void ConsoleUI::printTable(const ClassArray<string>& headers, 
                           const ClassArray<int>& widths, 
                           const ClassArray<ClassArray<string>>& rows) 
{
    // if no headers, return
    if (headers.getSize() == 0) return;

    // Top border
    cout << SECONDARY_COLOR << BOLD;
    cout << "┌";
    for (int i = 0; i < headers.getSize(); ++i) 
    {
        for (int j = 0; j < widths[i] + 2; ++j) cout << "─";

        // after putting dashes, connect them with ┬ if it is not the last header
        if (i < headers.getSize() - 1) cout << "┬";
    }
    cout << "┐" << endl;

    // Headers
    cout << "│";
    for (int i = 0; i < headers.getSize(); ++i) 
    {
        cout << " " << BOLD << SECONDARY_COLOR << left << setw(widths[i]) << headers[i] << RESET << SECONDARY_COLOR << " │";
    }
    cout << endl;

    // Headers and rows separater
    cout << "├";
    for (int i = 0; i < headers.getSize(); ++i) 
    {
        for (int j = 0; j < widths[i] + 2; ++j) cout << "─";
        if (i < headers.getSize() - 1) cout << "┼";
    }
    cout << "┤" << endl;

    // data rows
    for (int r = 0; r < rows.getSize(); ++r) 
    {
        cout << "│";
        for (int c = 0; c < headers.getSize(); ++c) 
        {
            // put the column value if available else put empty string
            string val = "";
            if (c < rows[r].getSize()) 
            {
                val = rows[r][c];
            }
            cout << " " << SECONDARY_COLOR << left << setw(widths[c]) << val << RESET << SECONDARY_COLOR << " │";
        }
        cout << endl;
    }

    // Bottom border
    cout << "└";
    for (int i = 0; i < headers.getSize(); ++i) 
    {
        for (int j = 0; j < widths[i] + 2; ++j) cout << "─";
        if (i < headers.getSize() - 1) cout << "┴";
    }
    cout << "┘" << RESET << endl;
}

string ConsoleUI::formatDouble(double val) {
    stringstream ss;
    ss << fixed << setprecision(2) << val;
    return ss.str();
}
