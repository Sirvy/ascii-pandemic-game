/**
 * @author Hoang Nam Tran <tranhoa1@fit.cvut.cz>
 */

#pragma once

#include "CScreen.hpp"

#include <thread>
#include <atomic>
#include "CGraphicController.hpp"
#include "CMap.hpp"
#include "CVirus.hpp"
#include "CStatHandler.hpp"
#include "CPerson.hpp"

/**
 * The game class
 * Takes care of every event and action during the gameplay
 */
class CGame : public CScreen
{
  public:

    /**
     * An enum of game options that appears in the game menu
     */ 
    enum OPTIONS {
        OPTION_MASKS,       /**< An option to introduce/cancel mandatory masks */
        OPTION_SCHOOL,      /**< An option to close/open universities */
        OPTION_BUSINESS,    /**< An option to close/open businesses */
        OPTION_LOCKDOWN,    /**< An option to start/stop a lockdown */
        OPTION_SAVE,        /**< An option to save a game */
        OPTION_EXIT         /**< An option to exit the game */
    };

    /**
     * An enum of possible game results to be sent to Application
     */ 
    enum RESULT {
        RESULT_NONE,        /**< A default game result (during exit) */
        RESULT_VICTORY,     /**< Results in victory */
        RESULT_DEFEAT       /**< Results in defeat */
    };

    /**
     * The size of map's witdth
     */
    const int MAP_WIDTH = 13;

    /**
     * The size of map's height
     */
    const int MAP_HEIGHT = 7;

    /**
     * Default constructor
     */
    CGame();

    /**
     * Constructor
     * Initializes the game configuration, menu, statistics, map
     * @param config a pointer to the App's configuration
     * @param graphicController a pointer to the App's graphic controller
     */
    CGame(TConfig * config, CGraphicController * graphicController);

    /**
     * Destructor
     */
    ~CGame();

    /**
     * Processes selected game's menu option
     */
    virtual void processInput() override;

    /**
     * The start of a game
     * Renders game layout, simulates the world life in a background threat
     * Processes actions of the player
     */
    virtual int start() override;

    /**
     * Loads a saved game
     * @throw error message on failure
     */
    void loadGame();

    /**
     * Initializes the game statistics to default values
     */
    void initStats();

  private:

    /**
     * Saves the current game
     * @throw error message on failure
     */
    void saveGame();

    /**
     * Buys a new Residential building
     * @param x coordinate of the purchase
     * @param y coordinate of the purchase
     */
    void buyResidential(int x, int y);

    /**
     * Buys a new Hospital building
     * @param x coordinate of the purchase
     * @param y coordinate of the purchase
     */
    void buyHospital(int x, int y);

    /**
     * Buys a new Business building
     * @param x coordinate of the purchase
     * @param y coordinate of the purchase
     */
    void buyBusiness(int x, int y);

    /**
     * Buys a new University building
     * @param x coordinate of the purchase
     * @param y coordinate of the purchase
     */
    void buyUniversity(int x, int y);

    /**
     * Buys a new Laboratory building
     * @param x coordinate of the purchase
     * @param y coordinate of the purchase
     */
    void buyLaboratory(int x, int y);

    /**
     * Introduces or cancels mandatory masks
     */
    void actionMasks();

    /**
     * Closes or reopens universities
     */
    void actionSchools();

    /**
     * Closes or reopens businesses
     */
    void actionBusinesses();

    /**
     * Starts or stops lockdown
     */
    void actionLockdown();

    /**
     * A method that kills citizens when they are out of stocks during the lockdown
     */
    void killOnHunger();

    /**
     * An event that occurs when citizens are out of stocks and are still forced to stay at home (during lockdown)
     * Increases the virus R constant
     */
    void startProtests();

    /**
     * A simulation of the city's life running in the background threat
     * Takes care of map and statistics updates
     * Refreshes every 500ms
     */
    void update();

    /**
     * Infects a random person with a 10% chance
     */
    void infectPeople();

    /**
     * For each infected citizen that is not isolated,
     * there is a chance to infect up to R other citizens
     */
    void peopleInfectPeople();

    /**
     * Kills citizens that had exceeded the killTime of the virus while not being isolated with 10% chance
     */ 
    void killPeople();

    /**
     * Performs an event
     * An event could be either suddenly infecting people
     * or R modification
     * @param time elapsed time since the game started (every 0.5s)
     */
    void performEvent(unsigned time);

    CStatHandler * m_stats;
    CMap * m_map;
    CCell * m_selectedCell;
    int m_selected_x;
    int m_selected_y;
    CVirus * m_virus;
    std::thread m_bgThread;
    std::atomic_bool m_exit;
    TConfig * m_config;

};