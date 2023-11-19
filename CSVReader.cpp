/**
 * @file CSVReader.cpp
 * @callergraph
 * @callgraph
 * @author Fabian MullerDahlberg
 * @authors (comments by Hamaad) (Testing done by Shishir) (Doxygen documentation by Abdi)
 * @brief Member function definitions for class CSVReader
 * @see CCSVReader.h for declaration.
 * @details
 * - Constructor: Opens a specified CSV file for reading.
 * - isOpen(): Checks if the CSV file is currently open.
 * - GetHeaders(): Parses and stores the header row of the CSV file, populating the Headers vector with column headers.
 * - ReadFile(): Reads and processes the entire CSV file, including parsing data rows and calculating state statistics.
 * - ParseLine(): Parses a single data row of the CSV file into a Row object, updating it with data from the input line.
 * - CheckMaxima(): Checks and updates a map (StateMaximums) with maximum and minimum values for latitude and longitude based on the input Row.
 * - CompareExtremes(): Compares and updates the maximum and minimum values for latitude and longitude in a state.
 * - GetStateMaximums(): Retrieves a copy of the StateMaximums map, which contains state statistics.
 * - close(): Closes the CSV file if it's currently open.
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

/**
 *
 */
#include "CSVReader.h"
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

/**
 * @brief Constructor that opens the CSV file specified by the 'filename' parameter.
 * @param filename The name of the CSV file to open.
 * @pre None.
 * @post The CSVReader object is constructed, and the CSV file is opened for reading.
 */
CSVReader::CSVReader(const std::string filename) {
    ZipCSV.open(filename, std::ios::in);
}

/**
 * @brief Checks if the CSV file is open.
 * @return true if the CSV file is open, false otherwise.
 * @pre None.
 * @post None.
 */
bool CSVReader::isOpen() const {
    return ZipCSV.is_open();
}

/**
 * @brief Parses and stores the header row of the CSV file.
 * @param line The header row of the CSV file.
 * @pre The CSV file is open for reading.
 * @post The 'Headers' vector is populated with column headers from the CSV file.
 */
void CSVReader::GetHeaders(std::string &line) {
    std::stringstream stream(line);
    std::string header;
    // Parses the first of the csv by comma to get headers
    while (std::getline(stream, header, ',')) {
        // Adds headers to the vector
        Headers.push_back(header);
    }
}

/**
 * @brief Reads and processes the entire CSV file.
 * @pre The CSV file is open for reading.
 * @post The CSV file is read, and data is parsed and stored in memory.
 */
void CSVReader::buildFileStructure(std::ofstream& file,HeaderRecord& headerRecord) {
    std::string line;

    // Read and store the header row of the CSV file.
    std::getline(ZipCSV, line, '\n');
    GetHeaders(line);
    headerRecord.setFieldsPerRecord(Headers.size());
    int recordCount = 0;
    // Read and process each data row of the CSV file.
    while (std::getline(ZipCSV, line, '\n')) {

        // line needs to be converted to length indicated
        // after converting read to file.
       //  ParseLine(line, NewRow);
        WriteToFile(line, file);
        recordCount = recordCount + 1;
    }
    headerRecord.setRecordCount(recordCount);
}

/**
 * @brief
 * @param
 * @param
 * @pre
 * @post
 */
std::vector<std::string> CSVReader::ParseLine(const std::string& Record) {
    // for parsing a length indicated record after being read from data file, not csv
    // consider switching to the c++ >> operator
    // parse by comma based on fields read from header
    std::stringstream stream(Record);
    std::string field;
    std::vector<std::string> parsedRecord;
    while (std::getline(stream, field, ',')) {
        parsedRecord.push_back(field);
    }
    return parsedRecord;
}

// -----------------New methods for handling length-indicated records -------------------------------//
void CSVReader::ConvertToLength(const std::string& inputRecord, Record& outputRecord) {
    // Implementation for ConvertToLength
    // Maintains comma seperated nature of original data but prepends binary integer representing length
    // store row in records struct made up of a char vector and an integer size.
}

void CSVReader::WriteToFile(const std::string& str, std::ofstream& file) {
    // should write a record with its length concatenated to the beginning.
    std::size_t size = str.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file.write(str.c_str(), size);
}

std::pair<std::size_t, std::string> CSVReader::ReadFromFile(std::ifstream& file) {
    // reads the record length to determine offset.
    // watch out fo errors caused by over, or under reading
        // ie. make sure the length of the "length indicator" itself is accounted for
    std::size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::string str;
    str.resize(size);
    file.read(&str[0], size);
    //return str;
    return std::make_pair(size, str);
}

//HeaderRecord CSVReader::GenerateHeaderRecord() {
//    HeaderRecord header;
//    // Initialize header fields
//    // may be
//    return header;
//

bool CSVReader::BuildDataFile(const std::string& sourceFile1, const std::string& sourceFile2, const std::string& destinationFile) {
    // Implementation for BuildDataFile
    // after header record is built use data to define and create file.
    std::ifstream file1("header.txt",std::ios::binary);
    std::ifstream file2("output.txt",std::ios::binary);
    std::ofstream destFile("combined_file.txt",std::ios::binary);

    if (!file1.is_open() || !file2.is_open() || !destFile.is_open()) {
        std::cerr << "Failed to open one or more files." << std::endl;
        return false;
    }

    destFile << file1.rdbuf() << file2.rdbuf();

    file1.close();
    file2.close();
    destFile.close();

    return true;
}

/**
 * @brief Closes the CSV file if it's open.
 * @pre None.
 * @post The CSV file is closed if it was open.
 */
void CSVReader::close() {
    if (ZipCSV.is_open()) {
        ZipCSV.close();
    }
}

CSVReader::~CSVReader(){}