#include "CAssetsFile.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

CAssetsFile::CAssetsFile(TConfig * config)
: CFile(config) {
}

CAssetsFile::~CAssetsFile() 
{}

void CAssetsFile::loadFile()
{
    ifstream fs (FILENAME);
    if (!fs.good() || !fs.is_open() || !fs) {
        fs.close();
        throw "Error in opening assets file.";
    }
    string line;
    string type;
    string val;
    uint8_t validator = 0;
    while (getline(fs, line)) {
        istringstream iss(line);
        if (!getline(iss, type, ':') || !getline(iss, val, '"') || !getline(iss, val, '"') || val.length() != 3) {
            fs.close();
            throw "Error while reading assets file.";
        }
        if (type == "empty") {
            m_config->m_emptyCellView = val;
            validator = validator | 0b00000001;
        } else if (type == "residential") {
            m_config->m_residentailView = val;
            validator = validator | 0b00000010;
        } else if (type == "hospital") {
            m_config->m_hospitalView = val;
            validator = validator | 0b00000100;
        } else if (type == "business") {
            m_config->m_businessView = val;
            validator = validator | 0b00001000;
        } else if (type == "university") {
            m_config->m_universityView = val;
            validator = validator | 0b00010000;
        } else if (type == "laboratory") {
            m_config->m_laboratoryView = val;
            validator = validator | 0b00100000;
        } else {
            throw "Unknown building asset detected.";
            fs.close();
        }
    }
    fs.close();
    if (validator != 0b00111111)
        throw "Some buildings are missing from the assets file.";
}