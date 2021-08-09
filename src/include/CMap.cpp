#include "CMap.hpp"

#include <iostream>
#include <sstream>

using namespace std;

CMap::CMap(TConfig * config, int rows, int columns) 
: m_config(config),
  m_rows(rows), 
  m_columns(columns) {
    if (rows > MAX_ROWS || columns > MAX_COLUMNS) {
        throw "Map is too large!";
    }
    if (rows < 1 || columns < 1) {
        throw "Map is too small!";
    }
    for (int i = 0; i < m_rows; i++) {
        vector<CCell*> tmp;
        for (int j = 0; j < m_columns; j++) {
            tmp.push_back(new CEmpty(m_config->m_emptyCellView));
        }
        m_cells.push_back(tmp);
    }
}

CMap::~CMap() 
{
    for (auto & it_r : m_cells) {
        for (auto & it_c : it_r) {
            delete it_c;
        }
    }
}

int CMap::getRows() const {
    return m_rows;
}

int CMap::getColumns() const {
    return m_columns;
}

void CMap::newSize(int rows, int columns)
{
    if (rows > MAX_ROWS || columns > MAX_COLUMNS) {
        throw "Map is too large!";
    }
    if (rows < 1 || columns < 1) {
        throw "Map is too small!";
    }
    for (auto & it_r : m_cells) {
        for (auto & it_c : it_r) {
            delete it_c;
        }
    }
    m_cells.clear();

    m_rows = rows;
    m_columns = columns;
    for (int i = 0; i < m_rows; i++) {
        vector<CCell*> tmp;
        for (int j = 0; j < m_columns; j++) {
            tmp.push_back(new CEmpty(m_config->m_emptyCellView));
        }
        m_cells.push_back(tmp);
    }
}

void CMap::loadCell(int y, int x, const std::string & data, CStatHandler * stats)
{
    istringstream iss(data);
    string type;
    if (!(iss >> type)) {
        throw "Error detected while reading map from save file.";
    }
    if (type == "residential") convertToResidential(x, y);
    else if (type == "hospital") convertToHospital(x, y);
    else if (type == "university") convertToUniversity(x, y);
    else if (type == "business") convertToBusiness(x, y);
    else if (type == "lab") convertToLaboratory(x, y);
    else if (type == "empty") {}
    else 
        throw "Unknown building cell detected.";
    m_cells.at(y).at(x)->loadSaveData(data, stats);
}

vector<vector<CCell*>> CMap::getCells() 
{
    return m_cells;
}

void CMap::update(CStatHandler & stats) {
    for (auto & it_r : m_cells) {
        for (auto & it_c : it_r) {
            it_c->update(stats);
        }
    }
}

void CMap::convertToResidential(int x, int y)
{
    delete m_cells.at(y).at(x);
    m_cells.at(y).at(x) = new CResidential(
        m_config->m_residentailView,
        m_config->m_residentialCitizensAmount,
        m_config->m_stockPrice,
        m_config->m_stockAmount
    );
}

   
void CMap::convertToHospital(int x, int y)
{
    delete m_cells.at(y).at(x);
    m_cells.at(y).at(x) = new CHospital(
        m_config->m_hospitalView,
        m_config->m_hospitalMaxPatients, 
        m_config->m_hospitalMaxParientsPrice,
        m_config->m_healthCarePrice
    );
}

void CMap::convertToBusiness(int x, int y)
{
    delete m_cells.at(y).at(x);
    m_cells.at(y).at(x) = new CBusiness(
        m_config->m_businessView,
        m_config->m_businessMaxTaxpayers, 
        m_config->m_businessTaxes, 
        m_config->m_masksPrice, 
        m_config->m_masksAmount
    );
}

void CMap::convertToUniversity(int x, int y)
{
    delete m_cells.at(y).at(x);
    m_cells.at(y).at(x) = new CUniversity(
        m_config->m_universityView,
        m_config->m_universityMaximumStudents,
        m_config->m_graduationTime
    );
}

void CMap::convertToLaboratory(int x, int y)
{
    delete m_cells.at(y).at(x);
    m_cells.at(y).at(x) = new CLaboratory(
        m_config->m_laboratoryView,
        m_config->m_sciencePrice,
        m_config->m_vaccineDevelopmentSpeed
    );
}