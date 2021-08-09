/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "../CCell.hpp"

/**
 * Empty cell
 * This class represents an empty cell on the map
 */
class CEmpty : public CCell
{
  public:

    /**
     * Enum of Cell's menu options
     */
    enum OPTIONS {
        OPTION_BUY_RESIDENTIAL,   /**< An option to buy a residential building */
        OPTION_BUY_HOSPITAL,      /**< An option to buy a hospital building */
        OPTION_BUY_BUSINESS,      /**< An option to buy a business building */
        OPTION_BUY_UNIVERSITY,    /**< An option to buy a university building */
        OPTION_BUY_LABORATORY     /**< An option to buy a laboratory building */
    };

    /**
     * Constructor
     * Initializes the view of the empty cell
     * @param view the view of an empty cell on map
     */
    CEmpty(const std::string & view);

    /**
     * Does nothing
     */
    virtual void update(CStatHandler & stats) override;

    /**
     * Gets the vector of building's menu options
     * @return vector of menu options
     */
    virtual std::vector<TMenu> getOptions() const override;
    
    /**
     * Processes selected options
     * @param the selected option
     * @param a reference to the game statistics that might be modified 
     */
    virtual void proceedOptionClicked(int option, CStatHandler & stats) override;

    /**
     * Gets the cell's information
     * @return the current information of the cell
     */
    virtual std::string getInfo() const override;
    
    /**
     * Gets data of the cell to be saved in a save file
     * @return a string of the data
     */
    virtual std::string getSaveData() const override;

    /**
     * Does nothing
     * @param data a string of data to be loaded
     * @param stats a pointer to the game statistics
     */
    virtual void loadSaveData(const std::string & data, CStatHandler * stats) override;

  private: 
    
    std::vector<TMenu> m_options;

};