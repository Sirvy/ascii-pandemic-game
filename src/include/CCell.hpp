/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include <string>
#include "TStructures.hpp"
#include "CStatHandler.hpp"

/**
 * The Cell class
 * An abstract class that represents each cell (building) on the game map including the empty cell
 */ 
class CCell
{
  public:

    /**
     * Default constructor
     */ 
    CCell();

    /**
     * Constructor
     * Assigns a view of the Cell on the map
     * @param view
     */ 
    CCell(const std::string & view);

    /**
     * Virtual destructor
     */ 
    virtual ~CCell() = default;

    /**
     * Draws the assigned view
     * @return the view
     */ 
    virtual std::string draw() const;

    /**
     * Pure virtual method
     * Each building on the map gets updated frequently
     * May make changes to the game's statistics
     * @param stats a reference to the game's statistics
     */ 
    virtual void update(CStatHandler & stats) = 0;

    /**
     * Pure virtual method
     * @return vector of the cell's menu options
     */ 
    virtual std::vector<TMenu> getOptions() const = 0;

    /**
     * Pure virtual method
     * @return information of the cell
     */ 
    virtual std::string getInfo() const = 0;

    /**
     * Pure virtual method
     * Defines action to be done when an option of the Cell is clicked
     * and make changes to the game's statistics if necessary
     * @param option the selected option of the cell's menu
     * @param stats a reference to the game's statistics
     */ 
    virtual void proceedOptionClicked(int option, CStatHandler & stats) = 0;

    /**
     * Pure virtual method
     * Returns a string of necessary data to be saved when the game is being saved
     * @return a string of data to be saved
     */ 
    virtual std::string getSaveData() const = 0;

    /**
     * Pure virtual method
     * Receives data from the save file when the game is loading and parses them
     * May make changes to the game's statistics
     * @param data the string of data to be loaded
     * @param stats a pointer to the game's statistics 
     */ 
    virtual void loadSaveData(const std::string & data, CStatHandler * stats) = 0;

  protected:
  
    std::string m_view;
};