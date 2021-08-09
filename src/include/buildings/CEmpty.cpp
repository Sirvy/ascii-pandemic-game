#include "CEmpty.hpp"

using namespace std;

CEmpty::CEmpty(const string & view) 
: CCell(view) {
    m_options = std::vector<TMenu>{
        TMenu(2, 2, "Buy Residential", OPTION_BUY_RESIDENTIAL),
        TMenu(19, 2, "Buy Hospital", OPTION_BUY_HOSPITAL),
        TMenu(33, 2, "Buy Business", OPTION_BUY_BUSINESS),
        TMenu(2, 4, "Buy University", OPTION_BUY_UNIVERSITY),
        TMenu(19, 4, "Buy Laboratory", OPTION_BUY_LABORATORY)
    };
}

string CEmpty::getSaveData() const 
{
    return "empty";
}

void CEmpty::loadSaveData(const std::string & data, CStatHandler * stats)
{
}

void CEmpty::update(CStatHandler & stats)
{
}

vector<TMenu> CEmpty::getOptions() const 
{
    return m_options;
}

string CEmpty::getInfo() const
{
    return "Empty building";
}

void CEmpty::proceedOptionClicked(int option, CStatHandler & stats)
{
    
}