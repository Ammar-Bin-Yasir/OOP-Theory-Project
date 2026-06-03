#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <string>
#include "core/ClassArray.h"

class ConsoleUI 
{
    public:
        // Text Color / Formatting Constants (ANSI Codes)
        static const std::string RESET;
        static const std::string BOLD;
        static const std::string RED;
        static const std::string GREEN;
        static const std::string YELLOW;
        static const std::string BLUE;
        static const std::string CYAN;
        static const std::string WHITE;

        // Configurable UI Settings (Adjustable for terminal size)
        static int HEADER_PADDING;
        static int DIVIDER_LENGTH;
        static std::string PRIMARY_COLOR;
        static std::string SECONDARY_COLOR;
        static std::string SUCCESS_COLOR;
        static std::string ERROR_COLOR;
        static std::string LABEL_COLOR;

        // Display Utilities
        static void clearScreen();
        static void printHeader(const std::string& title);
        static void printDivider();
        static void pause();

        // Styled Status Outputs
        static void printSuccess(const std::string& message);
        static void printError(const std::string& message);
        static void printInfo(const std::string& message);
        static void printLabelValue(const std::string& label, const std::string& value);

        // Safe Input Helpers (Robust against standard cin crash loops)
        static std::string promptString(const std::string& prompt, bool required = true);
        static int promptInt(const std::string& prompt, int minVal, int maxVal);
        static double promptDouble(const std::string& prompt, double minVal = 0.0);
        static bool promptConfirm(const std::string& prompt);

        // Generic Menu Renderer
        static int showMenu(const std::string& menuTitle, const ClassArray<std::string>& options);

        // Advanced Table Alignment & Grid System
        static void printTable(const ClassArray<std::string>& headers, 
                               const ClassArray<int>& widths, 
                               const ClassArray<ClassArray<std::string>>& rows);

        // Double formatting helper
        static std::string formatDouble(double val);
};

#endif
