#include "CGame.hpp"

#include <chrono>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include "CGameFile.hpp"

using namespace std;

CGame::CGame() {}

CGame::CGame(TConfig * config, CGraphicController * graphicController)
: CScreen(graphicController),
  m_stats(new CStatHandler()),
  m_map(nullptr),
  m_selectedCell(nullptr),
  m_virus(new CVirus()),
  m_exit(false),
  m_config(config) 
{
    m_map = new CMap(m_config, MAP_HEIGHT, MAP_WIDTH);
    m_graphicController->setMenuOptions(
        std::vector<TMenu> {
            TMenu(2, 1, "Face Masks", OPTION_MASKS),
            TMenu(15, 1, "C/O Schools", OPTION_SCHOOL),
            TMenu(15, 2, "C/O Business", OPTION_BUSINESS),
            TMenu(2, 2, "C/O Lockdown", OPTION_LOCKDOWN),
            TMenu(2, 4, "Save", OPTION_SAVE),
            TMenu(15, 4, "Exit", OPTION_EXIT)
        }
    );
}

CGame::~CGame() {
    delete m_stats;
    if (m_map != nullptr)
        delete m_map;
    delete m_virus;
}

void CGame::loadGame()
{
    try {
        CGameFile loadFile(m_map, m_stats, m_config);
        loadFile.loadFile();
        m_virus->setKillTime(m_config->m_virusKillTime);
        m_virus->modifyR(m_config->m_virusR);
        m_stats->m_virusR = m_virus->getR();
    } catch (const char * e) {
        throw e;
    }
}

void CGame::initStats()
{
    m_stats->m_money = m_config->m_startingMoney;
    m_stats->m_citizenCnt = 0;
    m_stats->m_studentCnt = 0;
    m_stats->m_doctorCnt = 0;
    m_stats->m_scientistCnt = 0;
    m_stats->m_businessmanCnt = 0;
    m_stats->m_infected = 0;
    m_stats->m_isolated = 0;
    m_stats->m_deathsByVirus = 0;
    m_stats->m_deathsByOther = 0;
    m_stats->m_masks = 0;
    m_stats->m_stocks = 0;
    m_stats->m_epidemic = m_config->m_virusCountDown;
    m_stats->m_mandatoryMasks = false;
    m_stats->m_schoolsClosed = false;
    m_stats->m_businessClosed = false;
    m_stats->m_lockdown = false;
    m_virus->setKillTime(m_config->m_virusKillTime);
    m_virus->modifyR(m_config->m_virusR);
    m_stats->m_virusR = m_virus->getR();
}

int CGame::start()
{
    m_graphicController->initGame();
    m_graphicController->renderLayout();
    m_graphicController->renderMap(m_map);
    m_graphicController->renderMenu();

    m_bgThread = thread(&CGame::update, this);

    while (!m_exit.load()) {
        processInput();
    }

    m_exit = true;
    m_bgThread.join();

    if (m_stats->m_vaccineFinished) {
        return RESULT_VICTORY;
    } 
    
    if (m_stats->m_epidemic <= 0 && m_stats->m_citizenCnt <= 0) {
        return RESULT_DEFEAT;
    }

    return RESULT_NONE;
}

void CGame::saveGame()
{
    try {
        CGameFile gfile(m_map, m_stats, m_config);
        gfile.saveFile();
        m_graphicController->printMessage("Game has been saved.");
    } catch (const char * msg) {
        m_graphicController->printMessage("Error occured while saving the game: " + (string)msg);
    }
}

void CGame::processInput() 
{
    int event_x = 0, event_y = 0;

    int event = m_graphicController->mouseInput(event_x, event_y);

    if (event == CGraphicController::MENU_CLICKED) 
    {
        int menu_selected = m_graphicController->proceedMenuClicked(event_x, event_y);
        try {
            switch (menu_selected) {
                case OPTION_EXIT:     m_exit = true;      break;
                case OPTION_SAVE:     saveGame();         break;
                case OPTION_SCHOOL:   actionSchools();    break;
                case OPTION_BUSINESS: actionBusinesses(); break;
                case OPTION_MASKS:    actionMasks();      break;
                case OPTION_LOCKDOWN: actionLockdown();   break;
            }
        } catch (const char * e) {
            m_graphicController->printMessage("Error: " + (string)e);
        }
    } 
    else if (event == CGraphicController::SUBMENU_CLICKED) 
    {
        int menu_selected = m_graphicController->proceedSubmenuClicked(event_x, event_y);
        if (m_selectedCell != nullptr) {
            try {
                if (dynamic_cast<CEmpty*>(m_selectedCell)) {
                    switch (menu_selected) {
                        case CEmpty::OPTION_BUY_RESIDENTIAL:
                            buyResidential(m_selected_x-1, m_selected_y-1);
                            break;
                        case CEmpty::OPTION_BUY_HOSPITAL:
                            buyHospital(m_selected_x-1, m_selected_y-1);
                            break;
                        case CEmpty::OPTION_BUY_BUSINESS:
                            buyBusiness(m_selected_x-1, m_selected_y-1);
                            break;
                        case CEmpty::OPTION_BUY_UNIVERSITY:
                            buyUniversity(m_selected_x-1, m_selected_y-1);
                            break;
                        case CEmpty::OPTION_BUY_LABORATORY:
                            buyLaboratory(m_selected_x-1, m_selected_y-1);
                            break;
                    }
                } else m_selectedCell->proceedOptionClicked(menu_selected, *m_stats);
            } catch (const char * e) {
                m_graphicController->printMessage("Error: " + (string)e);
            }
        }
    } 
    else if (event == CGraphicController::MAP_CLICKED) 
    {
        int menu_selected = m_graphicController->proceedMapClicked(m_map, event_x, event_y, m_selected_x, m_selected_y); 
        if (menu_selected) {
            m_selectedCell = m_map->getCells().at(m_selected_y-1).at(m_selected_x-1);
            m_graphicController->renderSubmenu(m_selectedCell, m_selected_x, m_selected_y);
        }
    }
}

void CGame::buyResidential(int x, int y) 
{
    if (m_stats->m_mandatoryMasks && m_stats->m_masks < m_config->m_residentialCitizensAmount) {
        throw "Not enough masks to buy new residentials.";
    }

    if (m_stats->m_money < m_config->m_residentialPrice) {
        throw "Not enough money to buy new residential.";
    }

    m_stats->m_money -= m_config->m_residentialPrice;
    m_map->convertToResidential(x, y);
    m_selectedCell = nullptr;
    m_selected_x = 0;
    m_selected_y = 0;
    m_graphicController->clearSubmenu();
    m_graphicController->renderMap(m_map);
}

void CGame::buyHospital(int x, int y) 
{
    if (m_stats->m_money < m_config->m_hospitalPrice) {
        throw "Not enough money to buy new hospital.";
    }

    m_stats->m_money -= m_config->m_hospitalPrice;
    m_map->convertToHospital(x, y);
    m_selectedCell = nullptr;
    m_selected_x = 0;
    m_selected_y = 0;
    m_graphicController->clearSubmenu();
    m_graphicController->renderMap(m_map);
}

void CGame::buyBusiness(int x, int y) 
{
    if (m_stats->m_money < m_config->m_businessPrice) {
        throw "Not enough money to buy new business.";
    }

    m_stats->m_money -= m_config->m_businessPrice;
    m_map->convertToBusiness(x, y);
    m_selectedCell = nullptr;
    m_selected_x = 0;
    m_selected_y = 0;
    m_graphicController->clearSubmenu();
    m_graphicController->renderMap(m_map);
}

void CGame::buyUniversity(int x, int y) 
{
    if (m_stats->m_money < m_config->m_universityPrice) {
        throw "Not enough money to buy new university.";
    }

    m_stats->m_money -= m_config->m_universityPrice;
    m_map->convertToUniversity(x, y);
    m_selectedCell = nullptr;
    m_selected_x = 0;
    m_selected_y = 0;
    m_graphicController->clearSubmenu();
    m_graphicController->renderMap(m_map);
}

void CGame::buyLaboratory(int x, int y) 
{
    if (m_stats->m_money < m_config->m_laboratoryPrice) {
        throw "Not enough money to buy new laboratory.";
    }

    m_stats->m_money -= m_config->m_laboratoryPrice;
    m_map->convertToLaboratory(x, y);
    m_selectedCell = nullptr;
    m_selected_x = 0;
    m_selected_y = 0;
    m_graphicController->clearSubmenu();
    m_graphicController->renderMap(m_map);
}

void CGame::actionMasks() {
    if (m_stats->m_mandatoryMasks) {
        m_stats->m_mandatoryMasks = false;
        m_virus->increaseR(0.2);
    } else {
        if (m_stats->m_masks < m_stats->m_citizenCnt) {
            throw "Not enough masks to introduce mandatory masks.";
        }
        m_stats->m_masks -= m_stats->m_citizenCnt;
        m_stats->m_mandatoryMasks = true;
        m_virus->decreaseR(0.2);
    }
}

void CGame::actionSchools() {
    if (m_stats->m_schoolsClosed) {
        m_stats->m_schoolsClosed = false;
        m_virus->increaseR(0.5);
    } else {
        m_stats->m_schoolsClosed = true;
        m_virus->decreaseR(0.5);
    }
}

void CGame::actionBusinesses() {
    if (m_stats->m_businessClosed) {
         m_stats->m_businessClosed = false;
        m_virus->increaseR(0.8);
    } else {
        m_stats->m_businessClosed = true;
        m_virus->decreaseR(0.8);
    }
}

void CGame::actionLockdown() {
    if (m_stats->m_lockdown) {
        m_stats->m_lockdown = false;
        m_virus->increaseR(m_config->m_virusR);
    } else {
        m_stats->m_lockdown = true;
        m_virus->decreaseR(m_config->m_virusR);
    }
}

void CGame::killOnHunger() 
{
    for (auto & person : m_stats->m_citizens) {
        if (person->isHealthy() || person->isInfected()) {
            if (rand() % 10 == 1) {
                m_stats->m_citizenCnt--;
                if (person->isInfected()) m_stats->m_infected--;
                person->die();
                m_stats->m_deathsByOther++;
                break;
            }
        }
    }
}

void CGame::startProtests() 
{
    m_graphicController->printMessage("People started protesting because they are out of stocks are are hungry!");
    m_virus->modifyR(0.5 * m_config->m_virusR);
    killOnHunger();
}

void CGame::update() 
{
    unsigned ctr = 0;
    m_stats->m_money = m_config->m_startingMoney;

    while (!m_exit.load()) {
        auto start_time = chrono::steady_clock::now();
        ctr++;

        if (m_stats->m_vaccineFinished) {
            m_graphicController->printMessage("Your laboratory has finished the vaccine! You have won! Click anywhere to continue...");
            m_exit = true;
            break;
        }

        if (m_stats->m_epidemic <= 0 && m_stats->m_citizenCnt <= 0) {
            m_graphicController->printMessage("All the citizens of your city have died. You have lost. Click anywhere to continue...");
            m_exit = true;
            break;
        }

        if (m_stats->m_lockdown && m_stats->m_stocks <= 0 && m_stats->m_citizenCnt > 0) {
            startProtests();
        }

        if (m_stats->m_epidemic <= 0) {
            if (m_stats->m_citizenCnt > 0) {
                if (ctr % 2 == 0) {
                    if (rand() % 10 == 0)
                        infectPeople();
                    if (rand() % 10 == 5)
                        peopleInfectPeople();
                }
            }
            killPeople();
        }
        if (ctr % 2 == 0) {
            if (m_stats->m_epidemic > 0)
                m_stats->m_epidemic--;
        }

        performEvent(ctr);
        m_stats->m_virusR = m_virus->getR();
        m_map->update(*m_stats);
        m_graphicController->renderStatistics(*m_stats);

        auto toWait = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count();
        this_thread::sleep_for(chrono::milliseconds(500 - toWait));
    }
}

void CGame::infectPeople()
{
    for (auto & person : m_stats->m_citizens) {
        if (person->isHealthy() & (rand() % 10 == 0)) {
            person->getInfected();
            m_stats->m_toBeHospitalized.push(person);
            m_stats->m_infected++;
            break;
        }
    }
}

void CGame::peopleInfectPeople()
{
    for (unsigned i = 0; i < m_stats->m_infected - m_stats->m_isolated; i++) {
        unsigned r = ( rand() % 100 <= (int)((double)(m_virus->getR()*10)) ) * ceil(m_virus->getR());

        for (unsigned j = 0; j < r; j++) {
            unsigned random = rand() % (m_stats->m_citizenCnt);
            if (m_stats->m_citizens.at(random)->isHealthy()) {
                m_stats->m_citizens.at(random)->getInfected();
                m_stats->m_toBeHospitalized.push(m_stats->m_citizens.at(random));
                m_stats->m_infected++;
            }
        }
    }
}

void CGame::killPeople()
{
    for (auto & person : m_stats->m_citizens) {
        if (person->isInfected() && (person->getInfectedDurationInSeconds() >= m_virus->getKillTime())) {
            if (rand() % 10 == 1) {
                person->die();
                m_stats->m_citizenCnt--;
                m_stats->m_infected--;
                m_stats->m_deathsByVirus++;
            }
        }
    }
}

void CGame::performEvent(unsigned time)
{
    for (auto & event : m_config->m_events) {
        if (time == event.time*2) {
            if (event.type == TEvent::EVENT_R) {
                m_virus->modifyR(event.val);
                m_graphicController->printMessage("An event occured! The R constant has been modified to " + to_string(event.val));
            } else if (event.type == TEvent::EVENT_INFECTIONS) {
                unsigned i = 0;
                m_graphicController->printMessage("An event occured! " + to_string(event.val) + " people has just been infected!");
                for (auto & person : m_stats->m_citizens) {
                    if (i >= event.val) break;
                    if (person->isHealthy()) {
                        person->getInfected();
                        m_stats->m_toBeHospitalized.push(person);
                        m_stats->m_infected++;
                        i++;
                    }
                }
            }
        }
    }
}