/**
 * @file PrimaryKeyIndex.h
 * @callergraph
 * @callgraph
 * @author Fabian MullerDahlberg
 * @brief Declarations for class PrimaryKeyIndex
 * @see PrimaryKeyIndex.cpp for the implementation of these functions.
 * @details
 * This file declares the class PrimaryKeyIndex, which provides functionality to manage and operate on a primary key index.
 * The class includes member functions for building, reading, writing, searching, and unpacking the primary key index.
 *
 * Assumptions:
 * - The file used for indexing contains valid data.
 * - The primary key index uses a mapping between a string (as the key) and a stream position.
 * - Record data can be unpacked for display purposes using the provided methods.
 */

#ifndef ZIPCODES_PRIMARYKEYINDEX_H
#define ZIPCODES_PRIMARYKEYINDEX_H

#include <string>
#include <map> // For using std::map or std::unordered_map

/**
 * @brief Represents the Primary Key Index functionality.
 * This class provides methods for building, reading, writing, searching, and unpacking a primary key index.
 */
class PrimaryKeyIndex {
public:
    /**
     * @brief Constructor to initialize the PrimaryKeyIndex.
     * @pre None.
     * @post The PrimaryKeyIndex object is constructed.
     */
    PrimaryKeyIndex();

    /**
     * @brief Builds the primary key index.
     * @param filename Name of the file to build the index from.
     * @return A map representing the primary key index.
     * @pre The file with the given filename exists and contains valid data.
     * @post The primary key index is built and returned.
     */
    std::map<std::string, std::streampos> BuildIndex(std::string filename);

    /**
     * @brief Reads the primary key index from a file.
     * @param fileName Name of the file to read the index from.
     * @return A map representing the primary key index.
     * @pre The file with the given filename exists and contains a valid index.
     * @post The primary key index is read and returned.
     */
    std::map<std::string, std::streampos> ReadIndex(const std::string& fileName);

    /**
     * @brief Writes the primary key index to a file.
     * @param primaryKeyIndex The primary key index to write.
     * @pre None.
     * @post The primary key index is written to a file.
     */
    void WriteIndex(const std::map<std::string, std::streampos> primaryKeyIndex);

    /**
     * @brief Searches for a record in the index using a primary key.
     * @param recordIndex The map of records to search within.
     * @param filename The name of the file containing the primary key index.
     * @return True if the record is found, otherwise false.
     * @pre The file with the given filename exists and contains a valid index.
     * @post None.
     */
    bool SearchIndex(const std::map<std::string, std::string> recordIndex, std::string filename);

    /**
     * @brief Unpacks and displays a record given its data.
     * @param recordData The data of the record to unpack and display.
     * @pre None.
     * @post The record data is unpacked and displayed.
     */
    void UnpackRecord(const std::string& recordData);

private:
    // Define the data structure for the primary key index
    //std::map<std::string, std::streampos> primaryKeyIndex; // You can use an unordered_map if preferred
};

#endif //ZIPCODES_PRIMARYKEYINDEX_H
