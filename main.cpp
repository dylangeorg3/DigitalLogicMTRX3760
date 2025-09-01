// File: main.cpp
// Author: Dylan George
// Date Modified: 1st September 2025
// Description: Main entry point for the logic circuit simulator program.



#include "logic_gates.hpp"
#include "circuits.hpp"

int main() {

    cSimulation* sim = new cSimulation();
    sim -> RunSimulation();
    delete sim;

    return 0;
}
