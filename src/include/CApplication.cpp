#include "CApplication.hpp"

#include <iostream>
#include <string>
#include "CConfigFile.hpp"
#include "CAssetsFile.hpp"
#include "CEventFile.hpp"
#include "CGame.hpp"
#include "CIntroScreen.hpp"
#include "COutroScreen.hpp"
#include "CGameFile.hpp"

using namespace std;

CApplication::CApplication()
: m_graphicController(new CGraphicController()),
  m_config(new TConfig()) {
}

CApplication::~CApplication()
{
    delete m_graphicController;
    delete m_config;
}

void CApplication::run()
{
    switch (startIntroScreen()) {
        case CIntroScreen::OPTION_EXIT: break;
        case CIntroScreen::OPTION_NEWGAME: 
            if (loadConfig()) {
                switch (startNewGame()) {
                    case CGame::RESULT_VICTORY:
                        startVictoryScreen();
                        break;
                    case CGame::RESULT_DEFEAT:
                        startDefeatScreen();
                        break;
                    case CGame::RESULT_NONE:
                        break;
                }
            }
            break;
        case CIntroScreen::OPTION_LOADGAME: 
            if (loadConfig()) {
                switch (loadGame()) {
                    case CGame::RESULT_VICTORY:
                        startVictoryScreen();
                        break;
                    case CGame::RESULT_DEFEAT:
                        startDefeatScreen();
                        break;
                    case CGame::RESULT_NONE:
                        break;
                }
            }
            break;
    }
}

int CApplication::startIntroScreen()
{
    CIntroScreen introScreen(m_graphicController);
    return introScreen.start();
}

int CApplication::startVictoryScreen()
{
    COutroScreen outroScreen(m_graphicController, "VICTORY");
    outroScreen.start();
    return 0;
}

int CApplication::startDefeatScreen()
{
    COutroScreen outroScreen(m_graphicController, "DEFEAT");
    outroScreen.start();
    return 0;
}

int CApplication::loadGame()
{
    CGame game(m_config, m_graphicController);
    try {
        game.loadGame();
        return game.start();
    } catch (const char * msg) {
        COutroScreen outroScreen(m_graphicController, "ERROR: " + (string)msg);
        outroScreen.start();
    }
    return CGame::RESULT_NONE;
}

int CApplication::startNewGame()
{
    CGame game(m_config, m_graphicController);
    game.initStats();
    return game.start();
}

bool CApplication::loadConfig()
{
    try {
        CConfigFile configFile(m_config);
        configFile.loadFile();
        CAssetsFile assetsFile(m_config);
        assetsFile.loadFile();
        CEventFile eventFile(m_config);
        eventFile.loadFile();
    } catch (const char * msg) {
        COutroScreen outroScreen(m_graphicController, "ERROR: " + (string)msg);
        outroScreen.start();
        return false;
    }
    return true;
}