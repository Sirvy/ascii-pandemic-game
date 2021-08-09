#include "CBusiness.hpp"

#include <sstream>

using namespace std;

CBusiness::CBusiness(const string & view, unsigned maxTaxpayers, unsigned taxes, unsigned masksPrice, unsigned masksAmount)
: CCell(view),
  m_maxTaxPayers(maxTaxpayers),
  m_taxes(taxes),
  m_masksPrice(masksPrice),
  m_masksAmount(masksAmount) {
    m_options = vector<TMenu>{
        TMenu(2, 2, "Buy 100 masks [" + to_string(masksPrice) + "/" + to_string(masksAmount) + "]", OPTION_BUY_MASKS)
    };
}

string CBusiness::getSaveData() const 
{
    return "business : " 
        + to_string(m_maxTaxPayers) + " : " 
        + to_string(m_taxPayers.size());
}

void CBusiness::loadSaveData(const std::string & data, CStatHandler * stats)
{
    istringstream iss(data);
    string type;
    unsigned maxTaxPayers, taxPayers;
    char delimiter;
    if (!(iss >> type >> delimiter >> maxTaxPayers >> delimiter >> taxPayers)) {
        throw "Error in reading Business cell.";
    }

    m_maxTaxPayers = maxTaxPayers;
    for (auto it = stats->m_graduates.begin(); it != stats->m_graduates.end() && m_taxPayers.size() < taxPayers; ++it) {
        if ((*it)->getProfession() == CPerson::BUSINESSMAN && !(*it)->isHired()) {
            m_taxPayers.push_back(*it);
            (*it)->setHired(true);
            stats->m_graduates.erase(it--);
        }
    }
    if (m_taxPayers.size() != taxPayers) {
        throw "Business building's number of workers doesn't match.";
    }
}

void CBusiness::update(CStatHandler & stats)
{
    if (!stats.m_businessClosed && !stats.m_lockdown) {
        if (m_taxPayers.size() < m_maxTaxPayers) {
            hireNewEmployee(stats);
        }
        payTaxes(stats.m_money);
    }
    removeDeadEmployee(stats);
}

vector<TMenu> CBusiness::getOptions() const 
{
    return m_options;
}

string CBusiness::getInfo() const
{
    return "Business, max workers: " + to_string(m_maxTaxPayers) + ", current workers: " + to_string(m_taxPayers.size());
}

void CBusiness::proceedOptionClicked(int option, CStatHandler & stats) 
{
    if (option == OPTION_BUY_MASKS) {
        if (stats.m_money < m_masksPrice)
            throw "Not enough money to buy more masks.";
        stats.m_masks += m_masksAmount;
        stats.m_money -= m_masksPrice;
    }
}

void CBusiness::payTaxes(unsigned & statsMoney) 
{
    statsMoney += m_taxes * m_taxPayers.size() + m_taxes;
}

void CBusiness::hireNewEmployee(CStatHandler & stats) 
{
    for (auto it = stats.m_graduates.begin(); it != stats.m_graduates.end(); ++it) {
        if ((*it)->getProfession() == CPerson::EProfession::BUSINESSMAN && (*it)->isHealthy()) {
            stats.m_businessmanCnt++;
            m_taxPayers.push_back(*it);
            (*it)->setHired(true);
            stats.m_graduates.erase(it--);
            break;
        }
    }
}

void CBusiness::removeDeadEmployee(CStatHandler & stats)
{
    for (auto it = m_taxPayers.begin(); it != m_taxPayers.end(); ++it) {
        if ((*it)->isIsolated() || (*it)->isDead()) {
            (*it)->setHired(false);
            stats.m_businessmanCnt--;
            m_taxPayers.erase(it--);
        }
    }
}