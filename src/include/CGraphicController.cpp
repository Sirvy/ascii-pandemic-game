#include "CGraphicController.hpp"

#include <sstream>
#include "CCell.hpp"

using namespace std;

CGraphicController::CGraphicController() 
: m_gameInitialized(false)
{
    unique_lock<mutex> ul(m_mtx);
    stringstream system_commands;
    system_commands << "resize -s " << WINDOW_HEIGHT << " " << WINDOW_WIDTH;
    system(system_commands.str().c_str());
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    refresh();
    mousemask(BUTTON1_CLICKED, NULL);
}

CGraphicController::~CGraphicController()
{
    if (m_gameInitialized) {
        wrefresh(m_windowStats.window);
        delwin(m_windowStats.window);

        wrefresh(m_windowMap.window);
        delwin(m_windowMap.window);

        wrefresh(m_windowMenu.window);
        delwin(m_windowMenu.window);

        wrefresh(m_windowSubmenu.window);
        delwin(m_windowSubmenu.window);

        wrefresh(m_windowMessage.window);
        delwin(m_windowMessage.window);
    }
    endwin();
}

void CGraphicController::initGame() 
{
    unique_lock<mutex> ul(m_mtx);
    m_gameInitialized = true;
    clear();
    refresh();

    m_windowStats = TWindow(0, 0, 30, 20);

    m_windowMap = TWindow(30, 0, 70, 20);

    m_windowMenu = TWindow(0, 20, 30, 6);

    m_windowSubmenu = TWindow(30, 20, 70, 6);

    m_windowMessage = TWindow(0, 26, WINDOW_WIDTH, 3);

    keypad(m_windowMap.window, TRUE); 
    keypad(m_windowMenu.window, TRUE); 
    keypad(m_windowSubmenu.window, TRUE); 
}

void CGraphicController::renderLayout() 
{   
    // HEIGHT, WIDTH, starty, startx
    unique_lock<mutex> ul(m_mtx);
    
    box(m_windowStats.window, 0, 0);
    mvwprintw(m_windowStats.window, 0, 2, " Statistics ");
    wrefresh(m_windowStats.window);
    
    box(m_windowMap.window, 0, 0);
    mvwprintw(m_windowMap.window, 0, 2, " Map ");
    /*
    mvwprintw(m_windowMap.window, 4, 50, "R - Residential");
    mvwprintw(m_windowMap.window, 6, 50, "H - Hospital");
    mvwprintw(m_windowMap.window, 8, 50, "B - Business");
    mvwprintw(m_windowMap.window, 10, 50, "U - University");
    mvwprintw(m_windowMap.window, 12, 50, "L - Laboratory");
    wrefresh(m_windowMap.window);
    */
    
    box(m_windowMenu.window, 0, 0);
    mvwprintw(m_windowMenu.window, 0, 2, " Menu ");
    wrefresh(m_windowMenu.window);
    
    box(m_windowSubmenu.window, 0, 0);
    mvwprintw(m_windowSubmenu.window, 0, 2, " Options ");
    wrefresh(m_windowSubmenu.window);
    
    box(m_windowMessage.window, 0, 0);
    mvwprintw(m_windowMessage.window, 1, 2, "Message: ");
    wrefresh(m_windowMessage.window);
    
}

void CGraphicController::renderSingleWindowMenu(const std::string & message)
{
    unique_lock<mutex> ul(m_mtx);
    
    clear();
    refresh();
    
    m_windowMenu = TWindow(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    keypad(m_windowMenu.window, TRUE); 

    box(m_windowMenu.window, 0, 0);
    mvwprintw(m_windowMenu.window, 1, 2, message.c_str());
    wrefresh(m_windowMenu.window);

    for (auto it = m_menuOptions.begin(); it != m_menuOptions.end(); ++it) {
        wattron(m_windowMenu.window, A_REVERSE); 
        mvwprintw(m_windowMenu.window, it->y, it->x, it->text.c_str());
        wattroff(m_windowMenu.window, A_REVERSE); 
    }
    wrefresh(m_windowMenu.window);
    
}

void CGraphicController::renderStatistics(const CStatHandler & stats) 
{
    unique_lock<mutex> ul(m_mtx);
    werase(m_windowStats.window);
    box(m_windowStats.window, 0, 0);
    int y = 1;
    mvwprintw(m_windowStats.window, 0, 2, " Statistics ");
    mvwprintw(m_windowStats.window, y++, 2, "- Money: %d", stats.m_money);
    mvwprintw(m_windowStats.window, y++, 2, "- Citizens: %d", stats.m_citizenCnt);
    mvwprintw(m_windowStats.window, y++, 2, "- Students: %d", stats.m_studentCnt);
    mvwprintw(m_windowStats.window, y++, 2, "- Doctors: %d", stats.m_doctorCnt);
    mvwprintw(m_windowStats.window, y++, 2, "- Scientists: %d", stats.m_scientistCnt);
    mvwprintw(m_windowStats.window, y++, 2, "- Infected: %d", stats.m_infected);
    mvwprintw(m_windowStats.window, y++, 2, "- Deaths by virus: %d", stats.m_deathsByVirus);
    mvwprintw(m_windowStats.window, y++, 2, "- Other deaths: %d", stats.m_deathsByOther);
    mvwprintw(m_windowStats.window, y++, 2, "- Masks: %d", stats.m_masks);
    mvwprintw(m_windowStats.window, y++, 2, "- Stocks: %d", stats.m_stocks);
    mvwprintw(m_windowStats.window, y++, 2, "- Epidemic: %s", (stats.m_epidemic <= 0) ? "Yes" : ("in " + to_string(stats.m_epidemic)).c_str());
    mvwprintw(m_windowStats.window, y++, 2, "- Mandatory masks: %s", stats.m_mandatoryMasks ? "Yes" : "No");
    mvwprintw(m_windowStats.window, y++, 2, "- Schools: %s", stats.m_schoolsClosed ? "Closed" : "Open");
    mvwprintw(m_windowStats.window, y++, 2, "- Businesses: %s", stats.m_businessClosed ? "Closed" : "Open");
    mvwprintw(m_windowStats.window, y++, 2, "- Lockdown: %s", stats.m_lockdown ? "Yes" : "No");
    mvwprintw(m_windowStats.window, y++, 2, "- Current R: %.1f", stats.m_virusR);
    mvwprintw(m_windowStats.window, y++, 2, "- Healthcare: %d", stats.m_investmentIntoHealthcare);
    mvwprintw(m_windowStats.window, y++, 2, "- Science: %d", stats.m_investmentIntoScience);
    wrefresh(m_windowStats.window);
}

void CGraphicController::setMenuOptions(const std::vector<TMenu> & options)
{
    m_menuOptions = options;
}

void CGraphicController::renderMenu() 
{
    unique_lock<mutex> ul(m_mtx);
    for (auto it = m_menuOptions.begin(); it != m_menuOptions.end(); ++it) {
        wattron(m_windowMenu.window, A_REVERSE); 
        mvwprintw(m_windowMenu.window, it->y, it->x, it->text.c_str());
        wattroff(m_windowMenu.window, A_REVERSE); 
    }
    wrefresh(m_windowMenu.window);
}

void CGraphicController::renderSubmenu(const CCell * cell, int selected_x, int selected_y) 
{
    unique_lock<mutex> ul(m_mtx);
    int x = 2;
    int y = 1;
    werase(m_windowSubmenu.window);
    box(m_windowSubmenu.window, 0, 0);
    mvwprintw(m_windowSubmenu.window, 0, 2, " Options ");
    mvwprintw(m_windowSubmenu.window, y, x, "[%d;%d]: %s", selected_x, selected_y, cell->getInfo().c_str());
    m_submenuOptions = cell->getOptions();
    for (auto & it : m_submenuOptions) {
        wattron(m_windowSubmenu.window, A_REVERSE); 
        mvwprintw(m_windowSubmenu.window, it.y, it.x, "%s", it.text.c_str());
        wattroff(m_windowSubmenu.window, A_REVERSE); 
    }
    wrefresh(m_windowSubmenu.window);
}

void CGraphicController::clearSubmenu()
{
    m_submenuOptions.clear();
    werase(m_windowSubmenu.window);
    box(m_windowSubmenu.window, 0, 0);
    wrefresh(m_windowSubmenu.window);
}

void CGraphicController::renderMap(CMap * map, int highlightX, int highlightY) 
{
    unique_lock<mutex> ul(m_mtx);
    int rows = map->getRows() * 2;
    int columns = map->getColumns();
    int i, j;
    int x = 7, y = 2;
    int idx = 1;
    int currentRow = 1;
    int currentColumn = 1;

    for (j = 0; j < columns; j++, x += 4) {
        mvwprintw(m_windowMap.window, y, x, "  %d ", idx++);
        if (j == columns-1)
            mvwprintw(m_windowMap.window, y, x+4, " ");
    }
    mvwprintw(m_windowMap.window, y, x, "  x  ");
    x = 7;
    y++;
    for (j = 0; j < columns; j++, x += 4) {
        mvwprintw(m_windowMap.window, y, x, "+---");
        if (j == columns-1)
            mvwprintw(m_windowMap.window, y, x+4, "+");
    }
    y++;
    idx = 1;
    for (i = 0; i < rows; i++, y++) {
        x = 5;
        if (i % 2) {
            x += 2;
            for (j = 0; j < columns; j++, x += 4) {
                mvwprintw(m_windowMap.window, y, x, "+---");
                if (j == columns-1)
                    mvwprintw(m_windowMap.window, y, x+4, "+");
            }
        }
        else {
            mvwprintw(m_windowMap.window, y, x, "%d ", idx++);
            x += 2;
            currentColumn = 1;
            for (j = 0; j < columns; j++, x += 4) {
                mvwprintw(m_windowMap.window, y, x, "|");
                if (currentRow == highlightY && currentColumn == highlightX) wattron(m_windowMap.window, A_REVERSE); 
                mvwprintw(m_windowMap.window, y, x+1, "%s", map->getCells().at(currentRow-1).at(currentColumn-1)->draw().c_str());
                if (currentRow == highlightY && currentColumn == highlightX) wattroff(m_windowMap.window, A_REVERSE);
                if (j == columns-1)
                    mvwprintw(m_windowMap.window, y, x+4, "|");
                currentColumn++;
            }
            currentRow++;
        }
    }

    mvwprintw(m_windowMap.window, y, 5, "y");
    wrefresh(m_windowMap.window);
}


void CGraphicController::printMessage(const string & message)
{
    unique_lock<mutex> ul(m_mtx);
    werase(m_windowMessage.window);
    box(m_windowMessage.window, 0, 0);
    mvwprintw(m_windowMessage.window, 1, 2, "Message: ");
    mvwprintw(m_windowMessage.window, 1, 11, message.c_str());
    wrefresh(m_windowMessage.window);
}

int CGraphicController::mouseInput(int & x, int & y) 
{
    int c_menu = wgetch(m_windowMenu.window);
    switch (c_menu) {
        case KEY_MOUSE:
            if (getmouse(&m_event) == OK) {
                if (m_event.bstate & BUTTON1_CLICKED) {
                    x = m_event.x;
                    y = m_event.y;
                    if ( m_event.y >= m_windowMenu.y 
                        && m_event.y <= m_windowMenu.y + m_windowMenu.sizeY 
                        && m_event.x >= m_windowMenu.x 
                        && m_event.x <= m_windowMenu.x + m_windowMenu.sizeX)
                        return MENU_CLICKED;
                    else if ( m_event.y >= m_windowSubmenu.y 
                        && m_event.y <= m_windowSubmenu.y + m_windowSubmenu.sizeY 
                        && m_event.x >= m_windowSubmenu.x 
                        && m_event.x <= m_windowSubmenu.x + m_windowSubmenu.sizeX)
                        return SUBMENU_CLICKED;
                    else if ( m_event.y >= m_windowMap.y 
                        && m_event.y <= m_windowMap.y + m_windowMap.sizeY 
                        && m_event.x >= m_windowMap.x 
                        && m_event.x <= m_windowMap.x + m_windowMap.sizeX)
                        return MAP_CLICKED;
                }
            }
            break;
    }
    return 1;
}

int CGraphicController::proceedMenuClicked(int x, int y) 
{
    int idx = 0;
    for (auto it = m_menuOptions.begin(); it != m_menuOptions.end(); ++it, idx++) {
        int rangeMinX = m_windowMenu.x + it->x;
        int rangeMinY = m_windowMenu.y + it->y;
        int rangeMaxX = m_windowMenu.x + it->x + it->text.length();
        int rangeMaxY = m_windowMenu.y + it->y;
        if (x >= rangeMinX && x <= rangeMaxX && y >= rangeMinY && y <= rangeMaxY) {
            return idx;
        }
    }
    return -1;
}

int CGraphicController::proceedSubmenuClicked(int x, int y) 
{
    for (auto it = m_submenuOptions.begin(); it != m_submenuOptions.end(); ++it) {
        int rangeMinX = m_windowSubmenu.x + it->x;
        int rangeMinY = m_windowSubmenu.y + it->y;
        int rangeMaxX = m_windowSubmenu.x + it->x + it->text.length();
        int rangeMaxY = m_windowSubmenu.y + it->y;
        if (x >= rangeMinX && x <= rangeMaxX && y >= rangeMinY && y <= rangeMaxY) {
            return it->return_value;
        }
    }
    return -1;
}

int CGraphicController::proceedMapClicked(CMap * map, int x, int y, int & selected_x, int & selected_y) 
{
    int startX = m_windowMap.x + 7;
    int startY = m_windowMap.y + 4;
    int posX = startX + 1;
    int posY = startY;

    for (int i = 1; i <= map->getRows(); i++) {
        for (int j = 1; j <= map->getColumns(); j++) {
            if (x >= posX && x <= posX + 3 && y == posY) {
                renderMap(map, j, i);
                selected_x = j;
                selected_y = i;
                return 1;
            }
            posX += 4;
        }
        posX = startX + 1;
        posY += 2;
    }
    return 0;
}