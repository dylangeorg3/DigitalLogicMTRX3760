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

// Forward declarations for gate classes
class cNandGate;
class cLogicGate;


class cLogic {
    public:
        // eLogicLevel: Represents the possible states of a digital logic signal.
        // Used for all gate and wire logic levels throughout the simulator.
        enum eLogicLevel {
            LOGIC_UNDEFINED = -1, // Line state is undefined (floating or not driven)
            LOGIC_LOW,            // Logic low (0)
            LOGIC_HIGH            // Logic high (1)
        };
};


// cWire connects devices in the simulation
// Each wire has a single input and may drive multiple outputs
class cWire {
    public:
        cWire(); // Constructor
        virtual ~cWire() {} // Destructor
       
        void AddOutputConnection( cLogicGate* apGateToDrive, int aGateInputToDrive );  // Adds a connection from this wire to a gate input
        void DriveLevel( cLogic::eLogicLevel aNewLevel ); // Drives the wire's value to all connected outputs
        
    private:
        static const int MaxFanout = 4;                // Maximum number of gates a wire can drive (fanout)
        int mNumOutputConnections;            // Number of outputs currently connected
        cLogicGate* mpGatesToDrive[MaxFanout]; // Array of pointers to gates driven by this wire
        int mGateInputIndices[MaxFanout];     // Array of input indices for each driven gate
};


// Base class for all logic gates
class cLogicGate {
    public:
        cLogicGate(int aNumInputs, int aNumOutputs); // Constructor with input/output count
        virtual ~cLogicGate() = default; // Destructor

        virtual void ConnectOutput( int aOutputIndex, cWire* apOutputConnection ); // Connects the output of this gate to a wire
        virtual void DriveInput( int aInputIndex, cLogic::eLogicLevel aNewLevel ); // Drives an input of this gate to a new logic level
        virtual cLogic::eLogicLevel GetOutputState(int aOutputIndex); // Gets the current output state of the gate
        virtual void TestOutputs() {}; // Print all output combinations 
        virtual void ComputeOutput() {}; // Computes the output value based on inputs

    protected:
        std::vector<cLogic::eLogicLevel> mInputs;           // Input values for the gate
        std::vector<cLogic::eLogicLevel> mOutputValues;     // Output values for the gate
        std::vector<cWire*> mpOutputConnections;            // Output wire connections for each output

        enum : int { INPUT_A, INPUT_B, INPUT_CARRY}; // Generic input indices
        enum : int { OUTPUT = 0, SUM_OUTPUT = 0, CARRY_OUTPUT}; // Generic output indices
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