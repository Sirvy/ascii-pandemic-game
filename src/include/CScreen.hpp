/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "CGraphicController.hpp"

/**
 * An abstract class of the screens
 */
class CScreen 
{
  public:

    /**
     * Default constructor
     */
    CScreen();

    /**
     * Constructor
     * @param graphicController a pointer the the App's graphic controller
     */
    CScreen(CGraphicController * graphicController);

    /**
     * Virtual destructor
     */
    virtual ~CScreen() = default;

    /**
     * A pure virtual method
     * A method to start the screen
     * @return selected menu option
     */
    virtual int start() = 0;

    /**
     * A pure virtual method to process the menu selection
     */
    virtual void processInput() = 0;

  protected:

    CGraphicController * m_graphicController;
    
};