/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include <vector>
#include "CCell.hpp"
#include "buildings/CEmpty.hpp"
#include "buildings/CResidential.hpp"
#include "buildings/CHospital.hpp"
#include "buildings/CBusiness.hpp"
#include "buildings/CUniversity.hpp"
#include "buildings/CLaboratory.hpp"
#include "TStructures.hpp"
#include "CStatHandler.hpp"


/**
 * Map
 * A class that defines the game map
 */
class CMap
{
  public:

    /**
     * Defines the maximum number of map rows
     */
    const int MAX_ROWS = 7;
    
    /**
     * Defines the maximum number of map columns
     */
    const int MAX_COLUMNS = 14;

    /**
     * Constructor
     * Initializes a new map of the given size
     * @param config a pointer to the game configuration
     * @param rows the size of map in rows
     * @param columns the size of map in columns
     */
    CMap(TConfig * config, int rows, int columns);

    /**
     * Destructor
     * Clears each cell of the map
     */
    ~CMap();

    /**
     * @return the number of map rows
     */
    int getRows() const;

    /**
     * @return the number of map columns
     */
    int getColumns() const;

    /**
     * Resizes the map with the given size
     * Clears all the cells from the previous map
     * @param rows the size of map in rows
     * @param columns the size of map in columns
     */
    void newSize(int rows, int columns);

    /**
     * A method to load the data from a saved game for each cell
     * @param y the y coordinate of the Cell
     * @param x the x coordinate of the Cell
     * @param data the data to be loaded by the Cell
     * @param stats a pointer to the game statistics that might be modifies
     * @throw error message on failure
     */
    void loadCell(int y, int x, const std::string & data, CStatHandler * stats);

    
    /**
     * All the map cells
     * @return 2D vector of all the map cells
     */
    std::vector<std::vector<CCell*>> getCells();

    /**
     * Updates each cell
     * @param a reference to the game statistics that might be modifies
     */
    void update(CStatHandler & stats);

    /**
     * Converts a given cell to residential building
     * @param x the x coordinates of the cell
     * @param y the y coordinates of the cell
     */
    void convertToResidential(int x, int y);

    /**
     * Converts a given cell to hospital building
     * @param x the x coordinates of the cell
     * @param y the y coordinates of the cell
     */
    void convertToHospital(int x, int y);

    /**
     * Converts a given cell to business building
     * @param x the x coordinates of the cell
     * @param y the y coordinates of the cell
     */
    void convertToBusiness(int x, int y);

    /**
     * Converts a given cell to university building
     * @param x the x coordinates of the cell
     * @param y the y coordinates of the cell
     */
    void convertToUniversity(int x, int y);

    /**
     * Converts a given cell to laboratory building
     * @param x the x coordinates of the cell
     * @param y the y coordinates of the cell
     */
    void convertToLaboratory(int x, int y);
    
  private:

    TConfig * m_config;
    int m_rows;
    int m_columns;
    std::vector<std::vector<CCell*>> m_cells;
    
};