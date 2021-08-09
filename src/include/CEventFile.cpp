#include "CEventFile.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

CEventFile::CEventFile(TConfig * config)
: CFile(config) {
}

CEventFile::~CEventFile() {}

void CEventFile::loadFile()
{
    ifstream fs (FILENAME);
    if (!fs.good() || !fs.is_open() || !fs) {
        fs.close();
        throw "Error in opening events file.";
    }
    string line;
    string type;
    unsigned time;
    unsigned val;
    char delimiter;
    while (getline(fs, line)) {
        istringstream iss(line);
        if (!(iss >> type >> delimiter >> val >> delimiter >> time)) {
            fs.close();
            throw "Error while reading events file.";
        }
        if (type == "infect") {
            m_config->m_events.push_back(TEvent(TEvent::EVENT_INFECTIONS, time, val));
        } else if (type == "r") {
            m_config->m_events.push_back(TEvent(TEvent::EVENT_R, time, val));
        } else {
            fs.close();
            throw "Unknown event detected.";
        }
    }
    fs.close();
}