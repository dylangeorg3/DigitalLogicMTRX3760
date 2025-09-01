// File: circuit.hpp
// Author: Dylan George
// Date Modified: 1st September 2025
// Description: Header file for circuit-related class declarations (user file, content not specified).

#include "logic_gates.hpp" // Include logic gate definitions

// Input indices for generic circuits
const int INPUT_A = 0; // First input
const int INPUT_B = 1; // Second input
const int INPUT_CARRY = 2; // Carry input (for adders)

// Output indices for generic circuits
const int SUM_OUTPUT = 0;   // Sum output
const int CARRY_OUTPUT = 1; // Carry output

// Half Adder input indices
enum HalfAdderInput {
    HA_A = 0, // Input A
    HA_B = 1  // Input B
};
// Half Adder output indices
enum HalfAdderOutput {
    HA_SUM = 0,   // Sum output
    HA_CARRY = 1  // Carry output
};

// Full Adder input indices
enum FullAdderInput {
    FA_A = 0,   // Input A
    FA_B = 1,   // Input B
    FA_CIN = 2  // Carry input
};
// Full Adder output indices
enum FullAdderOutput {
    FA_SUM = 0,   // Sum output
    FA_CARRY = 1  // Carry output
};

// cThreeBitAdder input indices
enum {
    A0 = 0, A1 = 1, A2 = 2, // First operand bits
    B0 = 3, B1 = 4, B2 = 5  // Second operand bits
};
// cThreeBitAdder output indices
enum {
    S0 = 0, S1 = 1, S2 = 2, COUT = 3 // Sum bits and carry out
};

// Base class for all subcircuits, inherits from cLogicGate
class cSubCircuit : public cLogicGate {
    public:
        cSubCircuit(int aNumInputs, int aNumOutputs); // Constructor with input/output count
        virtual ~cSubCircuit() {};

    protected:
        std::vector<cWire> mWires; // Wires connecting gates within the subcircuit
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

        cAndGate mAND1; // AND gate for A and B
        cAndGate mAND2; // AND gate for intermediate sum and carry
        cXorGate mXOR1; // XOR gate for A and B
        cXorGate mXOR2; // XOR gate for sum and carry
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
};

// Simulation class to run circuit tests
class cSimulation {
    public:
        cSimulation() {};
        ~cSimulation() {};

        void RunSimulation(); // Run all circuit tests

    private:
};