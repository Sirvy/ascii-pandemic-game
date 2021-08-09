#include "CCell.hpp"


CCell::CCell() {}

CCell::CCell(const std::string & view) {
    m_view = view;
}

std::string CCell::draw() const 
{
    return m_view;
}