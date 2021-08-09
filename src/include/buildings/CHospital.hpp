#pragma once

#include "../CCell.hpp"

/**
 * Hospital building
 * This class represents a hospital building cell
 **/
class CHospital : public CCell
{
  public:

    /**
     * Enum of Building menu options
     */
    enum OPTIONS { 
      OPTION_INVEST_INTO_HEALTHCARE,  /**< An option to invest money into healthcare */
      OPTION_INCREASE_MAX_PATIENTS    /**< An option to increase the maximum number of patients */
    };

    /**
     * Constructor
     * Initializes the building's attributes
     * @param view the view of the building on map
     * @param maxPatients the maximum number of patients
     * @param maxPatientsPrice the price of increasing the maximum number of patients
     * @param healthCarePrice the price of investing into healthcare
     */
    CHospital(const std::string & view, unsigned maxPatients, unsigned maxPatientsPrice, unsigned healthCarePrice);

    /**
     * Takes care of the building life updates
     * @param stats a reference to the game statistics that might be modified
     */
    virtual void update(CStatHandler & stats) override;

    /**
     * Gets the vector of building's menu options
     * @return vector of menu options
     */
    virtual std::vector<TMenu> getOptions() const override;

    /**
     * Gets the building information
     * @return the current information of the building
     */
    virtual std::string getInfo() const override;

    /**
     * Processes selected options
     * @param the selected option
     * @param a reference to the game statistics that might be modified 
     */
    virtual void proceedOptionClicked(int option, CStatHandler & stats) override;
    
    /**
     * Gets data of the building to be saved in a save file
     * @return a string of the data
     */
    virtual std::string getSaveData() const override;

    /**
     * Loads building data based on the given data
     * @param data a string of data to be loaded
     * @param stats a pointer to the game statistics that might be modified
     */
    virtual void loadSaveData(const std::string & data, CStatHandler * stats) override;

  private: 

    /**
     * Changes the state of a patient to healthy and releases him from the hospital
     * @param stats a reference to the game statistics that might be modified
     */
    void curePatients(CStatHandler & stats);

    /**
     * Receives an infected person from the infected queue and changes his state to isolated
     * @param stats a reference to the game statistics that might be modified
     */
    void receivePatients(CStatHandler & stats);

    /**
     * Hires new employees from the vector of graduates
     * @param stats a reference to the game statistics
     */
    void hireNewEmployee(CStatHandler & stats);

    /**
     * Removes employees who are either isolated or dead
     * @param stats a reference to the game statistics
     */
    void removeDeadEmployee(CStatHandler & stats);

    /**
     * Removes patients if there are no doctors in the hospital
     * @param stats a reference to the game statistics
     */
    void removeSurplusPatients(CStatHandler & stats);
    
    std::vector<TMenu> m_options;

    std::vector<CPerson*> m_doctors;

    std::vector<CPerson*> m_patients;

    unsigned m_maxPatients;

    unsigned m_maxPatientsPrice;

    unsigned m_healthCarePrice;

    unsigned m_ctr;

};