/**
 * @file CommandLineReader.h
 * @callergraph
 * @callgraph
 * @author Abdirahman Abdi
 * @brief Declarations for class CommandLineReader
 * @see CommandLineReader.cpp for the implementation of these functions.
 * @details
 * This file declares the class CommandLineReader, which provides functionality to read and process commands from the command line.
 * The class includes member functions for starting the reader loop and parsing command line input.
 *
 * Assumptions:
 * - Input from the command line is provided in a valid format.
 * - Parsing functions are capable of handling various types of command input.
 * - The loop continues until a termination condition is met.
 */

#ifndef COMMANDLINEREADER_H
#define COMMANDLINEREADER_H

#include <string>

class CommandLineReader {
public:
    /**
     * @brief Default constructor for CommandLineReader.
     * @pre None.
     * @post A CommandLineReader object is constructed with default settings.
     */
    CommandLineReader();

    /**
     * @brief Starts the command line reader loop, processing inputs.
     * @pre None.
     * @post Command lines are processed until the reader is terminated.
     */
    void Main();

    /**
     * @brief Parses the provided command line input string.
     * @param input The command line input as a string.
     * @pre Valid input string is provided.
     * @post The input string is parsed and appropriate actions are taken based on the content.
     */
    void ParseCommandLine(const std::string& input);

private:
    bool running;  /**< Flag to check if the program is still running. */
};

#endif //COMMANDLINEREADER_H
