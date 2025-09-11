// File: circuit.hpp
// Author: Dylan George
// Date Modified: 1st September 2025
// Description: Header file for circuit-related class declarations (user file, content not specified).

#include "logic_gates.hpp" // Include logic gate definitions

// Base class for all subcircuits, inherits from cLogicGate
class cSubCircuit : public cLogicGate {
    public:
        cSubCircuit(int aNumInputs, int aNumOutputs); // Constructor with input/output count
        virtual ~cSubCircuit() = default;
};

// Half Adder circuit, inherits from cSubCircuit
class cHalfAdder : public cSubCircuit{
    public:
        cHalfAdder(); // Constructor
        virtual ~cHalfAdder() {};

        void TestOutputs() override; // Print all output combinations
        void ComputeOutput() override; // Compute outputs based on inputs

    protected:
        cAndGate mAND; // AND gate for carry output
        cXorGate mXOR; // XOR gate for sum output
};

// Full Adder circuit, inherits from cSubCircuit
class cFullAdder : public cSubCircuit {
    public:
        cFullAdder(); // Constructor
        virtual ~cFullAdder() {};
        
        void TestOutputs() override; // Print all output combinations

    private:
        void ComputeOutput() override; // Compute outputs based on inputs

        cHalfAdder mHalfAdder1;
        cHalfAdder mHalfAdder2;
        cOrGate mOR;    // OR gate for final carry output
};

// Three Bit Adder circuit, inherits from cSubCircuit
class cThreeBitAdder : public cSubCircuit {
    public:
        cThreeBitAdder(); // Constructor
        virtual ~cThreeBitAdder() {};

        void TestOutputs() override; // Print all output combinations

    private:
        void ComputeOutput() override; // Compute outputs based on inputs

        cFullAdder mFullAdder1; // First full adder
        cFullAdder mFullAdder2; // Second full adder
        cHalfAdder mHalfAdder;  // Half adder for least significant bits
        
        enum : int { A0, A1, A2, B0, B1, B2};   // cThreeBitAdder input indices
        enum : int { S0, S1, S2, COUT};         // cThreeBitAdder output indices
};


// Simulation class to run circuit tests
class cSimulation {
    public:
        cSimulation() {};
        ~cSimulation() {};

        void RunSimulation(); // Run all circuit tests

    private:
        cLogicGate* mptr[7]; // Array of Logic Gate pointers to show polymorphism 
};