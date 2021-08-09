#include "CIntroScreen.hpp"

#include <vector>
#include "TStructures.hpp"

using namespace std;

CIntroScreen::CIntroScreen(CGraphicController * graphicController)
: CScreen(graphicController),
  m_choice(-1) {
    m_graphicController->setMenuOptions(vector<TMenu>{
        TMenu(2, 3, "New Game", OPTION_NEWGAME),
        TMenu(2, 5, "Load Game", OPTION_LOADGAME),
        TMenu(2, 7, "Exit", OPTION_EXIT)
    });
}

CIntroScreen::~CIntroScreen() {}

void CIntroScreen::processInput() {
    
    int event_x = 0, event_y = 0;

    int event = m_graphicController->mouseInput(event_x, event_y);

    if (event == CGraphicController::MENU_CLICKED) {
        int choice = m_graphicController->proceedMenuClicked(event_x, event_y);
        switch (choice) {
            case OPTION_NEWGAME:
                m_choice = OPTION_NEWGAME;
                break;
            case OPTION_LOADGAME:
                m_choice = OPTION_LOADGAME;
                break;
            case OPTION_EXIT:
                m_choice = OPTION_EXIT;
                break;
        }
    }
}

int CIntroScreen::start() {
    m_graphicController->renderSingleWindowMenu(MESSAGE);
    while (m_choice != OPTION_EXIT && m_choice != OPTION_NEWGAME && m_choice != OPTION_LOADGAME) {
        processInput();
    }
    return m_choice;
}