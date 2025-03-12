#include <iostream>
#include <string>
#include <limits>

void showMainMenu() {
    std::cout << "=================================================================================================" << std::endl;
    std::cout << "### Welcome to the Route Planning Tool! ###" << std::endl;
    std::cout << "Please choose an option from the following:" << std::endl;
    std::cout << "[1] Plan the fastest route from a starting location to a destination." << std::endl;
    std::cout << "[2] Plan the second-fastest route from a starting location to a destination." << std::endl;
    std::cout << "[3] Plan an environmentally-friendly route that combines driving and walking (with parking options)." << std::endl;
    std::cout << "[4] Exclude specific locations or segments from the route calculation." << std::endl;
    std::cout << "[5] Display detailed route information (e.g., time, path, nodes)." << std::endl;
    std::cout << "[6] Exit the program." << std::endl;
    std::cout << "=================================================================================================" << std::endl;
    std::cout << "-> ";
}

void handleMenuSelection() {
    int choice = 0;
    while (choice != 6) {
        showMainMenu();
        std::cout << "Enter your choice (1-6): ";
        
        std::cin >> choice;
        
        // Handle invalid input
        if (std::cin.fail() || choice < 1 || choice > 6) {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore wrong input
            std::cout << "Invalid choice, please select a valid option from 1 to 6." << std::endl;
            continue;
        }
        
        // switch (choice) {
        //     case 1:
        //         planFastestRoute();
        //         break;
        //     case 2:
        //         planSecondFastestRoute();
        //         break;
        //     case 3:
        //         planEnvironmentallyFriendlyRoute();
        //         break;
        //     case 4:
        //         excludeNodesOrSegments();
        //         break;
        //     case 5:
        //         displayRouteInfo();
        //         break;
        //     case 6:
        //         std::cout << "Exiting the program..." << std::endl;
        //         break;
        // }
    }
}

int main() {
    handleMenuSelection();
    return 0;  // Return 0 indicates the program executed successfully
}
