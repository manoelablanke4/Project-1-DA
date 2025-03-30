/**
 * @file BatchMode.cpp
 * @brief Implements functionality to run route planning in batch mode using input/output files.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include "../include/BatchMode.h"
#include "../include/IndependentRoutePlanning.h"
#include "../include/RestrictedRoutePlanning.h"

/**
 * @brief Reads input data from a file, parses route options, and writes the result to an output file.
 *
 * Determines whether to run independent route planning (no restrictions) or restricted route planning
 * based on the parsed fields from the input file.
 *
 * @param inputFile Path to the input file containing batch route instructions.
 * @param outputFile Path to the output file where results will be written.
 */
void processInputFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    std::ofstream out(outputFile, std::ios::out | std::ios::trunc); // Create/overwrite file

    if (!in.is_open()) {
        std::cerr << "Error opening input file: " << inputFile << "\n";
        return;
    }

    if (!out.is_open()) {
        std::cerr << "Error creating output file: " << outputFile << "\n";
        return;
    }

    std::string line, mode;
    int origin = -1, destination = -1, includeNode = -1;
    std::unordered_set<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidSegments;

    // Read file line by line
    while (std::getline(in, line)) {
        size_t pos = line.find(':');
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue;
        }

        std::string label = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        // Trim spaces
        label.erase(0, label.find_first_not_of(" \t"));
        label.erase(label.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        // Process fields
        if (label == "Mode") {
            mode = value;
        } else if (label == "Source") {
            try { origin = std::stoi(value); } catch (...) { std::cerr << "Invalid Source: " << value << "\n"; }
        } else if (label == "Destination") {
            try { destination = std::stoi(value); } catch (...) { std::cerr << "Invalid Destination: " << value << "\n"; }
        } else if (label == "AvoidNodes") {
            if (!value.empty()) {
                std::stringstream ss(value);
                std::string node;
                while (std::getline(ss, node, ',')) {
                    try { avoidNodes.insert(std::stoi(node)); } catch (...) { std::cerr << "Invalid AvoidNode: " << node << "\n"; }
                }
            }
        } else if (label == "AvoidSegments") {
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
        } else if (label == "IncludeNode") {
            try { if (!value.empty()) { includeNode = std::stoi(value); } } catch (...) { std::cerr << "Invalid IncludeNode: " << value << "\n"; }
        } else {
            std::cerr << "Unknown label: " << label << "\n";
        }
    }

    in.close();

    // Determine which function to call based on input data
    if (avoidNodes.empty() && avoidSegments.empty() && includeNode == -1) {
        std::cout << "Calling Independent Route Planning...\n";
        IndependentRoutesResult result = planFastestRoute(origin, destination, true);
        outputIndependentRouteResult(result, out, origin, destination);
    } else {
        std::cout << "Calling Restricted Route Planning...\n";
        RestrictedRoutesResult result = excludeNodesOrSegments(origin, destination, avoidNodes, avoidSegments, includeNode);
        outputRestrictedRouteResult(result, out, origin, destination);
    }

    out.close();
}

/**
 * @brief Launches batch mode route planning using an input file and optional output file.
 *
 * Validates the input file and triggers the processing of instructions.
 *
 * @param inputFile Path to the input file with route instructions.
 * @param outputFile Path to the output file (default is "output.txt").
 */
void runBatchMode(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    if (!in.is_open()) {
        std::cerr << "Error: Cannot open input file: " << inputFile << "\n";
        return;
    }
    in.close();

    // Process the input file and write the result
    processInputFile(inputFile, outputFile);
}
