#include "core/ConsoleUI.h"
#include <iostream>
#include <iomanip>

using namespace std;

void ConsoleUI::printDivider(char ch, int width) {
    for (int i = 0; i < width; ++i) {
        cout << ch;
    }
    cout << "\n";
}

void ConsoleUI::printHeader(const string& title) {
    clearScreen();
    printDivider('=', SCREEN_WIDTH);
    
    // Centering System Title
    string mainTitle = "UNIVERSITY TRANSPORT MANAGEMENT SYSTEM";
    int spacesMain = (SCREEN_WIDTH - mainTitle.length()) / 2;
    cout << string(spacesMain > 0 ? spacesMain : 0, ' ') << mainTitle << "\n";

    // Centering Section Title
    int spacesTitle = (SCREEN_WIDTH - title.length()) / 2;
    cout << string(spacesTitle > 0 ? spacesTitle : 0, ' ') << title << "\n";
    
    printDivider('=', SCREEN_WIDTH);
}

void ConsoleUI::clearScreen() {
    // Cross-platform ANSI escape code to clear terminal screen
    cout << "\033[2J\033[1;1H";
}

void ConsoleUI::printTableHeader(const vector<string>& headers, const vector<int>& widths) {
    printDivider('-', SCREEN_WIDTH);
    for (size_t i = 0; i < headers.size(); ++i) {
        cout << left << setw(widths[i]) << headers[i];
    }
    cout << "\n";
    printDivider('-', SCREEN_WIDTH);
}

void ConsoleUI::printTableRow(const vector<string>& cells, const vector<int>& widths) {
    for (size_t i = 0; i < cells.size(); ++i) {
        cout << left << setw(widths[i]) << cells[i];
    }
    cout << "\n";
}
