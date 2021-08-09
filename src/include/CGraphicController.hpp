/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include <ncurses.h>
#include <string>
#include <vector>
#include <mutex>
#include "TStructures.hpp"
#include "CStatHandler.hpp"
#include "CMap.hpp"
#include "CCell.hpp"

/**
 * Graphic Controller
 * Takes care of the graphic rendering in terminal using ncurses
 */ 
class CGraphicController
{
  public:

    /**
     * Defines the terminal height
     */
    static const int WINDOW_HEIGHT = 30;
    
    /**
     * Defines the terminal width
     */
    static const int WINDOW_WIDTH = 100;

    /**
     * An enum of which window has been click on
     */
    enum WINDOW_CLICKED {
        MENU_CLICKED,     /**< Player clicked on the game's menu */
        SUBMENU_CLICKED,  /**< Player clicked building's menu */
        MAP_CLICKED       /**< Player clicked on the map */
    };

    /**
     * Default constructor
     * Initializes the window and ncurses settings
     */
    CGraphicController();

    /**
     * Clears up and closes the ncruses data
     */
    ~CGraphicController();

    /**
     * Initializes the layout windows for the game
     */
    void initGame();

    /**
     * Renders the game layout
     */
    void renderLayout();

    /**
     * Renders the statistics window
     * @param stats the statistics to be rendered
     */
    void renderStatistics(const CStatHandler & stats);

    /**
     * Changes the menu options to be rendered
     * @param options a vector of the menu options
     */
    void setMenuOptions(const std::vector<TMenu> & options);

    /**
     * Renders menu options
     */
    void renderMenu();

    /**
     * Renders data in the submenu of the given cell
     * @param cell a pointer to the cell
     * @param selected_x the x coordinates of the cell
     * @param selected_y the y coordinates of the cell
     */
    void renderSubmenu(const CCell * cell, int selected_x, int selected_y);

    /**
     * Clears the submenu and leave it blank
     */
    void clearSubmenu();

    /**
     * Renders map
     * Highlights a selected cell on the map
     * @param map a pointer to the map
     * @param highlightX an x coordinate of the cell to be highlighted, -1 if none
     * @param highlightY an y coordinate of the cell to be highlighted, -1 if none
     */
    void renderMap(CMap * map, int highlightX = -1, int highlightY = -1);

    /**
     * Renders a given message in the message window
     * @param message a message to be rendered
     */
    void printMessage(const std::string & message);

    /**
     * Detects which window has been clicked on
     * and returns the location of the mouse click
     * @param[out] x the x coordinate of the mouseclick
     * @param[out] y the y coordinate of the mouseclick
     */
    int mouseInput(int & x, int & y);

    /**
     * Detects which option of the menu has been click on
     * @param x the x coordinate of the mouse click
     * @param y the y coordinate of the mouse click
     * @return the corresponding menu option
     */
    int proceedMenuClicked(int x, int y);

    /**
     * Detects which option of the submenu has been click on
     * @param x the x coordinate of the mouse click
     * @param y the y coordinate of the mouse click
     * @return the corresponding menu option
     */
    int proceedSubmenuClicked(int x, int y);

    /**
     * Detects which cell of the map has been click on
     * @param map a pointer to the map
     * @param[in] x the x coordinate of the mouse click
     * @param[in] y the y coordinate of the mouse click
     * @param[out] selected_x the x coordinate of the selected cell
     * @param[out] selected_y the y coordinate of the selected cell
     */
    int proceedMapClicked(CMap * map, int x, int y, int & selected_x, int & selected_y);

    /**
     * Renders a screen with a single window with a message and a menu
     * @param message a message to be printed on the window
     */
    void renderSingleWindowMenu(const std::string & message);
    
  private:
  
    bool m_gameInitialized;
    TWindow m_windowStats;
    TWindow m_windowMessage;
    TWindow m_windowMenu;
    TWindow m_windowSubmenu;
    TWindow m_windowMap;
    MEVENT  m_event;
    std::vector<TMenu> m_menuOptions;
    std::vector<TMenu> m_submenuOptions;
    std::mutex m_mtx;
};