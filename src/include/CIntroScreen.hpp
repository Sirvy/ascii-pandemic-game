/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "CScreen.hpp"

#include "CGraphicController.hpp"

/**
 * The welcome screen
 */ 
class CIntroScreen : public CScreen
{
  public:

    /**
     * The welcome message to be shown on the screen
     */
    const std::string MESSAGE = "Welcome to the (Corona)virus game!";

    /**
     * Enum of the menu options
     */
    enum OPTIONS {
        OPTION_NEWGAME,     /**< Option for a new game */
        OPTION_LOADGAME,    /**< Option for a loading a game */
        OPTION_EXIT         /**< Option for exit */
    };

    /**
     * Constructor
     * @param graphicController a pointer to the App's graphic controller
     */
    CIntroScreen(CGraphicController * graphicController);

    /**
     * Destructor
     */
    ~CIntroScreen();

    /**
     * A method to process the menu selection
     */
    virtual void processInput() override;

    /**
     * A method to start the screen
     * @return selected menu option
     */
    virtual int start() override;

  protected:
  
    int m_choice;

};