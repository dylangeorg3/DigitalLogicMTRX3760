// File: logic_gates.hpp
// Author: Dylan George
// Date Modified: 1st September 2025
// Description: Header file containing class declarations and constants for logic gates.

// Header file for LogicSim
// Contains class declarations and constants for the logic circuit simulator
#ifndef LOGICSIM_V1_HPP
#define LOGICSIM_V1_HPP

#include <iostream>
#include <vector>


// Number of inputs per logic gate (NAND, AND, OR, XOR)
const int InputsPerGate = 2; // Default number of inputs for gates
// Maximum number of gate inputs that one wire output can drive
const int MaxFanout = 4; // Maximum fanout for a wire

// Enum defining the possible states of a logic line
enum eLogicLevel {
    LOGIC_UNDEFINED = -1, // Line state is undefined
    LOGIC_LOW,            // Logic low (0)
    LOGIC_HIGH            // Logic high (1)
};

// Forward declarations for gate classes
class cNandGate;
class cLogicGate;

// cWire connects devices in the simulation
// Each wire has a single input and may drive multiple outputs
class cWire {
    public:
        cWire(); // Constructor
        // Adds a connection from this wire to a gate input
        void AddOutputConnection( cLogicGate* apGateToDrive, int aGateInputToDrive );
        // Drives the wire's value to all connected outputs
        void DriveLevel( eLogicLevel aNewLevel );
    private:
        int mNumOutputConnections;            // Number of outputs connected
        cLogicGate* mpGatesToDrive[MaxFanout]; // List of gates driven by this wire
        int mGateInputIndices[MaxFanout];     // Indices of inputs in each gate
};

// Base class for all logic gates
class cLogicGate {
    public:
        cLogicGate(int aNumInputs, int aNumOutputs); // Constructor with input/output count
        virtual ~cLogicGate(); // Destructor

        // Connects the output of this gate to a wire
        virtual void ConnectOutput( int aOutputIndex, cWire* apOutputConnection );

        // Drives an input of this gate to a new logic level
        virtual void DriveInput( int aInputIndex, eLogicLevel aNewLevel );

        // Gets the current output state of the gate
        virtual eLogicLevel GetOutputState(int aOutputIndex);

        virtual void TestOutputs() = 0; // Print all output combinations (pure virtual)

        // Computes the output value based on inputs
        virtual void ComputeOutput() {};

    protected:
        std::vector<eLogicLevel> mInputs;           // Input values
        std::vector<eLogicLevel> mOutputValues;     // Output values   
        std::vector<cWire*> mpOutputConnections;    // Output wire connections    
};

// AND gate (inherits from cLogicGate)
class cAndGate : public cLogicGate {
    public:
        cAndGate(); // Constructor
        virtual ~cAndGate(); // Destructor

        void TestOutputs() override; // Print all output combinations
        void ComputeOutput() override; // Compute outputs based on inputs
        
};

// OR gate (inherits from cLogicGate)
class cOrGate : public cLogicGate {
    public:
        cOrGate(); // Constructor
        virtual ~cOrGate(); // Destructor

        void TestOutputs() override; // Print all output combinations
        void ComputeOutput() override; // Compute outputs based on inputs
        
};

// XOR gate (inherits from cLogicGate)
class cXorGate : public cLogicGate {
    public:
        cXorGate(); // Constructor
        virtual ~cXorGate(); // Destructor

        void TestOutputs() override; // Print all output combinations
        void ComputeOutput() override; // Compute outputs based on inputs
        
};

// NAND gate (inherits from cLogicGate)
class cNandGate : public cLogicGate {
    public:
        cNandGate(); // Constructor
        virtual ~cNandGate(); // Destructor

        void TestOutputs() override; // Print all output combinations
        
        void ComputeOutput() override; // Compute outputs based on inputs
        
};

#endif // LOGICSIM_V1_HPP
