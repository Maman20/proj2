#ifndef ZIPCODES_HEADERRECORD_H
#define ZIPCODES_HEADERRECORD_H

#include <string>
#include <vector>

class HeaderRecord {
public:
    std::vector<std::string> fieldNames;
    HeaderRecord(
            const std::string& fileName,
            int version,
            const std::string& sizeFormatType,
            const std::string& primaryKeyIndexFileName,
            int primaryKeyOrdinality
    );

    // Getter methods
    const std::string& getFileName() const;
    int getVersion() const;
    int getHeaderSize() const;
    std::string getRecordSizeBytes() const;
    const std::string& getSizeFormatType() const;
    const std::string& getPrimaryKeyIndexFileName() const;
    int getRecordCount() const;
    int getFieldsPerRecord() const;
    int getPrimaryKeyOrdinality() const;

    // Setter methods
    void setFileName(const std::string& newFileName);
    void setVersion(int newVersion);
    void setHeaderSize();
    void setRecordSizeBytes(std::string newRecordSizeBytes);
    void setSizeFormatType(const std::string& newSizeFormatType);
    void setPrimaryKeyIndexFileName(const std::string& newPrimaryKeyIndexFileName);
    void setRecordCount(int newRecordCount);
    void setFieldsPerRecord(int newFieldsPerRecord);
    void setPrimaryKeyOrdinality(int newPrimaryKeyOrdinality);


private:
    std::string fileName;
    int version;
    int headerSize;
    std::string recordSizeBytes = "variable";
    std::string sizeFormatType;
    std::string primaryKeyIndexFileName;
    int recordCount;
    int fieldsPerRecord;
    int primaryKeyOrdinality;

};

#endif //ZIPCODES_HEADERRECORD_H
