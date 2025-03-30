#ifndef BATCH_MODE_H
#define BATCH_MODE_H

/**
 * @file BatchMode.h
 * @brief Declaration for executing route planning in batch mode using input/output files.
 */

/**
 * @brief Processes input file, parses instructions, and performs route planning.
 *
 * @param inputFile Path to input batch instructions.
 * @param outputFile Path to output results.
 *
 * @note **Time Complexity:** O((V + E) log V), dominated by route planning algorithm.
 */
void processInputFile(const std::string& inputFile, const std::string& outputFile);



/**
 * @brief Runs batch mode using a provided input file and optional output file.
 *
 * Parses route instructions from a file and triggers the appropriate route planning logic.
 *
 * @param inputFile Path to the input file containing route instructions.
 * @param outputFile Path to the output file where results will be written.
 * @note **Time Complexity:** O((V + E) log V), inherited from processInputFile().
 */
void runBatchMode(const std::string& inputFile, const std::string& outputFile);

#endif // BATCH_MODE_H
