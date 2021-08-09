#include "CPerson.hpp"

using namespace std;

CPerson::CPerson()
: m_hired(false),
  m_student(false),
  m_graduated(false),
  m_state(EState::HEALTHY),
  m_profession(EProfession::NONE),
  m_home(true) {
}

void CPerson::getInfected() 
{
    m_infectionStart = chrono::steady_clock::now();
    m_state = INFECTED;
}

unsigned CPerson::getInfectedDurationInSeconds() const
{
    if (m_state != INFECTED) return 0;
    return chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - m_infectionStart).count();
}

bool CPerson::isHired() const 
{
    return m_hired;
}

bool CPerson::isStudent() const
{
    return m_student;
}

bool CPerson::hasGraduated() const
{
    return m_graduated;
}

void CPerson::setHired(bool hired) 
{
    m_hired = hired;
}

void CPerson::setStudent(bool student)
{
    m_student = student;
}

void CPerson::setGraduated(bool graduated)
{
    m_graduated = graduated;
}

void CPerson::die()
{
    m_state = DEAD;
}

void CPerson::setState(EState state)
{
    m_state = state;
}

void CPerson::setProfession(EProfession profession)
{
    m_profession = profession;
}

CPerson::EState CPerson::getState() const 
{
    return m_state;
}

CPerson::EProfession CPerson::getProfession() const
{
    return m_profession;
}

bool CPerson::isHealthy() const
{
    return m_state == HEALTHY;
}

bool CPerson::isInfected() const
{
    return m_state == INFECTED;
}

bool CPerson::isIsolated() const
{
    return m_state == ISOLATED;
}

bool CPerson::isDead() const
{
    return m_state == DEAD;
}

bool CPerson::hasHome() const
{
    return m_home;
}

void CPerson::setHome(bool home)
{
    m_home = home;
}