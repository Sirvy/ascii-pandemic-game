/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

/**
 * Virus
 * This class represents the virus
 */
class CVirus
{
  public:

    /**
     * Default constructor
     * Initializes the R value to 0
     */
    CVirus();

    /**
     * Constructor
     * Initializes the R value to the given number
     * @param R the R value
     */
    CVirus(int R);

    /**
     * Modifies the R value
     * @param R the R value
     */
    void modifyR(double R);

    /**
     * Decreases the R value by given amount
     * @param amount to be decreased
     */
    void decreaseR(double amount);

    /**
     * Increases the R value by given amount
     * @param amount to be increased
     */
    void increaseR(double amount);

    /**
     * Gets the current R value
     * @return the current R value, 0 if negative
     */
    double getR() const;

    /**
     * Modifies the time of the virus to be deadly
     * @param killTime the time in seconds
     */
    void setKillTime(unsigned killTime);

    /**
     * Gets the killTime of the virus
     * @return number of seconds for the virus to be deadly
     */
    unsigned getKillTime() const;
    
  private:

    double m_R;
    unsigned m_timeToKill;

};