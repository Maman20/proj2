/**
 * @file CSVReader.h
 * @callergraph
 * @callgraph
 * @author Fabian MullerDahlberg
 * @author (Comments by Roshan and Fabian) (Testing done by Shishir) (Doxygen documentation by Abdi)
 * @brief Declarations for class CSVReader
 * @see CSVReader.cpp for the implementation of these functions.
 * @details
 * This file declares the class CSVReader, which provides functionality to read and process CSV files.
 * The class includes member functions for opening, reading, and analyzing CSV files, as well as storing and retrieving state statistics.
 *
 * Assumptions:
 * - The input CSV file is properly formatted with valid data.
 * - The CSV file has a header row that defines column names.
 * - Latitude and longitude values are provided in decimal format.
 * - The CSV file contains data for multiple states.
 * - The CSV file follows the format: Zip,Name,State,County,Latitude,Longitude.
 * - Rows with missing or invalid data will be skipped.
 * - The CSV file may be large, so memory usage is considered.
 * - State statistics, including maximum and minimum values, are calculated and stored for each state in the data.
 */

#ifndef ZIPCODES_CSVREADER_H
#define ZIPCODES_CSVREADER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "HeaderRecord.h"

/**
 * @brief Represents a row of data in the CSV file.
 * This struct stores information for a single row of data in the CSV file,
 * including the ZIP code, name, state, county, latitude, and longitude.
 */
struct Row {
    int zip;            /**< The ZIP code. */
    std::string name;   /**< The place name. */
    std::string state;  /**< The state. */
    std::string county; /**< The county. */
    float latitude;    /**< The latitude. */
    float longitude;   /**< The longitude. */
};

struct Record {
    int recordLength;
    std::vector<char> recordData;
    // Add other fields specific to a length-indicated record
};

class CSVReader {
public:

    /**
     * @brief Constructor that opens the CSV file specified by the 'filename' parameter.
     * @param filename The name of the CSV file to open.
     * @pre None.
     * @post The CSVReader object is constructed, and the CSV file is opened for reading.
     */
    CSVReader(const std::string filename);

    /**
     * @brief Checks if the CSV file is open.
     * @return true if the CSV file is open, false otherwise.
     * @pre None.
     * @post None.
     */
    bool isOpen() const;

    /**
     * @brief Parses and stores the header row of the CSV file.
     * @param line The header row of the CSV file.
     * @pre The CSV file is open for reading.
     * @post The 'Headers' vector is populated with column headers from the CSV file.
     */
    void GetHeaders(std::string &line);

    /**
     * @brief Reads and processes the entire CSV file.
     * @pre The CSV file is open for reading.
     * @post The CSV file is read, and data is parsed and stored in memory.
     */
    void buildFileStructure(std::ofstream& file,HeaderRecord& headerRecord);

    /**
     * @brief Parses a single data row of the CSV file into a Row object.
     * @param Line The data row to parse.
     * @param r Reference to the Row object to store the parsed data.
     * @pre The CSV file is open for reading.
     * @post The 'r' object is updated with data from the input 'Line'.
     */
    static std::vector<std::string> ParseLine(const std::string &line);

    /**
     * @brief Closes the CSV file if it's open.
     * @pre None.
     * @post The CSV file is closed if it was open.
     */
    void close();

    ~CSVReader();

    //---------------- New methods for handling length-indicated records ------------------------------------//
    void ConvertToLength(const std::string& inputRecord, Record& outputRecord);
    void WriteToFile(const std::string& str, std::ofstream& file);
    static std::pair<std::size_t, std::string> ReadFromFile(std::ifstream& file);
    HeaderRecord GenerateHeaderRecord();
    bool BuildDataFile(const std::string& sourceFile1, const std::string& sourceFile2, const std::string& destinationFile);

private:
    std::ifstream ZipCSV; /**< Represents the input CSV file stream used to open and read the CSV file. */
    std::vector<std::string> Headers; /**< Stores the column headers from the CSV file. */
};

#endif //ZIPCODES_CSVREADER_H
