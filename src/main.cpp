#include <iostream>
#include <ctime>
#include "include/CApplication.hpp"

using namespace std;

int main() 
{
    srand(time(nullptr));
    CApplication app;
    app.run();
    return 0;
}