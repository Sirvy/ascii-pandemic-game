#include "CResidential.hpp"

#include <sstream>
#include "../CPerson.hpp"


using namespace std;

CResidential::CResidential(const std::string & view, unsigned citizensAmount, unsigned stockPrice, unsigned stockAmount)
: CCell(view),
  m_citizensAmount(citizensAmount),
  m_stockPrice(stockPrice),
  m_stockAmount(stockAmount),
  m_alreadyMaxed(false) {
    m_options = std::vector<TMenu>{
        TMenu(2, 2, "Invest into stocks [" + to_string(stockPrice) + "/" + to_string(stockAmount) + "]", OPTION_INVEST_INTO_STOCKS)
    };
}

string CResidential::getSaveData() const 
{
    return "residential : " 
        + to_string(m_citizens.size()) + " : "
        + to_string(m_alreadyMaxed ? 1 : 0);
}

void CResidential::loadSaveData(const std::string & data, CStatHandler * stats)
{
    istringstream iss(data);
    string type;
    unsigned citizensCount;
    bool maxAlready;
    char delimiter;
    if (!(iss >> type >> delimiter >> citizensCount >> delimiter >> maxAlready)) {
        throw "Error in reading Residential cell.";
    }

    m_alreadyMaxed = maxAlready;

    for (auto it = stats->m_citizens.begin(); it != stats->m_citizens.end() && m_citizens.size() < citizensCount; ++it) {
        if (!(*it)->hasHome()) {
            m_citizens.push_back(*it);
            (*it)->setHome(true);
        }
    }
    if (m_citizens.size() != citizensCount) {
        throw "Residential building's number of citizens doesn't match.";
    }
}

void CResidential::update(CStatHandler & stats)
{
    if (m_citizens.size() < m_citizensAmount && !m_alreadyMaxed) {
        stats.m_citizenCnt++;
        stats.m_citizens.push_back(new CPerson());
        m_citizens.push_back(stats.m_citizens.back());
    } else {
        m_alreadyMaxed = true;
    }

    if (stats.m_lockdown)
        decreaseStocks(stats);
        
    removeDeadCitizens();
}

std::vector<TMenu> CResidential::getOptions() const 
{
    return m_options;
}

string CResidential::getInfo() const
{
    return "Residential, citizens: " + to_string(m_citizens.size());
}

void CResidential::proceedOptionClicked(int option, CStatHandler & stats) 
{
    if (option == OPTION_INVEST_INTO_STOCKS) {
        if (stats.m_money < m_stockPrice)
            throw "Not enough money to buy more stocks";
        stats.m_stocks += m_stockAmount;
        stats.m_money -= m_stockPrice;
    }
}

void CResidential::decreaseStocks(CStatHandler & stats)
{
    if (stats.m_stocks > 0)
        stats.m_stocks--;
}

void CResidential::removeDeadCitizens()
{
    for (auto it = m_citizens.begin(); it != m_citizens.end(); ++it) {
        if ((*it)->isDead()) {
            m_citizens.erase(it--);
        }
    }
}