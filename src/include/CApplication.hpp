/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "CGraphicController.hpp"
#include "CConfigFile.hpp"
#include "TStructures.hpp"

/**
 * The main application.
 * This class takes care of the switching between screens and the game itself.
 */ 
class CApplication
{
  public:

    /** 
     * Default constructor 
     * Initializes configuration and graphic controller
     */
    CApplication();

    /**
     * Destructor
     * Deletes the configuration and graphic controller
     */
    ~CApplication();

    /**
     * Starts the application
     */
    void run();

    /**
     * Starts welcome screen with the main menu
     * @return selected option of the menu
     */
    int startIntroScreen();

    /**
     * Starts a new game with default configurations
     * @return the game result or exit option
     */
    int startNewGame();

    /**
     * Opens a victory screen with an exit button
     * @return the exit option
     */
    int startVictoryScreen();

    /**
     * Opens a defeat screen with an exit button
     * @return the exit option
     */
    int startDefeatScreen();

    /**
     * Loads an existing game if exists
     * @return the game result or exit option
     * @throw error message if it fails
     */
    int loadGame();

    /**
     * Loads the configuration file
     * @returns true on success, false on failure
     */
    bool loadConfig();

  private:

    CGraphicController * m_graphicController;
    TConfig * m_config;
    
};