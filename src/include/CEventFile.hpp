/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "CFile.hpp"
#include "TStructures.hpp"

/**
 * Event File Manager
 * This class takes care of the event file
 */ 
class CEventFile : public CFile
{
  public:

    /**
     * A path to the events file
     */
    const std::string FILENAME = FILE_DIRECTORY + "/events.txt";

    /**
     * Constructor
     * @param config a pointer to the App's configuration
     */ 
    CEventFile(TConfig * config);

    /**
     * Destructor
     */ 
    ~CEventFile();

    /**
     * Loads the file
     * Loads the events into configuration
     * @throw error message on failure
     */ 
    virtual void loadFile() override;

};