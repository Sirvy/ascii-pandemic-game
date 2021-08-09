#include "CGameFile.hpp"

#include <fstream>
#include <sstream>
#include "CCell.hpp"

using namespace std;

CGameFile::CGameFile(CMap * map, CStatHandler * stats, TConfig * config)
: CFile(config),
  m_map(map),
  m_stats(stats) {
}

CGameFile::~CGameFile(){}

void CGameFile::loadFile() 
{
    ifstream fin(FILENAME);  
    if (!fin.good() || !fin.is_open() || !fin) {
        fin.close();
        throw "Couldn't open file for loading.";
    }

    string line;
    string type;
    char delimiter;
    int val;
    while (getline(fin, line)) {
        istringstream iss(line);
        if (!(iss >> type >> delimiter >> val) || delimiter != ':' || val < 0) {
            fin.close();
            throw "Error while reading save file.";
        }
        if (type == "money") m_stats->m_money = val;
        else if (type == "epidemic") m_stats->m_epidemic = val;
        else if (type == "stocks") m_stats->m_stocks = val;
        else if (type == "masks") m_stats->m_masks = val;
        else if (type == "r") m_stats->m_virusR = val;
        else if (type == "actionMasks") m_stats->m_mandatoryMasks = (val == 1 ? true : false);
        else if (type == "actionSchools") m_stats->m_schoolsClosed = (val == 1 ? true : false);
        else if (type == "actionBusiness") m_stats->m_businessClosed = (val == 1 ? true : false);
        else if (type == "actionLockdown") m_stats->m_lockdown = (val == 1 ? true : false);
        else if (type == "invHealthcare") m_stats->m_investmentIntoHealthcare = val;
        else if (type == "invScience") m_stats->m_investmentIntoScience = val;
        else if (type == "invBusiness") m_stats->m_investmentIntoBusiness = val;
        else if (type == "citizenCnt") m_stats->m_citizenCnt = val;
        else if (type == "studentCnt") m_stats->m_studentCnt = val;
        else if (type == "doctorCnt") m_stats->m_doctorCnt = val;
        else if (type == "scientistCnt") m_stats->m_scientistCnt = val;
        else if (type == "businessmanCnt") m_stats->m_businessmanCnt = val;
        else if (type == "infected") m_stats->m_infected = val;
        else if (type == "isolated") m_stats->m_isolated = val;
        else if (type == "deathsByVirus") m_stats->m_deathsByVirus = val;
        else if (type == "deathsByOther") m_stats->m_deathsByOther = val;
        else if (type == "map") break;
        else {
            fin.close();
            throw "Detected unknown data in saved file.";
        }        
    }

    m_stats->fillCitizens();

    getline(fin, line);
    int rows, columns;
    istringstream iss(line);
    if (!(iss >> rows >> delimiter >> columns) || delimiter != ':' || rows <= 0 || columns <= 0) {
        fin.close();
        throw "Couldn't properly read the map size from the save file.";
    }
    m_map->newSize(rows, columns);
    try {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                getline(fin, line);
                m_map->loadCell(i, j, line, m_stats);
            }
        }
    } catch (const char * e) {
        throw e;
    }
}

void CGameFile::saveFile()
{
    ofstream fout(FILENAME);  
    if (!fout.good() || !fout.is_open() || !fout) {
        fout.close();
        throw "Couldn't open file for saving.";
    }

    fout << "money : " << m_stats->m_money << "\n";
    fout << "epidemic : " << m_stats->m_epidemic << "\n";
    fout << "stocks : " << m_stats->m_stocks << "\n";
    fout << "masks : " << m_stats->m_masks << "\n";
    fout << "r : " << m_stats->m_virusR << "\n";
    fout << "actionMasks : " << (m_stats->m_mandatoryMasks ? 1 : 0) << "\n";
    fout << "actionSchools : " << (m_stats->m_schoolsClosed ? 1 : 0) << "\n";
    fout << "actionBusiness : " << (m_stats->m_businessClosed ? 1 : 0) << "\n";
    fout << "actionLockdown : " << (m_stats->m_lockdown ? 1 : 0) << "\n";
    fout << "invHealthcare : " << m_stats->m_investmentIntoHealthcare << "\n";
    fout << "invScience : " << m_stats->m_investmentIntoScience << "\n";
    fout << "invBusiness : " << m_stats->m_investmentIntoBusiness << "\n";
    
    fout << "citizenCnt : " <<  m_stats->m_citizenCnt << "\n";
    fout << "studentCnt : " <<  m_stats->m_studentCnt << "\n";
    fout << "doctorCnt : " <<  m_stats->m_doctorCnt << "\n";
    fout << "scientistCnt : " <<  m_stats->m_scientistCnt << "\n";
    fout << "businessmanCnt : " <<  m_stats->m_businessmanCnt << "\n";
    fout << "infected : " <<  m_stats->m_infected << "\n";
    fout << "isolated : " <<  m_stats->m_isolated << "\n";
    fout << "deathsByVirus : " <<  m_stats->m_deathsByVirus << "\n";
    fout << "deathsByOther : " <<  m_stats->m_deathsByOther << "\n";

    fout << "map : 0\n";
    fout << m_map->getRows() << " : " << m_map->getColumns() << "\n";
    vector<vector<CCell*>> cells = m_map->getCells();
    for (int i = 0; i < m_map->getRows(); i++) {
        for (int j = 0; j < m_map->getColumns(); j++) {
            fout << cells.at(i).at(j)->getSaveData() << "\n";
        }
    }

    fout.close();

}