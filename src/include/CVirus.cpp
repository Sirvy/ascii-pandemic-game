#include "CVirus.hpp"


CVirus::CVirus() : m_R(0) {
}

CVirus::CVirus(int R) : m_R(R) {
}

void CVirus::modifyR(double R) {
    m_R = R;
}

void CVirus::decreaseR(double amount) 
{
    m_R -= amount;
}

void CVirus::increaseR(double amount) 
{
    m_R += amount;
}

double CVirus::getR() const {
    if (m_R < 0) return 0;
    return m_R;
}

void CVirus::setKillTime(unsigned killTime)
{
    m_timeToKill = killTime;
}

unsigned CVirus::getKillTime() const
{
    return m_timeToKill;
}