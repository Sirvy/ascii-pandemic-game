#include "CUniversity.hpp"

#include <sstream>
#include <ctime>

using namespace std;

CUniversity::CUniversity(const std::string & view, unsigned maximumStudents, unsigned graduationTime) 
: CCell(view),
  m_maximumStudents(maximumStudents),
  m_graduationTime(graduationTime),
  m_ctr(0),
  m_processGraduation(false) {
}

string CUniversity::getSaveData() const 
{
    return "university : " 
        + to_string(m_students.size());
}

void CUniversity::loadSaveData(const std::string & data, CStatHandler * stats)
{
    istringstream iss(data);
    string type;
    unsigned studentsCount;
    char delimiter;
    if (!(iss >> type >> delimiter >> studentsCount)) {
        throw "Error in reading University cell.";
    }
    
    for (auto & person : stats->m_citizens) {
        if (!person->isHired() && !person->hasGraduated() && !person->isStudent() && (person->isHealthy() || person->isInfected())) {
            m_students.push_back(person);
            person->setStudent(true);
        }
        if (m_students.size() == studentsCount) break;
    }
    if (m_students.size() != studentsCount) {
        throw "University building's number of students doesn't match.";
    }
}

void CUniversity::update(CStatHandler & stats)
{
    removeDeadStudents(stats);
    if (!stats.m_schoolsClosed && !stats.m_lockdown) {
        if (m_ctr >= m_graduationTime) {
            m_processGraduation = true;
        }
        if (m_ctr <= 0) {
            m_processGraduation = false;
        }
        if (m_processGraduation) {
            m_ctr--;
            actionGraduate(stats);
        } else {
            m_ctr++;
            if (m_students.size() < m_maximumStudents)
                hireNewStudents(stats);
        }
    }
}

vector<TMenu> CUniversity::getOptions() const 
{
    return m_options;
}

string CUniversity::getInfo() const
{
    return "University, current students: " + to_string(m_students.size());
}

void CUniversity::proceedOptionClicked(int option, CStatHandler & stats) 
{}

void CUniversity::hireNewStudents(CStatHandler & stats)
{
    for (auto & person : stats.m_citizens) {
        if (!person->isHired() && !person->hasGraduated() && !person->isStudent() && person->isHealthy()) {
            stats.m_studentCnt++;
            m_students.push_back(person);
            person->setStudent(true);
            break;
        }
    }
}

void CUniversity::actionGraduate(CStatHandler & stats)
{
    for (auto it = m_students.begin(); it != m_students.end(); ++it) {
        unsigned random = rand() % (stats.m_investmentIntoBusiness + stats.m_investmentIntoHealthcare + stats.m_investmentIntoScience);
        if (random < stats.m_investmentIntoBusiness)
            (*it)->setProfession(CPerson::BUSINESSMAN);
        else if (random >= stats.m_investmentIntoBusiness && random < stats.m_investmentIntoBusiness + stats.m_investmentIntoHealthcare)
            (*it)->setProfession(CPerson::DOCTOR);
        else
            (*it)->setProfession(CPerson::RESEARCHER);
        (*it)->setStudent(false);
        (*it)->setGraduated(true);
        stats.m_graduates.push_back(*it);
        m_students.erase(it--);
        stats.m_studentCnt--;
        break;
    }
}

void CUniversity::removeDeadStudents(CStatHandler & stats)
{
    for (auto it = m_students.begin(); it != m_students.end(); ++it) {
        if ((*it)->isIsolated() || (*it)->isDead()) {
            (*it)->setStudent(false);
            (*it)->setHired(false);
            (*it)->setGraduated(false);
            m_students.erase(it--);
            stats.m_studentCnt--;
        }
    }
}