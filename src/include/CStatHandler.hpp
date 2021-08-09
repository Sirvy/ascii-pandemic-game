/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include <vector>
#include <queue>
#include "CPerson.hpp"

/**
 * Stat Handler
 * This class handles the statistics of the game
 * Including the database of citizens
 */
class CStatHandler {

  public:

    /**
     * A constant that motivates people to become businessmen
     */
    const int BUSINESS_SALARY = 1000000;

    /**
     * Default constructor
     * Initializes the stastistics to default values
     */
    CStatHandler();

    /**
     * Destructor
     * Clears up the vector of citizens
     */
    ~CStatHandler();

    /**
     * Fills the vectors of citizens based on the statistics numbers
     * @throw error message on failure
     */
    void fillCitizens();

    /** Current amount of money **/
    unsigned m_money;

    /** Current number of all citizens **/
    unsigned m_citizenCnt;

    /** Current number of students **/
    unsigned m_studentCnt;

    /** Current number of active doctors **/
    unsigned m_doctorCnt;

    /** Current number of active scientists **/
    unsigned m_scientistCnt;

    /** Current number of active businessmen **/
    unsigned m_businessmanCnt;
    
    /** Current number of infected people **/
    unsigned m_infected;

    /** Current number of infected people isolated in hospitals **/
    unsigned m_isolated;
    
    /** Current number of deaths caused by the infection **/
    unsigned m_deathsByVirus;
    
    /** Current number of deaths caused by hunger **/
    unsigned m_deathsByOther;
    
    /** Current number of purchased masks in the city **/
    unsigned m_masks;
    
    /** Current number of stocks for the residents **/
    unsigned m_stocks;
    
    /** Number of seconds for the pandemic to start **/
    unsigned m_epidemic;
    
    /** An indicator for mandatory masks **/
    bool m_mandatoryMasks;

    /** An indicator for closed schools **/
    bool m_schoolsClosed;

    /** An indicator for closed businesses **/
    bool m_businessClosed;

    /** An indicator for active lockdown **/
    bool m_lockdown;

    /** Current R number of the virus **/
    double m_virusR;
    
    /** Amount of money invested into business **/
    unsigned m_investmentIntoBusiness;
    
    /** Amount of money invested into healthcare **/
    unsigned m_investmentIntoHealthcare;

    /** Amount of money invested into science **/
    unsigned m_investmentIntoScience;
    
    /** An indicator for finished vaccine **/
    bool m_vaccineFinished = false;
    
    /** Vector of all citizens **/
    std::vector<CPerson*> m_citizens;

    /** Queue of infected people waiting to be hospitalized **/
    std::queue<CPerson*> m_toBeHospitalized;
    
    /** Vector of graduated people waiting to get a job **/
    std::vector<CPerson*> m_graduates;
};