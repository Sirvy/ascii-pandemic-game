#include "CLaboratory.hpp"

#include <cmath>
#include <sstream>
#include <algorithm>

using namespace std;

CLaboratory::CLaboratory(const string & view, unsigned sciencePrice, unsigned vaccineSpeed) 
: CCell(view),
  m_sciencePrice(sciencePrice),
  m_progress(0),
  m_vaccineSpeed(vaccineSpeed),
  m_failedAttempts(0),
  m_ctr(0) {
    m_options = vector<TMenu>{
        TMenu(2, 2, "Invest into science [" + to_string(m_sciencePrice) + "]", OPTION_INVEST_INTO_SCIENCE),
        TMenu(2, 4, "Invest into science [" + to_string(m_sciencePrice*10) + "]", OPTION_INVEST_INTO_SCIENCE2)
    };  
}

string CLaboratory::getSaveData() const 
{
    return "lab : " 
        + to_string(m_progress) + " : "
        + to_string(m_failedAttempts) + " : "
        + to_string(m_scientists.size());
}

void CLaboratory::loadSaveData(const std::string & data, CStatHandler * stats)
{
    istringstream iss(data);
    string type;
    unsigned progress, failedAttempts, scientistsCount;
    char delimiter;
    if (!(iss >> type >> delimiter >> progress >> delimiter >> failedAttempts >> delimiter >> scientistsCount)) {
        throw "Error in reading Laboratory cell.";
    }

    m_progress = progress;
    m_failedAttempts = failedAttempts;

    for (auto it = stats->m_graduates.begin(); it != stats->m_graduates.end() && m_scientists.size() < scientistsCount; ++it) {
        if ((*it)->getProfession() == CPerson::RESEARCHER && !(*it)->isHired()) {
            m_scientists.push_back(*it);
            (*it)->setHired(true);
            stats->m_graduates.erase(it--);
        }
    }
    if (m_scientists.size() != scientistsCount) {
        throw "Laboratory building's number of scientists doesn't match.";
    }
}

void CLaboratory::update(CStatHandler & stats)
{
    hireNewScientists(stats);
    m_ctr++;
    if (m_ctr >= (signed)(m_vaccineSpeed - m_scientists.size())) {
        m_ctr = 0;
        improveProgress(stats);
    }
    removeDeadEmployee(stats);
}

vector<TMenu> CLaboratory::getOptions() const 
{
    return m_options;
}

string CLaboratory::getInfo() const
{
    return "Laboratory, scientists: " + to_string(m_scientists.size()) + ", progress: " + to_string(m_progress) + "%, failed: " + to_string(m_failedAttempts);
}

void CLaboratory::proceedOptionClicked(int option, CStatHandler & stats) 
{
    if (option == OPTION_INVEST_INTO_SCIENCE) {
        if (stats.m_money < m_sciencePrice)
            throw "Not enough money to invest into science.";
        stats.m_investmentIntoScience += m_sciencePrice;
        stats.m_money -= m_sciencePrice;
    }
    if (option == OPTION_INVEST_INTO_SCIENCE2) {
        if (stats.m_money < m_sciencePrice*10)
            throw "Not enough money to invest into science.";
        stats.m_investmentIntoScience += m_sciencePrice*10;
        stats.m_money -= m_sciencePrice*10;
    }
}

void CLaboratory::hireNewScientists(CStatHandler & stats) 
{
    for (auto it = stats.m_graduates.begin(); it != stats.m_graduates.end(); ++it) {
        if ((*it)->getProfession() == CPerson::RESEARCHER && (*it)->isHealthy()) {
            stats.m_scientistCnt++;
            (*it)->setHired(true);
            m_scientists.push_back(*it);
            stats.m_graduates.erase(it--);
            break;
        }
    }
}

void CLaboratory::improveProgress(CStatHandler & stats)
{
    if (m_progress < 100)
        m_progress++;
    else { 
        m_progress = 0;

        if ((rand() % 100) <= (min((int)(log10(stats.m_investmentIntoScience)*log10(stats.m_investmentIntoScience)), 90))) {
            stats.m_vaccineFinished = true;
        } else {
            m_failedAttempts++;
        }
    }
}

void CLaboratory::removeDeadEmployee(CStatHandler & stats)
{
    for (auto it = m_scientists.begin(); it != m_scientists.end(); ++it) {
        if ((*it)->isIsolated() || (*it)->isDead()) {
            (*it)->setHired(false);
            m_scientists.erase(it--);
            stats.m_scientistCnt--;
        }
    }
}