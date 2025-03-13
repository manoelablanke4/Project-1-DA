#include <iostream>
#include <string>
#include <limits>
#include <unordered_set>
#include <vector>
#include <sstream>
#include "../include/Menu.h"
#include "../include/RestrictedRoutePlanning.h"

// Functions must be developed here
void planFastestRouteMenu() {
    int origin, destination;
    std::cout << "Enter the origin location ID: ";
    std::cin >> origin;
    std::cout << "Enter the destination location ID: ";
    std::cin >> destination;

    planFastestRoute(origin, destination, true);
}

void planSecondFastestRoute() {
    std::cout << "Planning the second-fastest route...\n";
}

void planEnvironmentallyFriendlyRoute() {
    std::cout << "Planning an environmentally-friendly route...\n";
}

void excludeNodesOrSegmentsMenu() {
    int origin, destination;
    std::unordered_set<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidSegments;
    std::string input;

    std::cout << "Enter the origin location ID: ";
    std::cin >> origin;

    std::cout << "Enter the destination location ID: ";
    std::cin >> destination;

    std::cin.ignore();

    // Nodes to avoid
    std::cout << "Enter nodes to avoid (format: x,z,y) or press Enter for none: ";
    getline(std::cin, input);
    if (!input.empty()) {
        std::stringstream ss(input);
        std::string node;
        while (getline(ss, node, ',')) {
            avoidNodes.insert(std::stoi(node));
        }
    }

    // Segments to avoid
    std::cout << "Enter segments to avoid (format: (x,y),(a,b)) or press Enter for none: ";
    getline(std::cin, input);
    if (!input.empty()) {
        std::stringstream ss(input);
        char dummy;
        int src, dst;

        while (ss >> dummy && dummy == '(') {
            if (ss >> src >> dummy >> dst >> dummy && dummy == ')') {
                avoidSegments.emplace_back(src, dst);
            }
            ss >> dummy; // consume ',' between segments
        }
    }

    // Location to include
    int include = -1;
    std::cout << "Enter node to include or press Enter for none: ";
    getline(std::cin, input);
    if (!input.empty()) {
        include = std::stoi(input);
    }

    // Check if user wants any restriction
    if (avoidNodes.empty() && avoidSegments.empty() && include == -1) {
        // Sem restrições, plano mais rápido
        planFastestRoute(origin, destination, false);
    } else {
        // Com restrições
        excludeNodesOrSegments(origin, destination, avoidNodes, avoidSegments, include);
    }
}

void displayRouteInfo() {
    std::cout << "Displaying detailed route information...\n";
}

void showMainMenu() {
    std::cout << "=================================================================================================" << std::endl;
    std::cout << "### Welcome to the Route Planning Tool! ###" << std::endl;
    std::cout << "Please choose an option from the following:" << std::endl;
    std::cout << "[1] Plan the fastest route from a starting location to a destination." << std::endl;
    //std::cout << "[2] Plan the second-fastest route from a starting location to a destination." << std::endl;
    //std::cout << "[3] Plan an environmentally-friendly route that combines driving and walking (with parking options)." << std::endl;
    std::cout << "[4] Exclude specific locations or segments from the route calculation." << std::endl;
    //std::cout << "[5] Display detailed route information (e.g., time, path, nodes)." << std::endl;
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

        if (std::cin.fail() || choice < 1 || choice > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice, please select a valid option from 1 to 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                planFastestRouteMenu();
                break;
            case 2:
                planSecondFastestRoute();
                break;
            case 3:
                planEnvironmentallyFriendlyRoute();
                break;
            case 4:
                excludeNodesOrSegmentsMenu();
                break;
            case 5:
                displayRouteInfo();
                break;
            case 6:
                std::cout << "Exiting the program...\n";
                break;
        }
    }
}
