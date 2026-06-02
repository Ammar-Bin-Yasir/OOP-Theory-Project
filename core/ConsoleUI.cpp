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
int ConsoleUI::DIVIDER_LENGTH = 80;
string ConsoleUI::PRIMARY_COLOR = ConsoleUI::CYAN;
string ConsoleUI::SECONDARY_COLOR = ConsoleUI::WHITE;
string ConsoleUI::SUCCESS_COLOR = ConsoleUI::GREEN;
string ConsoleUI::ERROR_COLOR = ConsoleUI::RED;
string ConsoleUI::LABEL_COLOR = ConsoleUI::YELLOW;

void ConsoleUI::clearScreen() 
{
    cout << "\033[2J\033[1;1H" << flush;
}

void ConsoleUI::printDivider() 
{
    cout << PRIMARY_COLOR << "═" << RESET;
    for (int i = 0; i < DIVIDER_LENGTH - 2; ++i) 
    {
        cout << PRIMARY_COLOR << "═";
    }
    cout << RESET << endl;
}

/*
╔═════════════════════════╗
║    STUDENT DASHBOARD    ║
╚═════════════════════════╝
*/
void ConsoleUI::printHeader(const string& title) 
{
    int boxWidth = title.length() + (HEADER_PADDING * 2) + 2;

    cout << endl << PRIMARY_COLOR << BOLD;
    
    // Top border
    cout << "╔";
    for (int i = 0; i < boxWidth - 2; ++i) cout << "═";
    cout << "╗" << endl;

    // Centered Title Line
    cout << "║";
    for (int i = 0; i < HEADER_PADDING; ++i) cout << " ";
    cout << title;
    for (int i = 0; i < HEADER_PADDING; ++i) cout << " ";
    cout << "║" << endl;

    // Bottom border
    cout << "╚";
    for (int i = 0; i < boxWidth - 2; ++i) cout << "═";
    cout << "╝" << RESET << endl << endl;
}

void ConsoleUI::pause() 
{
    cout << endl << LABEL_COLOR << "Press Enter to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
}

void ConsoleUI::printSuccess(const string& message) 
{
    cout << SUCCESS_COLOR << BOLD << "[✓] " << RESET << SUCCESS_COLOR << message << RESET << endl;
}

void ConsoleUI::printError(const string& message) 
{
    cout << ERROR_COLOR << BOLD << "[✗] " << RESET << ERROR_COLOR << message << RESET << endl;
}

void ConsoleUI::printInfo(const string& message) 
{
    cout << BLUE << BOLD << "[i] " << RESET << SECONDARY_COLOR << message << RESET << endl;
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
    
    for (int i = 0; i < options.getSize(); ++i) 
    {
        cout << PRIMARY_COLOR << BOLD << "  [" << (i + 1) << "] " << RESET << SECONDARY_COLOR << options[i] << RESET << endl;
    }
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
    cout << PRIMARY_COLOR;
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
        cout << " " << BOLD << SECONDARY_COLOR << left << setw(widths[i]) << headers[i] << RESET << PRIMARY_COLOR << " │";
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
            cout << " " << SECONDARY_COLOR << left << setw(widths[c]) << val << RESET << PRIMARY_COLOR << " │";
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
