#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <string>
#include <vector>

class ConsoleUI 
{
    public:
        // Layout Constant
        static const int SCREEN_WIDTH = 80;

        // Core Layout Helpers
        static void printDivider(char ch = '-', int width = SCREEN_WIDTH);
        static void printHeader(const std::string& title);
        static void clearScreen();

        // Advanced Table Alignment Formatting (<iomanip>)
        static void printTableHeader(const std::vector<std::string>& headers, const std::vector<int>& widths);
        static void printTableRow(const std::vector<std::string>& cells, const std::vector<int>& widths);
};

#endif
