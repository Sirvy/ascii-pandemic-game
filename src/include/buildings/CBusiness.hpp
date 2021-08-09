/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "../CCell.hpp"

/**
 * Business building
 * This class represents a Business building cell
 */
class CBusiness : public CCell
{
  public:

    /**
     * Enum of Building menu options
     */
    enum OPTIONS { 
        OPTION_BUY_MASKS  /**< An option to buy masks */
    };

    /**
     * Constructor
     * Initializes the building's attributes
     * @param view the view of the building on map
     * @param maxTaxpayers the maximum number of workers
     * @param taxes the amount of money to be earned by each worker
     * @param masksPrice the price of buying masks
     * @param masksAmount the amount of masks to be purchased
     */
    CBusiness(const std::string & view, unsigned maxTaxpayers, unsigned taxes, unsigned masksPrice, unsigned masksAmount);

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
     * Buys masks if the masks option was selected
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
     * A method to increase the game's money
     * @param[out] statsMoney the game's money to be updated
     */
    void payTaxes(unsigned & statsMoney);

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

    std::vector<TMenu> m_options;

    unsigned m_maxTaxPayers;

    unsigned m_taxes;

    unsigned m_masksPrice;

    unsigned m_masksAmount;
    
    std::vector<CPerson*> m_taxPayers;

};