/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "CFile.hpp"
#include "TStructures.hpp"
#include "CMap.hpp"
#include "CStatHandler.hpp"

/**
 * Game File Manager
 * This class takes care of the saved game file
 * It saves and loads a played out game data
 */ 
class CGameFile : public CFile
{
  public:

    /**
     * A path to the saved game file
     */
    const std::string FILENAME = FILE_DIRECTORY + "/save.txt";
    
    /**
     * Constructor
     * @param map a pointer to game's map
     * @param stats a pointer to game's statistics
     * @param config a pointer to game's configuration
     */ 
    CGameFile(CMap * map, CStatHandler * stats, TConfig * config);

    /**
     * Destructor
     */ 
    ~CGameFile();
    
    /**
     * Loads the file
     * Loads the saved game map, stats and configuration into game
     * @throw error message on failure
     */ 
    virtual void loadFile() override;
    
    /**
     * Saves the file
     * Saves the played out game data into a file
     * @throw error message on failure
     */ 
    void saveFile();

  private:
  
    CMap * m_map;
    CStatHandler * m_stats;
};