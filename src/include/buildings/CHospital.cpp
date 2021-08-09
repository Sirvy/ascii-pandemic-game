#include "CHospital.hpp"

#include <sstream>

using namespace std;

CHospital::CHospital(const std::string & view, unsigned maxPatients, unsigned maxPatientsPrice, unsigned healthCarePrice) 
: CCell(view),
  m_maxPatients(maxPatients),
  m_maxPatientsPrice(maxPatientsPrice),
  m_healthCarePrice(healthCarePrice),
  m_ctr(0) {
    m_options = std::vector<TMenu>{
        TMenu(2, 2, "Invest into healthcare [" + to_string(healthCarePrice) + "]", OPTION_INVEST_INTO_HEALTHCARE),
        TMenu(2, 4, "Increase max patients capacity [" + to_string(maxPatientsPrice) + "]", OPTION_INCREASE_MAX_PATIENTS)
    };  
}

string CHospital::getSaveData() const 
{
    return "hospital : " 
        + to_string(m_maxPatients) + " : "
        + to_string(m_patients.size()) + " : "
        + to_string(m_doctors.size());
}

void CHospital::loadSaveData(const std::string & data, CStatHandler * stats)
{
    istringstream iss(data);
    string type;
    unsigned maxPatients, patientsCount, doctorsCount;
    char delimiter;
    if (!(iss >> type >> delimiter >> maxPatients >> delimiter >> patientsCount >> delimiter >> doctorsCount)) {
        throw "Error in reading Hospital cell.";
    }

    m_maxPatients = maxPatients;
    for (auto it = stats->m_graduates.begin(); it != stats->m_graduates.end() && m_doctors.size() < doctorsCount; ++it) {
        if ((*it)->getProfession() == CPerson::DOCTOR && !(*it)->isHired()) {
            m_doctors.push_back(*it);
            (*it)->setHired(true);
            stats->m_graduates.erase(it--);
        }
    }
    if (m_doctors.size() != doctorsCount) {
        throw "Hospital building's number of doctors doesn't match.";
    }
    
    while (!stats->m_toBeHospitalized.empty() && m_patients.size() < patientsCount) {
        CPerson * person = stats->m_toBeHospitalized.front();   
        stats->m_toBeHospitalized.pop();
        m_patients.push_back(person);
    }
    if (m_patients.size() != patientsCount) {
        throw "Hospital building's number of patients doesn't match.";
    }
}

void CHospital::update(CStatHandler & stats)
{
    removeDeadEmployee(stats);

    if (m_doctors.size() == 0) {
        removeSurplusPatients(stats);
    }
    
    if (m_doctors.size() < m_maxPatients) {
        hireNewEmployee(stats);
    }

    if (m_patients.size() < m_maxPatients && m_doctors.size() > 0) {
        receivePatients(stats);
    }

    if (m_ctr++ >= (m_maxPatients - m_doctors.size() + 10)) {
        curePatients(stats);
        m_ctr = 0;
    }
}

vector<TMenu> CHospital::getOptions() const 
{
    return m_options;
}

string CHospital::getInfo() const
{
    return "Hospital, capacity: " + to_string(m_maxPatients) + ", patients: " + to_string(m_patients.size()) + ", doctors: " + to_string(m_doctors.size());
}

void CHospital::proceedOptionClicked(int option, CStatHandler & stats) 
{
    if (option == OPTION_INVEST_INTO_HEALTHCARE) {
        if (stats.m_money < m_healthCarePrice)
            throw "Not enough money to invest into healthcare.";
        stats.m_investmentIntoHealthcare += m_healthCarePrice;
        stats.m_money -= m_healthCarePrice;
    }
    if (option == OPTION_INCREASE_MAX_PATIENTS) {
        if (stats.m_money < m_maxPatientsPrice)
            throw "Not enough money to increase max patients capacity.";
        m_maxPatients++;
        stats.m_money -= m_maxPatientsPrice;
    }
}

void CHospital::curePatients(CStatHandler & stats)
{
    if (!m_patients.empty()) {
        auto it = m_patients.begin();
        (*it)->setState(CPerson::HEALTHY);
        (*it)->setHired(false);
        (*it)->setStudent(false);
        if ((*it)->hasGraduated())
            stats.m_graduates.push_back(*it);
        m_patients.erase(it--);
        stats.m_infected--;
        stats.m_isolated--;
    }
}

void CHospital::receivePatients(CStatHandler & stats)
{
    if (!stats.m_toBeHospitalized.empty() && m_patients.size() < m_maxPatients) {
        CPerson * person = stats.m_toBeHospitalized.front();   
        stats.m_toBeHospitalized.pop();
        if (!person->isDead()) {
            m_patients.push_back(person);
            person->setState(CPerson::ISOLATED);
            stats.m_isolated++;
        }
    }
}

void CHospital::hireNewEmployee(CStatHandler & stats)
{
    for (auto it = stats.m_graduates.begin(); it != stats.m_graduates.end(); ++it) {
        if ((*it)->getProfession() == CPerson::DOCTOR && (*it)->isHealthy()) {
            (*it)->setHired(true);
            stats.m_doctorCnt++;
            m_doctors.push_back(*it);
            stats.m_graduates.erase(it--);
            break;
        }
    }
}

void CHospital::removeDeadEmployee(CStatHandler & stats)
{
    for (auto it = m_doctors.begin(); it != m_doctors.end(); ++it) {
        if ((*it)->isIsolated() || (*it)->isDead()) {
            (*it)->setHired(false);
            m_doctors.erase(it--);
            stats.m_doctorCnt--;
        }
    }
}

void CHospital::removeSurplusPatients(CStatHandler & stats) 
{
    while (m_patients.size() > m_doctors.size()) {
        auto it = m_patients.begin();
        (*it)->setHired(false);
        (*it)->setStudent(false);
        (*it)->setState(CPerson::INFECTED);
        if ((*it)->hasGraduated())
            stats.m_graduates.push_back(*it);
        m_patients.erase(it--);
        stats.m_isolated--;
    }
}