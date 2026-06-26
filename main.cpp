#include "Engine/TransportManager.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() 
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    // 1. Instantiate the central engine core
    TransportManager systemEngine;

    // 2. Boot phase: Load all historical data from files into dynamic memory
    // (Reads users.txt, vehicles.txt, routes.txt, passes.txt)
    systemEngine.loadSystemData();

    // 3. Operational phase: Hand control over to the main application loop
    // This method handles the login/registration menus and polymorphic routing
    systemEngine.runMainMenu();

    // 4. Shutdown phase: Before the program exits, save state back to disk
    // and let the TransportManager destructor cleanly 'delete' all allocated pointers.
    systemEngine.saveSystemData();

    return 0;
}