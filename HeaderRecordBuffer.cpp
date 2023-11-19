/**
 * @file HeaderRecordBuffer.cpp
 * @callergraph
 * @callgraph
 * @author Fabian MullerDahlberg & Chakong
 * @author (Comments by Chakong Lor)(Doxygen documentation by Chakong Lor)
 * @brief Definitions for class HeaderRecordBuffer
 * @see HeaderRecordBuffer.h for the implementation of these functions.
 * @details
 * This file defines the class HeaderRecordBuffer, which provides functionality to read and write header records for files.
 * The class includes member functions for writing, reading, and analyzing CSV files.
 *
 */
// Created by mulle on 10/11/2023.
//
// Edited by Lor on 10/14/2023

#include "HeaderRecordBuffer.h"
#include <fstream>
#include <iostream>
#include <bitset>
#include <exception>

/**
 * @brief Constructor definition
 * @param none N/A
 * @pre none
 * @post The ReadHeaderRecord object is constructed
 */
HeaderRecordBuffer::HeaderRecordBuffer() {
    // Constructor, initialize variables if necessary
    
}

/**
 * @brief Method to read file and store header record data
 * @param filename The name of the CSV file to open.
 * @pre The file must exist
 * @post The ReadHeaderRecord object is constructed and stored
 */
bool HeaderRecordBuffer::ReadHeaderRecord(const std::string& filename) {
    // Implement the code to read the header record from a file
    // Parse the fields and store them in the headerRecord struct
    // Return true if successful, false if there was an error

    // Method requirements:
    // 1. The file being read must be length indicated

        headerRecord.fileName = filename;
        std::ifstream file(filename);
        std::string header;
        std::string word = "";
        int count = 0;
        std::vector<std::string> vec;

        if (!file.is_open())
        {
            std::cout << "No such file";
            return false;
        }
        while(file >> word)
        {
            count++;
            if (count == 2)
            {
                vec = parser(word);
            }
            
            if (count == 5)
            {
                header = word;
            }
        }
        headerRecord.version = std::stoi(vec[1]);
        headerRecord.sizeFormatType = vec[3];
        headerRecord.recordCount = count;
        word = "";
        headerRecord.headerSize = lengthDecoder(header);
        for (int i = 3; i < header.length(); i++)
        {
            if (header[i] != ',' && header[i] != '\n')
            {
                word = word + header[i];
            }
            else
            {
                headerRecord.fieldNames.push_back(word);
                word = "";
            }
        }
        headerRecord.fieldNames.push_back(word);
        headerRecord.fieldsPerRecord = headerRecord.fieldNames.size();

    return true;
}

/**
 * @brief Method to write file
 * @param header HeaderRecord object with desired data
 * @pre None
 * @post A new file will be written and names according to header's filename
 */
bool HeaderRecordBuffer::WriteHeaderRecord( HeaderRecord& header, std::string& fields) {//
    // Implement the code to write the header record to a file
    // Write the fields of the header struct to the file
    // Return true if successful, false if there was an error

    // Method only outputs:
    // 1. headerSize
    // 2. sizeFormatType
    // 3. fieldsPerRecord
    // 4. fieldNames

    // Method only requires
    // the following to write:
    // 1. HeaderRecord object
    //    - filename
    //    - sizeFormatType {ASCII or binary}
    // 2. field names with comma separation (string)
    //    - ex: "Zip,Place,State...etc"

    try
    {
        if (header.headerSize == 0)
        {
            char c;
            std::string temp = "";
            int holder = 0;
            for (int i = 0; i < fields.size();i++)
            {
                c = fields[i];
                if (c != ',' && c != '\n')
                {
                    holder += sizeof(c);
                    temp = temp + c;
                }
                else if (c == ',' || c == '\n')
                {
                    header.fieldNames.push_back(temp);
                    temp = "";
                }
            }
            header.fieldNames.push_back(temp);
            header.headerSize = holder;
            header.fieldsPerRecord = header.fieldNames.size();
        }
        std::ofstream file(header.fileName);
        
        if (header.sizeFormatType == "ASCII")
        {
            file << "39filename,version,headersize,sizeFormatType" << std::endl;
            file << header.fileName.size() + sizeof(header.version) + sizeof(header.headerSize) + header.sizeFormatType.size()
            << header.fileName << "," << header.version << "," << header.headerSize <<"," << header.sizeFormatType << std::endl;
            file << 26 << "recordCount,fieldsPerRecord" << std::endl;
            file << sizeof(int) + sizeof(int)<<header.recordCount << ","<<header.fieldsPerRecord << std::endl;
            file << header.headerSize;
        }
        if (header.sizeFormatType == "binary")
        {
            file << std::bitset<8>(39).to_string() << "filename,version,headersize,sizeFormatType" << std::endl;
            file << std::bitset<8>(header.fileName.size() + sizeof(header.version) + sizeof(header.headerSize) + header.sizeFormatType.size())
            << header.fileName << "," << header.version << "," << header.headerSize <<"," << header.sizeFormatType << std::endl;
            file << std::bitset<8>(26) << "recordCount,fieldsPerRecord" << std::endl;
            file << std::bitset<8>(sizeof(int) + sizeof(int))<<header.recordCount<< "," << header.fieldsPerRecord << std::endl;
            std::string byte = std::bitset<32>(header.headerSize).to_string();
            std::string temp = "";
            int coolInteger = 0;
            for (int i =0; i < byte.size(); i++)
            {
                temp = temp + byte[i];
                if (i == 7 || i == 15 || i == 23)
                {
                    temp = "";
                }
            }
            byte = temp;
            file << byte;
        }
        for (int i = 0; i < header.fieldNames.size();i++)
        {
            if (i == header.fieldNames.size() - 1)
            {
                file << header.fieldNames[i] << '\n';
            }
            else
            {
                file << header.fieldNames[i] << ",";
            }
        }
        throw std::runtime_error("");
    }
    catch(...)
    {
        return false;
    }
    return true;
}

/**
 * @brief Method to get headerRecord object headerRecord
 * @param none N/A
 * @pre None.
 * @post headerRecord struct is returned
 */
HeaderRecord HeaderRecordBuffer::GetHeaderRecord() const {
    return headerRecord;
}

/**
 * @brief Method to set headerRecord
 * @param header HeaderRecord object made with desired data
 * @pre None
 * @post headerRecord now has the same values as header
 */
void HeaderRecordBuffer::SetHeaderRecord(const HeaderRecord& header) {
    headerRecord = header;
}

/**
* @brief Method to destroy buffer
 * @param None N/A
 * @pre None
 * @post The ReadHeaderRecordBuffer object is destroyed
 */
HeaderRecordBuffer::~HeaderRecordBuffer() {
    // Destructor, perform cleanup if necessary
}

/**
 * @brief Method to format length indicators
 * @param header comma separated string
 * @pre None
 * @post integer is returned for record size
 */
int HeaderRecordBuffer::lengthDecoder(std::string header)
{
    std::string temp = "";
    int integer = 0;
    bool binflag = true;
    for (int i = 0; i < header.size(); i++)
    {
        if (isdigit(header[i]))
        {
            temp = temp + header[i];
            
        }
        if ((header[i] != '0' && header[i] != '1') && isdigit(header[i]))
        {
            binflag = false;
        }
    }
    
    if (binflag == true)
    {
        //std::cout << temp << std::endl;
        headerRecord.sizeFormatType = "binary";
        integer = std::stoi(temp,0,2);
    }
    if (!binflag)
    {
        
        headerRecord.sizeFormatType = "ASCII";
        integer = std::stoi(temp);
    }
    return integer;
}

/**
* @brief Method to parse record
 * @param s comma separated string object
 * @pre The file must exist
 * @post a vector of the comma separated values inside vector
 */
std::vector<std::string> HeaderRecordBuffer::parser(std::string s)
{
    std::string temp = "";
    std::vector<std::string> v;

    for (int i = 0;i < s.size(); i++)
    {
        if(s[i] == ',' || s[i] == '\n')
        {
            v.push_back(temp);
            temp = "";
        }
        else if (s[i] != ',')
        {
            temp = temp + s[i];
        }
    }
    v.push_back(temp);
    return v;
}