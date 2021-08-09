/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 * 
 * This file contains helpful structures used in the game
 * The reason for these structures to be here instead of being represented as classes
 * is that apart from getters and setters for each attribute, they wouldn't contain any other meaningful method
 */

#pragma once

#include <ncurses.h>
#include <string>
#include <vector>

/**
 * TWindow
 * This structure represents a rendered window for the graphic controller
 */
struct TWindow {

    /**
     * Default constructor
     */
    TWindow();

    /**
     * Constructor
     * Initializes the window
     * @param x the starting x position of the window
     * @param y the starting y position of the window
     * @param sizeX the width size of the window
     * @param sizeY the height size of the window
     */
    TWindow(int x, int y, int sizeX, int sizeY);

    /** The ncurses window */
    WINDOW * window;
    
    /** The starting x position of the window */
    int x;

    /** The starting y position of the window */
    int y;

    /** The width size of the window */
    int sizeX;

    /** The height size of the window */
    int sizeY;
};

/**
 * TMenu
 * This structure represents a menu option
 */
struct TMenu {
    
    /**
     * Default constructor
     */
    TMenu();

    /**
     * Constructor
     * Initializes the menu option
     * @param x the starting x position of the option
     * @param y the starting y position of the option
     * @param text a caption of the option
     * @param return_value a value to be returned when this option gets selected
     */
    TMenu(int x, int y, std::string text, int return_value = 0);

    /** The starting x position of the option */
    int x;

    /** The starting y position of the option */
    int y;

    /** The caption of the option */
    std::string text;

    /** A value to be returned when this option gets selected */
    int return_value;
};

/**
 * TEvent
 * This structure represents a game event that could occur during the play
 */
struct TEvent {

    /**
     * Enum of the event type
     */
    enum ETYPE { 
        EVENT_R,            /**< An event that modifies the R value of the virus */
        EVENT_INFECTIONS    /**< An event that suddenly infects given amount of people */
    };

    /**
     * Default constructor
     */
    TEvent();

    /**
     * Constructor
     * Initializes the event attributes
     * @param type the event type
     * @param time the time in seconds for the event to be executed
     * @param val the value of the event
     */
    TEvent(ETYPE type, unsigned time, unsigned val);

    /** The type of the event */
    ETYPE type;

    /** The time for the event to happen in seconds */
    unsigned time;

    /** The value of the event */
    unsigned val;
};

/**
 * Config
 * This structure represents the configuration of the game
 * Loaded from the configuration file
 */
struct TConfig {

    /**
     * Default constructor
     */
    TConfig();

    /** Starting money */
    unsigned m_startingMoney;

    /** The price of a stock */
    unsigned m_stockPrice;

    /** The amount of stocks to be purchased each time */
    unsigned m_stockAmount;

    /** The price of buying masks */
    unsigned m_masksPrice;

    /** The amount of masks to be purchased each time */
    unsigned m_masksAmount;
    
    /** The view of an empty cell */
    std::string m_emptyCellView;

    /** The view of a residential building */
    std::string m_residentailView;
    
    /** The number of citizens summoned in each residential building */
    unsigned m_residentialCitizensAmount;

    /** The price of a residential building */
    unsigned m_residentialPrice;

    /** The view of a hospital building */
    std::string m_hospitalView;

    /** The price of a hospital building */
    unsigned m_hospitalPrice;

    /** The maximum number of patients for each hospital */
    unsigned m_hospitalMaxPatients;

    /** The price of increasing a hospital number of patients */
    unsigned m_hospitalMaxParientsPrice;

    /** The price to invest into healthcare */
    unsigned m_healthCarePrice;

    /** The view of a business building */
    std::string m_businessView;

    /** The price of a business building */
    unsigned m_businessPrice;

    /** The maximum number of workers per business building */
    unsigned m_businessMaxTaxpayers;

    /** The number of money received from each worker and business building */
    unsigned m_businessTaxes;
    
    /** The view of a university building */
    std::string m_universityView;

    /** The price of a university building */
    unsigned m_universityPrice;

    /** The maximum number of students per university */
    unsigned m_universityMaximumStudents;

    /** The time in 0.5s for the university to perform graduation */
    unsigned m_graduationTime;

    /** The view of a laboratory biulding */
    std::string m_laboratoryView;

    /** The price of a laboratory building */
    unsigned m_laboratoryPrice;

    /** The price to invest into science */
    unsigned m_sciencePrice;

    /** The variable speed of a vaccine to be developed for each laboratory */
    unsigned m_vaccineDevelopmentSpeed;

    /** The R value of the virus */
    unsigned m_virusR;

    /** The time in seconds for the virus to become deadly */
    unsigned m_virusKillTime;

    /** The number of seconds before the epidemic starts */
    unsigned m_virusCountDown;
    
    /** A vector of game events */
    std::vector<TEvent> m_events;
};