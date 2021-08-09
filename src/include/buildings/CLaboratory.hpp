/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "../CCell.hpp"

/**
 * Laboratory building
 * This class represents a laboratory building cell
 */
class CLaboratory : public CCell
{
  public:

    /**
     * Enum of Building menu options
     */
    enum OPTIONS { 
        OPTION_INVEST_INTO_SCIENCE,     /**< An option to invest into science */
        OPTION_INVEST_INTO_SCIENCE2     /**< An option to invest more into science */
    };

    /**
     * Constructor
     * Initializes the building's attributes
     * @param view the view of the building on map
     * @param sciencePrice the price to be invested into science
     * @param vaccineSpeed the speed of the vaccine development
     */
    CLaboratory(const std::string & view, unsigned sciencePrice, unsigned vaccineSpeed);

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
     * Hires new employees from the vector of graduates
     * @param stats a reference to the game statistics
     */
    void hireNewScientists(CStatHandler & stats);

    /**
     * Increases progress in vaccine development
     * @param stats a reference to the game statistics
     */
    void improveProgress(CStatHandler & stats);

    /**
     * Sets the indicator of a vaccine to be finished if it's finished
     */
    void vaccineFinished();

    /**
     * Removes employees who are either isolated or dead
     * @param stats a reference to the game statistics
     */
    void removeDeadEmployee(CStatHandler & stats);
    
    std::vector<TMenu> m_options;

    std::vector<CPerson*> m_scientists;

    unsigned m_sciencePrice;

    unsigned m_progress;

    unsigned m_vaccineSpeed;

    unsigned m_failedAttempts;

    int m_ctr;

};