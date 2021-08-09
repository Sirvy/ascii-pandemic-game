/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "CScreen.hpp"

#include "CGraphicController.hpp"

/**
 * The ending screen
 */ 
class COutroScreen : public CScreen
{
  public:

    /**
     * Enum of the menu options
     */
    enum OPTIONS {
        OPTION_EXIT     /**< Option for exit */
    };

    /**
     * Constructor
     * @param graphicController a pointer the the App's graphic controller
     * @param message a message to be printed on the screen
     */
    COutroScreen(CGraphicController * graphicController, const std::string & message);

    /**
     * Destructor
     */
    ~COutroScreen();

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

    std::string m_message;

};