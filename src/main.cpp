#include <iostream>
#include <fstream>
#include <string>
#include "../include/Menu.h"
#include "../include/BatchMode.h"

/**
 * @file main.cpp
 * @brief Entry point of the application. Determines whether to run in batch mode or interactive menu mode.
 *
 * If command-line arguments are provided, the application runs in batch mode, processing input and output files.
 * If no arguments are given, it launches an interactive menu for user interaction.
 */

/**
 * @brief Main function of the application.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 *        - argv[1]: Path to the input file (optional).
 *        - argv[2]: Path to the output file (optional, defaults to "../output.txt").
 *
 * @return int Exit status.
 */
int main(int argc, char* argv[]) {
    if (argc > 1) {
        // Batch mode: Process input file and create output file
        std::string inputFile = argv[1];
        std::string outputFile = (argc > 2) ? argv[2] : "../output.txt"; // Use given output file or default

        std::cout << "Running in batch mode with input file: " << inputFile << std::endl;
        std::cout << "Output will be written to: " << outputFile << std::endl;

        runBatchMode(inputFile, outputFile); // Call batch mode function
    } else {
        // No arguments provided: Run interactive menu mode
        std::cout << "Launching interactive mode...\n";
        handleMenuSelection(); // Open the menu
    }

    return 0;
}
