#include "CConfigFile.hpp"

#include <fstream>
#include <sstream>

using namespace std;

CConfigFile::CConfigFile(TConfig * config)
: CFile(config) {
}

CConfigFile::~CConfigFile() 
{}

void CConfigFile::loadFile()
{
    ifstream fs (FILENAME);
    if (!fs.good() || !fs.is_open() || !fs) {
        fs.close();
        throw "Error in opening config file.";
    }
    string line;
    char delimiter;
    string type;
    int val;
    uint32_t validator = 0;
    while (getline(fs, line)) {
        istringstream iss(line);
        if (!(iss >> type >> delimiter >> val) || delimiter != ':' || val < 0) {
            fs.close();
            throw "Error while reading config file.";
        }

        // Don't judge me, the due date was near when I wrote this...
        if (type == "startingMoney") {
            m_config->m_startingMoney = val;
            validator = validator | 0b0000000000000000000000001;
        } else if (type == "stockPrice") {
            m_config->m_stockPrice = val;
            validator = validator | 0b0000000000000000000000010;
        } else if (type == "stockAmount") {
            m_config->m_stockAmount = val;
            validator = validator | 0b0000000000000000000000100;
        } else if (type == "masksPrice") {
            m_config->m_masksPrice = val;
            validator = validator | 0b0000000000000000000001000;
        } else if (type == "masksAmount") {
            m_config->m_masksAmount = val;
            validator = validator | 0b0000000000000000000010000;
        } else if (type == "residentialCitizensAmount") {
            m_config->m_residentialCitizensAmount = val;
            validator = validator | 0b0000000000000000000100000;
        } else if (type == "residentialPrice") {
            m_config->m_residentialPrice = val;
            validator = validator | 0b0000000000000000001000000;
        } else if (type == "hospitalPrice") {
            m_config->m_hospitalPrice = val;
            validator = validator | 0b0000000000000000010000000;
        } else if (type == "hospitalMaxPatients") {
            m_config->m_hospitalMaxPatients = val;
            validator = validator | 0b0000000000000000100000000;
        } else if (type == "hospitalMaxParientsPrice") {
            m_config->m_hospitalMaxParientsPrice = val;
            validator = validator | 0b0000000000000001000000000;
        } else if (type == "businessPrice") {
            m_config->m_businessPrice = val;
            validator = validator | 0b0000000000000010000000000;
        } else if (type == "businessMaxTaxpayers") {
            m_config->m_businessMaxTaxpayers = val;
            validator = validator | 0b0000000000000100000000000;
        } else if (type == "businessTaxes") {
            m_config->m_businessTaxes = val;
            validator = validator | 0b0000000000001000000000000;
        } else if (type == "universityPrice") {
            m_config->m_universityPrice = val;
            validator = validator | 0b0000000000010000000000000;
        } else if (type == "universityMaximumStudents") {
            m_config->m_universityMaximumStudents = val;
            validator = validator | 0b0000000000100000000000000;
        } else if (type == "laboratoryPrice") {
            m_config->m_laboratoryPrice = val;
            validator = validator | 0b0000000001000000000000000;
        } else if (type == "virusR") {
            m_config->m_virusR = val;
            validator = validator | 0b0000000010000000000000000;
        } else if (type == "virusKillTime") {
            m_config->m_virusKillTime = val;
            validator = validator | 0b0000000100000000000000000;
        } else if (type == "virusCountDown") {
            m_config->m_virusCountDown = val;
            validator = validator | 0b0000001000000000000000000;
        } else if (type == "healthCarePrice") {
            m_config->m_healthCarePrice = val;
            validator = validator | 0b0000010000000000000000000;
        } else if (type == "sciencePrice") {
            m_config->m_sciencePrice = val;
            validator = validator | 0b0000100000000000000000000;
        } else if (type == "graduationTime") {
            m_config->m_graduationTime = val;
            validator = validator | 0b0001000000000000000000000;
        } else if (type == "vaccineDevelopmentSpeed") {
            m_config->m_vaccineDevelopmentSpeed = val;
            validator = validator | 0b0010000000000000000000000;
        } else {
            fs.close();
            throw "Unknown configuration detected in config file.";
        }
    }
    fs.close();
    if (validator != 0b0011111111111111111111111) {
        throw "Some configurations are missing from the config file.";
    }
}