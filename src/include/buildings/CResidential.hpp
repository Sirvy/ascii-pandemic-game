/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "../CCell.hpp"

/**
 * Residential building
 * This class represents a Residential building call
 */
class CResidential : public CCell
{
  public:

    /**
     * Enum of Building menu options
     */
    enum OPTIONS { 
        OPTION_INVEST_INTO_STOCKS   /**< An option to buy stocks */
    };

    /**
     * Constructor
     * Initializes the building's attributes
     * @param view the view of the building on map
     * @param citizensAmount the number of citizens to be summoned
     * @param stockPrice the price of buying stocks
     * @param stockAmount the amount of stocks to be purchased
     */
    CResidential(const std::string & view, unsigned citizensAmount, unsigned stockPrice, unsigned stockAmount);

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
     * Reduces stocks on active lockdown
     * @param stats a reference to the game statistics
     */
    void decreaseStocks(CStatHandler & stats);

    /**
     * Removes citizens who are dead
     */
    void removeDeadCitizens();
    
    std::vector<TMenu> m_options;

    std::vector<CPerson*> m_citizens;

    unsigned m_citizensAmount;

    unsigned m_stockPrice;
    
    unsigned m_stockAmount;

    bool m_alreadyMaxed;

};