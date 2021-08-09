/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "CFile.hpp"
#include "TStructures.hpp"
#include <string>

/**
 * Configuration File Manager
 * This class takes care of the configuration file
 */ 
class CConfigFile : public CFile
{
  public:

    /**
     * A path to the configuration file
     */
    const std::string FILENAME = FILE_DIRECTORY + "/config.txt";

    /**
     * Constructor
     * @param config a pointer to the App's configuration
     */ 
    CConfigFile(TConfig * config);

    /**
     * Destructor
     */ 
    ~CConfigFile();

    /**
     * Loads the file
     * Loads the configuration data into App's configuration
     * @throw error message on failure
     */ 
    virtual void loadFile() override;
};