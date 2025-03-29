#include <iostream>
#include <string>
#include <limits>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <fstream>

#include "../include/CreatingMap.h"
#include "../include/Menu.h"
#include "../include/RestrictedRoutePlanning.h"
#include "../include/IndependentRoutePlanning.h"
#include "../include/envFriendlyRoutePlanning.h"


// Function for manual fastest route input
void planFastestRouteMenu() {
    int origin, destination;
    std::cout << "Enter the origin location ID: ";
    std::cin >> origin;
    std::cout << "Enter the destination location ID: ";
    std::cin >> destination;
    IndependentRoutesResult result = planFastestRoute(origin, destination, true);
    outputIndependentRouteResult(result, std::cout, origin, destination);
}

// Function for batch mode fastest route
void planFastestRouteBatch() {
    std::ifstream inputFile("../input.txt");
    std::ofstream outputFile("../output.txt");

    // Ensure input file exists
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input.txt\n";
        return;
    }

    // Ensure output file exists (create if necessary)
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output.txt. Creating a new file...\n";
        std::ofstream createFile("../output.txt");  // This creates the file
        if (!createFile) {
            std::cerr << "Fatal error: Unable to create output.txt\n";
            return;
        }
        createFile.close();
        outputFile.open("../output.txt", std::ios::app); // Reopen the file for writing
    }

    std::string line;
    int origin = -1, destination = -1;

    while (std::getline(inputFile, line)) {
        // Find the position of ':'
        size_t pos = line.find(':');
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue;
        }

        // Extract label and value
        std::string label = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        // Trim spaces
        label.erase(0, label.find_first_not_of(" \t"));
        label.erase(label.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        // Process based on label
        if (label == "Mode") {
        } else if (label == "Source") {
            try {
                origin = std::stoi(value);
            } catch (...) {
                std::cerr << "Error: Invalid source value: " << value << std::endl;
            }
        } else if (label == "Destination") {
            try {
                destination = std::stoi(value);
            } catch (...) {
                std::cerr << "Error: Invalid destination value: " << value << std::endl;
            }
        } else {
            std::cerr << "Unknown label: " << label << std::endl;
        }
    }

    // Run fastest route calculation
    IndependentRoutesResult result = planFastestRoute(origin, destination, true);
    outputIndependentRouteResult(result, outputFile, origin, destination);

    inputFile.close();
    outputFile.close();
}

// Function for manual environmental friendly route input
void planEnvironmentallyFriendlyRouteMenu() {
    int origin, destination, maxWalkTime;
    std::unordered_set<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidSegments;
    std::string input;

    std::cout << "Enter the origin location ID: ";
    std::cin >> origin;
    std::cout << "Enter the destination location ID: ";
    std::cin >> destination;
    std::cout << "Enter the maximum walking time: ";
    std::cin >> maxWalkTime;

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

    EnvironmentallyFriendlyRouteResult result = planEnvironmentallyFriendlyRoute(origin, destination, maxWalkTime, avoidNodes, avoidSegments);
    outputEnvironmentallyFriendlyRouteResult(result, std::cout);
}

// Function for batch mode environmental friendly route
void planEnvironmentallyFriendlyRouteBatch() {
    std::ifstream inputFile("../input.txt");
    std::ofstream outputFile("../output.txt", std::ios::app); // Append mode

    // Ensure input file exists
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input.txt\n";
        return;
    }

    // Ensure output file exists (create if necessary)
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output.txt. Creating a new file...\n";
        std::ofstream createFile("../output.txt");
        if (!createFile) {
            std::cerr << "Fatal error: Unable to create output.txt\n";
            return;
        }
        createFile.close();
        outputFile.open("../output.txt", std::ios::app); // Reopen for writing
    }

    std::string line;
    int origin = -1, destination = -1, maxWalkTime = -1;
    std::unordered_set<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidSegments;

    while (std::getline(inputFile, line)) {
        size_t pos = line.find(':');
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue;
        }

        std::string label = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        // Trim spaces
        label.erase(0, label.find_first_not_of(" \t\r\n"));
        label.erase(label.find_last_not_of(" \t\r\n") + 1);
        value.erase(0, value.find_first_not_of(" \t\r\n"));
        value.erase(value.find_last_not_of(" \t\r\n") + 1);

        if (label == "Mode") {
        }
        else if (label == "Source") {
            try {
                origin = std::stoi(value);
            } catch (...) {
                std::cerr << "Error: Invalid source value: " << value << std::endl;
            }
        }
        else if (label == "Destination") {
            try {
                destination = std::stoi(value);
            } catch (...) {
                std::cerr << "Error: Invalid destination value: " << value << std::endl;
            }
        }
        else if (label == "MaxWalkTime") {
            try {
                maxWalkTime = std::stoi(value);
            } catch (...) {
                std::cerr << "Error: Invalid source value: " << value << std::endl;
            }
        }
        else if (label == "AvoidNodes") {
            if (!value.empty()) {
                std::stringstream ss(value);
                std::string node;
                while (std::getline(ss, node, ',')) {
                    try {
                        avoidNodes.insert(std::stoi(node));
                    } catch (...) {
                        std::cerr << "Error: Invalid avoid node: " << node << std::endl;
                    }
                }
            }
        }
        else if (label == "AvoidSegments") {
            if (!value.empty()) {
                std::stringstream ss(value);
                char dummy;
                int from, to;
                while (ss >> dummy && dummy == '(') {
                    if (ss >> from >> dummy >> to >> dummy && dummy == ')') {
                        avoidSegments.emplace_back(from, to);
                    }
                    ss >> dummy;
                }
            }
        }
    }

    EnvironmentallyFriendlyRouteResult result = planEnvironmentallyFriendlyRoute(origin, destination, maxWalkTime, avoidNodes, avoidSegments);
    outputEnvironmentallyFriendlyRouteResult(result, outputFile);

    inputFile.close();
    outputFile.close();
    }

// Function for manual restricted route input
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
        // No restrictions, plan the fastest route
        planFastestRoute(origin, destination, false);
    } else {
        // With restrictions
        RestrictedRoutesResult result = excludeNodesOrSegments(origin, destination, avoidNodes, avoidSegments, include);
        outputRestrictedRouteResult(result, std::cout, origin, destination);
    }
}

// Function for batch mode restricted route
void excludeNodesOrSegmentsBatch() {
    std::ifstream inputFile("../input.txt");
    std::ofstream outputFile("../output.txt", std::ios::app); // Append mode

    // Ensure input file exists
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input.txt\n";
        return;
    }

    // Ensure output file exists (create if necessary)
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output.txt. Creating a new file...\n";
        std::ofstream createFile("../output.txt");
        if (!createFile) {
            std::cerr << "Fatal error: Unable to create output.txt\n";
            return;
        }
        createFile.close();
        outputFile.open("../output.txt", std::ios::app); // Reopen for writing
    }

    std::string line, mode;
    int origin = -1, destination = -1, include = -1;
    std::unordered_set<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidSegments;

    while (std::getline(inputFile, line)) {
        size_t pos = line.find(':');
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue;
        }

        std::string label = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        // Trim spaces
        label.erase(0, label.find_first_not_of(" \t\r\n"));
        label.erase(label.find_last_not_of(" \t\r\n") + 1);
        value.erase(0, value.find_first_not_of(" \t\r\n"));
        value.erase(value.find_last_not_of(" \t\r\n") + 1);

        if (label == "Mode") {
            mode = value;
        }
        else if (label == "Source") {
            try {
                origin = std::stoi(value);
            } catch (...) {
                std::cerr << "Error: Invalid source value: " << value << std::endl;
            }
        }
        else if (label == "Destination") {
            try {
                destination = std::stoi(value);
            } catch (...) {
                std::cerr << "Error: Invalid destination value: " << value << std::endl;
                continue;
            }
        }
        else if (label == "AvoidNodes") {
            if (!value.empty()) {
                std::stringstream ss(value);
                std::string node;
                while (std::getline(ss, node, ',')) {
                    try {
                        avoidNodes.insert(std::stoi(node));
                    } catch (...) {
                        std::cerr << "Error: Invalid avoid node: " << node << std::endl;
                    }
                }
            }
        }
        else if (label == "AvoidSegments") {
            if (!value.empty()) {
                std::stringstream ss(value);
                char dummy;
                int from, to;
                while (ss >> dummy && dummy == '(') {
                    if (ss >> from >> dummy >> to >> dummy && dummy == ')') {
                        avoidSegments.emplace_back(from, to);
                    }
                    ss >> dummy;
                }
            }
        }
        else if (label == "IncludeNode") {
            try {
                if (!value.empty()) {
                    include = std::stoi(value);
                }
            } catch (...) {
                std::cerr << "Error: Invalid include node: " << value << std::endl;
            }
        }
        else {
            std::cerr << "Unknown label: " << label << std::endl;
        }
}


    // Run the restricted route calculation
    RestrictedRoutesResult result = excludeNodesOrSegments(origin, destination, avoidNodes, avoidSegments, include);
    outputRestrictedRouteResult(result, outputFile, origin, destination);

    inputFile.close();
    outputFile.close();
}

// Handles the fastest route selection
void handleFastestRouteOption() {
    int subChoice = 0;
    std::cout << "Fastest Route: Choose input method:\n";
    std::cout << "  1) Manual input (terminal)\n";
    std::cout << "  2) Batch input (files)\n";
    std::cout << "-> ";
    std::cin >> subChoice;

    if (subChoice == 1) {
        planFastestRouteMenu();
    } else if (subChoice == 2) {
        planFastestRouteBatch();
    } else {
        std::cout << "Invalid sub-choice.\n";
    }
}

// Handles the Environmentally Friendly route selection
void handleEnvironmentallyFriendlyRouteOption() {
    int subChoice = 0;
    std::cout << "Environmentally Friendly Route: Choose input method:\n";
    std::cout << "  1) Manual input (terminal)\n";
    std::cout << "  2) Batch input (files)\n";
    std::cout << "-> ";
    std::cin >> subChoice;

    if (subChoice == 1) {
        planEnvironmentallyFriendlyRouteMenu();
    } else if (subChoice == 2) {
        planEnvironmentallyFriendlyRouteBatch();
    } else {
        std::cout << "Invalid sub-choice.\n";
    }
}
// Handles the restricted route selection
void handleRestrictedOption() {
    int subChoice = 0;
    std::cout << "Restricted Route: Choose input method:\n";
    std::cout << "  1) Manual input (terminal)\n";
    std::cout << "  2) Batch input (files)\n";
    std::cout << "-> ";
    std::cin >> subChoice;

    if (subChoice == 1) {
        excludeNodesOrSegmentsMenu();
    } else if (subChoice == 2) {
        excludeNodesOrSegmentsBatch();
    } else {
        std::cout << "Invalid sub-choice.\n";
    }
}

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

        if (std::cin.fail() || choice < 1 || choice > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice, please select a valid option from 1 to 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                handleFastestRouteOption();
                break;
            case 2:
                //planSecondFastestRoute();
                break;
            case 3:
                handleEnvironmentallyFriendlyRouteOption();
                break;
            case 4:
                handleRestrictedOption();
                break;
            case 5:
                //displayRouteInfo();
                break;
            case 6:
                std::cout << "Exiting the program...\n";
                break;
            default: ;
        }
    }
}
