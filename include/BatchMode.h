#ifndef BATCH_MODE_H
#define BATCH_MODE_H

/**
 * @file BatchMode.h
 * @brief Declaration for executing route planning in batch mode using input/output files.
 */

/**
 * @brief Runs batch mode using a provided input file and optional output file.
 *
 * Parses route instructions from a file and triggers the appropriate route planning logic.
 *
 * @param inputFile Path to the input file containing route instructions.
 * @param outputFile Path to the output file where results will be written.
 */
void runBatchMode(const std::string& inputFile, const std::string& outputFile);

#endif // BATCH_MODE_H
