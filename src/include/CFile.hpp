/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include <string>
#include "TStructures.hpp"

/**
 * Event File Manager
 * This class takes care of the event file
 */ 
class CFile 
{
  public:
  
    /**
     * A path to the files directory
     */
    const std::string FILE_DIRECTORY = "examples/";
    
    /**
     * Constructor
     * @param config a pointer to the App's configuration
     */ 
    CFile(TConfig * config);
    
    /**
     * Virtual destructor
     */ 
    virtual ~CFile() = default;

    /**
     * Pure virtual method
     * Loads the file
     */ 
    virtual void loadFile() = 0;

  protected:
  
    TConfig * m_config;
};