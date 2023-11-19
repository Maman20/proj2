/**
 * @file HeaderRecordBuffer.h
 * @callergraph
 * @callgraph
 * @author Fabian MullerDahlberg & Chakong
 * @author (Comments by Chakong Lor)(Doxygen documentation by Chakong Lor)
 * @brief Declarations for class HeaderRecordBuffer
 * @see HeaderRecordBuffer.cpp for the implementation of these functions.
 * @details
 * This file declares the class HeaderRecordBuffer, which provides functionality to read and write header records for files.
 * The class includes member functions for writing, reading, and analyzing CSV files.
 *
 */
#ifndef ZIPCODES_HEADERRECORDBUFFER_H
#define ZIPCODES_HEADERRECORDBUFFER_H

#include <string>
#include <fstream>
#include "HeaderRecord.h"

class HeaderRecordBuffer {
public:
    /**
     * @brief Constructor for the HeaderRecordBuffer class
     * @param none N/A
     * @pre none
     * @post The ReadHeaderRecord object is constructed
     */
    HeaderRecordBuffer();

    /**
     * @brief destructor
     * @param none N/A
     * @pre None.
     * @post The ReadHeaderRecord object is destroyed
     */
    ~HeaderRecordBuffer();

    // Method to read the header record from a file
    /**
     * @brief Method to read file and store header record data
     * @param filename The name of the CSV file to open.
     * @pre The file must exist
     * @post The ReadHeaderRecord object is constructed
     */
    bool ReadHeaderRecord(const std::string& filename);

    // Method to write a header record to a file
    /**
     * @brief Method to write a header record to a file.
     * @param header A headerRecord object
     * @param fields The fields of the file
     * @pre None.
     * @post A file is created with length indicated records in bytes
    */
    bool WriteHeaderRecord( HeaderRecord& header,std::string& fields);

    // Accessor methods to get and set the header record
    /**
     * @brief Method to get the HeaderRecord object within the HeaderRecordBuffer
     * @param none N/A
     * @pre none
     * @post HeaderRecord should be returned
     */
    HeaderRecord GetHeaderRecord() const;

    /**
     * @brief method to grab data and set to the HeaderRecordBuffer
     * @param header HeaderRecord object made by some user or from file
     * @pre None.
     * @post headerRecord inside HeaderRecordBuffer object should contain
     * contain the data of the HeaderRecord object
     */
    void SetHeaderRecord(const HeaderRecord& header);

private:
    HeaderRecord headerRecord;

    //Method to change ASCII to integer for header size for reading
    //Method changes binary to integer for header size for reading
    /**
     * @brief Method to format the sie format type
     * @param header a comma separated string for field names
     * @pre None.
     * @post an integer will be returned
     */
    int lengthDecoder(std::string header);

    /**
     * @brief Method for parsing the header record
     * @param s A comma separated string
     * @pre None.
     * @post a vector is returned with all comma separated word in their own spot
     */
    std::vector<std::string> parser(std::string s);

};


#endif //ZIPCODES_HEADERRECORDBUFFER_H
