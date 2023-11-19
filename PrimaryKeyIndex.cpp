/**
 * @file PrimaryKeyIndex.cpp
 * @author Fabian MullerDahlberg
 * @brief Member function definitions for the PrimaryKeyIndex class.
 * @see PrimaryKeyIndex.h for declaration.
 */

#include "PrimaryKeyIndex.h"
#include "CSVReader.h"
#include <fstream>
#include <iostream>

/**
 * @brief Default constructor for PrimaryKeyIndex.
 * @details Initializes any member variables if necessary.
 */
PrimaryKeyIndex::PrimaryKeyIndex() {
    // Constructor: You can initialize any member variables here.
}

/**
 * @brief Builds a primary key index based on a given file.
 * @param filename The name of the file to be indexed.
 * @return A map representing the primary key index.
 */
std::map<std::string, std::streampos> PrimaryKeyIndex::BuildIndex(std::string filename) {
    std::ifstream inputFile(filename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Failed to open input file." << std::endl;
        return std::map<std::string, std::streampos>();;
    }

    std::map<std::string, std::streampos> primaryKeyIndex;

    while (inputFile) {
        std::pair<std::size_t, std::string> record = CSVReader::ReadFromFile(inputFile);
        std::size_t size = record.first;
        std::string data = record.second;
        if (size == 0) {
            break; // End of file reached
        }

        std::vector<std::string> parsedRecord = CSVReader::ParseLine(data);

        if (!parsedRecord.empty()) {
            std::string key = parsedRecord[0];
            std::streampos currentRecordPos = inputFile.tellg();
            primaryKeyIndex[key] = currentRecordPos;
        }
    }
    return primaryKeyIndex;
}

/**
 * @brief Reads a primary key index from a given file.
 * @param fileName The name of the index file.
 * @return A map representing the primary key index.
 */
std::map<std::string, std::streampos> PrimaryKeyIndex::ReadIndex(const std::string& fileName) {
    std::map<std::string, std::streampos> primaryKeyIndex;

    // Open the file for reading
    std::ifstream indexFile(fileName);
    if (indexFile.is_open()) {
        std::string line;
        while (std::getline(indexFile, line)) {
            std::string key;
            std::streampos value;

            // Split the line into key and value using a space
            size_t spacePos = line.find(' ');
            if (spacePos != std::string::npos) {
                key = line.substr(0, spacePos);
                value = std::stoll(line.substr(spacePos + 1));
                primaryKeyIndex[key] = value;
            }
        }
        // Close the file
        indexFile.close();
        std::cout << "Opened the index file for reading." << std::endl;
        return primaryKeyIndex;
    } else {
        std::cerr << "Error: Failed to open the index file for reading." << std::endl;
    }
}

/**
 * @brief Writes the primary key index to a file.
 * @param primaryKeyIndex A map representing the primary key index.
 * @pre The map primaryKeyIndex is correctly populated.
 * @post The index is written to the file "KeyIndex.txt".
 */
void PrimaryKeyIndex::WriteIndex(const std::map<std::string, std::streampos> primaryKeyIndex) {
    // Implement the logic to write the primary key index to a file
    // Open the file for writing
    std::ofstream indexFile("KeyIndex.txt");
    if (indexFile.is_open()) {
        // Iterate through the map and write key-value pairs to the file
        for (const auto& pair : primaryKeyIndex) {
            indexFile << pair.first << " " << pair.second << std::endl;
        }
        // Close the file
        indexFile.close();
        std::cout << "Index written to index.txt" << std::endl;
    } else {
        std::cerr << "Error: Failed to open the index file for writing." << std::endl;
    }
}

/**
 * @brief Searches for a record in the primary key index.
 * @param recordIndex A map representing the primary key index.
 * @param filename The name of the file where the records are stored.
 * @return True if the record is found, false otherwise.
 */
bool PrimaryKeyIndex::SearchIndex(const std::map<std::string,std::string> recordIndex,std::string filename) {
    std::ifstream inputFile(filename, std::ios::binary);
    // Implement the logic to search for a record in the index
    // Implement the logic to read the primary key index from a file
    std::string targetRecordId = "zipCode"; // The ID of the record you want to access
    //std::streampos targetPosition = recordIndex[targetRecordId];

// Move to the specified position in the file, accounting for the length indicator
    //inputFile.seekg(targetPosition + lengthIndicatorSize);

// Read the record at the specified position
// Read the length indicator
    std::size_t lengthIndicator;
    //inputFile.read(reinterpret_cast<char*>(&lengthIndicator), lengthIndicatorSize);

// Read the record data based on the length indicator
    std::string recordData(lengthIndicator, '\0');
    inputFile.read(&recordData[0], lengthIndicator);
    return false; // Return true if the record is found; false otherwise
}

/**
 * @brief Unpacks and displays a given record.
 * @param recordData The record data as a string.
 * @pre The recordData string is correctly formatted.
 * @post The record is unpacked and displayed to the console.
 */
void PrimaryKeyIndex::UnpackRecord(const std::string& recordData) {
    // Implement the logic to unpack and display a record
}
