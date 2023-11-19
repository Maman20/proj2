/**
 * @file main.cpp
 * @callergraph
 * @callgraph
 * @author Chakong Lor
 * @author (Comments by Roshan) (Testing done by Shishir and Abdi) (Doxygen documentation by Abdi)
 * @brief This program reads a CSV file containing postal code data, calculates state statistics,
 * and displays the easternmost, westernmost, northernmost, and southernmost locations for each state.
 * It also makes a CommandLineReader instance to check for zipcodes and if location is present
 * @see CCSVReader.h, CCSVReader.cpp, CommandLineReader.h, CommandLineReader.cpp for Class declaration, implementation, and Assumptions.
 * @details The program utilizes the CSVReader class to process the CSV file. The methods are run twice on two
 * different csv's. One contains the rows ordered by zip code, smallest to largest, The other csv is ordered by
 * location name alphabetically A-Z. The two running's are compared to ensure that their output is the same.
 */

#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include "CSVReader.h"
#include "CommandLineReader.h"

// Declaration for analyzeCSV
void analyzeCSV(CSVReader &file);



/**
 * @brief Main function to process and display state statistics from a CSV file and check location using commandLine
 * @details This function creates a CSVReader object, opens a CSV file, reads and
 * processes the data, and displays state statistics. 
 * It also makes a CommandLineReader instance to check for zipcodes and if location is present
 * @return 0 on success, 1 on failure (e.g., if the CSV file cannot be opened).
 */
int main() {
    //RunTest();
    // Create a CSVReader object and open a CSV file
    std::string file = "us_postal_codes.csv";
    std::cout << "Processing us_postal_codes.csv. \n" << std::endl;
    CSVReader csvReader(file);
    analyzeCSV(csvReader);

    std::string file2 = "us_postal_codes_place.csv";
    std::cout << "Processing us_postal_codes_ROWS_RANDOMIZED.csv. \n" << std::endl;
    CSVReader csvReader2(file2);
    analyzeCSV(csvReader2);

    std::cout << "\n" << std::endl;

    //check if location and its zipcode is in .csv file using commandline
    CommandLineReader cmdReader;
    cmdReader.Main();
    
    return 0;
}

/**
 * @brief Analyzes and displays state statistics from a CSVReader object.
 * @param csvReader The CSVReader object to analyze.
 * @pre The CSVReader object is open and initialized.
 * @post State statistics are displayed for the given CSVReader object.
 */
void analyzeCSV(CSVReader &csvReader) {
    //CSVReader csvReader(fileName);
    if (!csvReader.isOpen()) {
        std::cerr << "Failed to open CSV file." << std::endl;
        return;
    }
    // Read and process the CSV file.
    csvReader.ReadFile();


    // Close the CSV file.
    csvReader.close();
}


