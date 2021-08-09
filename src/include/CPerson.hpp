/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include <chrono>

/**
 * Person
 * This class represent each citizen living in the city
 */
class CPerson
{
  public:

    /**
     * Enum of the person states
     */
    enum EState {HEALTHY, INFECTED, ISOLATED, DEAD};

    /**
     * Enum of the person profession
     */
    enum EProfession {BUSINESSMAN, DOCTOR, RESEARCHER, NONE};

    /**
     * Default constructor
     * Initializes the person attributes
     */
    CPerson();

    /**
     * Changes the person state to infected
     */
    void getInfected();

    /**
     * Changes the person state to dead
     */
    void die();

    /**
     * Gets the number of seconds that passed since the person got infected
     * @return number of seconds
     */
    unsigned getInfectedDurationInSeconds() const;

    /**
     * Checks if the person is already hired
     * @return true if hired, false if not
     */
    bool isHired() const;

    /**
     * Checks if the person is currently a student
     * @return true if is a student, false if not
     */
    bool isStudent() const;

    /**
     * Checks if the person has already graduated from university
     * @return true if yes, false if not
     */
    bool hasGraduated() const;
    
    /**
     * Changes the hired state of the person
     * @param hired the hired state
     */
    void setHired(bool hired);

    /**
     * Changes the student state of the person
     * @param student the student state
     */
    void setStudent(bool student);

    /**
     * Changes the graduated state of the person
     * @param graduated the graduated state
     */
    void setGraduated(bool graduated);

    /**
     * Changes the current state of the person
     * @param state the state of the person
     */
    void setState(EState state);

    /**
     * Changes the current profession of the person
     * @param profession the profession of the person
     */
    void setProfession(EProfession profession);

    /**
     * Gets the current state of the person
     * @return the state of the person
     */
    EState getState() const;

    /**
     * Gets the current profession of the person
     * @return the profession of the person
     */
    EProfession getProfession() const;

    /**
     * Checks if the person state is healthy
     * @return true if healthy, false if not
     */
    bool isHealthy() const;

    /**
     * Checks if the person state is infected
     * @return true if infected, false if not
     */
    bool isInfected() const;

    /**
     * Checks if the person state is isolated
     * @return true if isolated, false if not
     */
    bool isIsolated() const;

    /**
     * Checks if the person state is dead
     * @return true if dead, false if not
     */
    bool isDead() const;

    /**
     * Checks if the person is assigned to a residential building
     * @return true if has a resident, false if not
     */
    bool hasHome() const;

    /**
     * Changes the assigned resident indicator
     * @param home true for assigned resident, false otherwise
     */
    void setHome(bool home);
    
  private:

    bool m_hired;
    bool m_student;
    bool m_graduated;
    EState m_state;
    EProfession m_profession;
    std::chrono::steady_clock::time_point m_infectionStart;
    bool m_home;
    
};