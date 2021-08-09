#include "CStatHandler.hpp"

#include "CPerson.hpp"

CStatHandler::CStatHandler()
:   m_money(0),
    m_citizenCnt(0),
    m_studentCnt(0),
    m_doctorCnt(0),
    m_scientistCnt(0),
    m_infected(0),
    m_isolated(0),
    m_deathsByVirus(0),
    m_deathsByOther(0),
    m_masks(0),
    m_stocks(0),
    m_epidemic(0),
    m_mandatoryMasks(false),
    m_schoolsClosed(false),
    m_businessClosed(false),
    m_lockdown(false),
    m_virusR(0),
    m_investmentIntoBusiness(BUSINESS_SALARY),
    m_investmentIntoHealthcare(0),
    m_investmentIntoScience(0) {
}

CStatHandler::~CStatHandler() {
    for (auto & it : m_citizens)
        delete it;
}

void CStatHandler::fillCitizens()
{
    if (   m_infected > m_citizenCnt 
        || m_isolated > m_citizenCnt 
        || m_studentCnt > m_citizenCnt
        || m_doctorCnt > m_citizenCnt
        || m_scientistCnt > m_citizenCnt) {
        throw "Citizens numbers doesn't make sense.";
    }
    while (m_citizens.size() < m_citizenCnt) {
        CPerson * tmp = new CPerson();
        tmp->setHome(false);
        m_citizens.push_back(tmp);
    }
    unsigned i = 0;
    for (auto & person : m_citizens) {
        if (person->isHealthy()) {
            if (i >= m_isolated) break;
            i++;
            person->setState(CPerson::ISOLATED);
            m_toBeHospitalized.push(person);
        }
    }
    if (i != m_isolated) throw "Number of isolated people doesn't match.";
    i = 0;
    for (auto & person : m_citizens) {
        if (person->isHealthy()) {
            if (i >= m_infected - m_isolated) break;
            i++;
            person->getInfected();
            m_toBeHospitalized.push(person);
        }
    }
    if (i != m_infected - m_isolated) throw "Number of infected people doesn't match.";
    i = 0;
    for (auto & person : m_citizens) {
        if ((person->isHealthy() || person->isInfected()) && person->getProfession() == CPerson::NONE) {
            if (i >= m_businessmanCnt) break;
            i++;
            person->setProfession(CPerson::BUSINESSMAN);
            person->setGraduated(true);
            m_graduates.push_back(person);
        }
    }
    if (i != m_businessmanCnt) throw "Number of businessmen people doesn't match.";
    i = 0;
    for (auto it = m_citizens.rbegin(); it != m_citizens.rend(); ++it) {
        if (((*it)->isHealthy() || (*it)->isInfected()) && (*it)->getProfession() == CPerson::NONE) {
            if (i >= m_doctorCnt) break;
            i++;
            (*it)->setProfession(CPerson::DOCTOR);
            (*it)->setGraduated(true);
            m_graduates.push_back((*it));
        }
    }
    if (i != m_doctorCnt) throw "Number of doctors people doesn't match.";
    i = 0;
    for (auto it = m_citizens.rbegin(); it != m_citizens.rend(); ++it) {
        if (((*it)->isHealthy() || (*it)->isInfected()) && (*it)->getProfession() == CPerson::NONE) {
            if (i >= m_scientistCnt) break;
            i++;
            (*it)->setProfession(CPerson::RESEARCHER);
            (*it)->setGraduated(true);
            m_graduates.push_back((*it));
        }
    }
    if (i != m_scientistCnt) throw "Number of scientists people doesn't match.";

}