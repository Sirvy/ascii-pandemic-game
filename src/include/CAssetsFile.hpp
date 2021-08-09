/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "CFile.hpp"
#include "TStructures.hpp"
#include <string>

/**
 * Assets File Manager
 * This class takes care of the assets file
 */ 
class CAssetsFile : public CFile
{
  public:

    /**
     * A path to the assets file
     */
    const std::string FILENAME = FILE_DIRECTORY + "/assets.txt";

    /**
     * Constructor
     * @param config a pointer to the App's configuration
     */ 
    CAssetsFile(TConfig * config);

    /**
     * Destructor
     */ 
    ~CAssetsFile();

    /**
     * Loads the file
     * Loads the building's assets data into configuration
     * @throw error message on failure
     */ 
    virtual void loadFile() override;
};