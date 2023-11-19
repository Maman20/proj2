#include "HeaderRecord.h"

HeaderRecord::HeaderRecord(
        const std::string& fileName,
        int version,
        const std::string& sizeFormatType,
        const std::string& primaryKeyIndexFileName,
        int primaryKeyOrdinality
)
        : fileName(fileName),
          version(version),
          sizeFormatType(sizeFormatType),
          primaryKeyIndexFileName(primaryKeyIndexFileName),
          primaryKeyOrdinality(primaryKeyOrdinality) {
}

// Implement getter methods
const std::string& HeaderRecord::getFileName() const {
    return fileName;
}

int HeaderRecord::getVersion() const {
    return version;
}

int HeaderRecord::getHeaderSize() const {
    return headerSize;
}

std::string HeaderRecord::getRecordSizeBytes() const {
    return recordSizeBytes;
}

const std::string& HeaderRecord::getSizeFormatType() const {
    return sizeFormatType;
}

const std::string& HeaderRecord::getPrimaryKeyIndexFileName() const {
    return primaryKeyIndexFileName;
}

int HeaderRecord::getRecordCount() const {
    return recordCount;
}

int HeaderRecord::getFieldsPerRecord() const {
    return fieldsPerRecord;
}

int HeaderRecord::getPrimaryKeyOrdinality() const {
    return primaryKeyOrdinality;
}

// Implement setter methods
void HeaderRecord::setFileName(const std::string& newFileName) {
    fileName = newFileName;
}

void HeaderRecord::setVersion(int newVersion) {
    version = newVersion;
}

void HeaderRecord::setHeaderSize() {
    headerSize = sizeof(*this);
}

void HeaderRecord::setRecordSizeBytes(std::string newRecordSizeBytes) {
    recordSizeBytes = newRecordSizeBytes;
}

void HeaderRecord::setSizeFormatType(const std::string& newSizeFormatType) {
    sizeFormatType = newSizeFormatType;
}

void HeaderRecord::setPrimaryKeyIndexFileName(const std::string& newPrimaryKeyIndexFileName) {
    primaryKeyIndexFileName = newPrimaryKeyIndexFileName;
}

void HeaderRecord::setRecordCount(int newRecordCount) {
    recordCount = newRecordCount;
}

void HeaderRecord::setFieldsPerRecord(int newFieldsPerRecord) {
    fieldsPerRecord = newFieldsPerRecord;
}

void HeaderRecord::setPrimaryKeyOrdinality(int newPrimaryKeyOrdinality) {
    primaryKeyOrdinality = newPrimaryKeyOrdinality;
}
