#include "COutroScreen.hpp"

#include <vector>
#include "TStructures.hpp"

using namespace std;

COutroScreen::COutroScreen(CGraphicController * graphicController, const string & message)
: CScreen(graphicController),
  m_choice(-1),
  m_message(message) {
    m_graphicController->setMenuOptions(vector<TMenu>{
        TMenu(2, 3, "Exit", OPTION_EXIT)
    });
}

COutroScreen::~COutroScreen() {}

void COutroScreen::processInput() {
    int event_x = 0, event_y = 0;

    int event = m_graphicController->mouseInput(event_x, event_y);

    if (event == CGraphicController::MENU_CLICKED) {
        int choice = m_graphicController->proceedMenuClicked(event_x, event_y);
        switch (choice) {
            case OPTION_EXIT:
                m_choice = OPTION_EXIT;
                break;
        }
    }
}

int COutroScreen::start() {
    m_graphicController->renderSingleWindowMenu(m_message);
    while (m_choice != OPTION_EXIT) {
        processInput();
    }
    return 0;
}