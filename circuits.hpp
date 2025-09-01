// File: circuit.hpp
// Author: Dylan George
// Date Modified: 1st September 2025
// Description: Header file for circuit-related class declarations (user file, content not specified).

#include "logic_gates.hpp"


const int INPUT_A = 0;
const int INPUT_B = 1;
const int INPUT_CARRY = 2;

const int SUM_OUTPUT = 0;
const int CARRY_OUTPUT = 1;

// Half Adder input indices
enum HalfAdderInput {
    HA_A = 0,
    HA_B = 1
};
// Half Adder output indices
enum HalfAdderOutput {
    HA_SUM = 0,
    HA_CARRY = 1
};

// Full Adder input indices
enum FullAdderInput {
    FA_A = 0,
    FA_B = 1,
    FA_CIN = 2
};
// Full Adder output indices
enum FullAdderOutput {
    FA_SUM = 0,
    FA_CARRY = 1
};

// cThreeBitAdder input indices
enum {
    A0 = 0, A1 = 1, A2 = 2,
    B0 = 3, B1 = 4, B2 = 5
};
// cThreeBitAdder output indices
enum {
    S0 = 0, S1 = 1, S2 = 2, COUT = 3
};


class cSubCircuit : public cLogicGate {
    public:
        cSubCircuit(int aNumInputs, int aNumOutputs);
        virtual ~cSubCircuit() {};


    protected:
        std::vector<cWire> mWires;
};

class cHalfAdder : public cSubCircuit{

    public:
        cHalfAdder();
        virtual ~cHalfAdder() {};

        void TestOutputs() override;

        void ComputeOutput() override;

    protected:

        cAndGate mAND;
        cXorGate mXOR;

    

};

class cFullAdder : public cSubCircuit {
    public:
        cFullAdder();
        virtual ~cFullAdder() {};

        void TestOutputs() override;

    private:
        void ComputeOutput() override;

        cAndGate mAND1;
        cAndGate mAND2;

        cXorGate mXOR1;
        cXorGate mXOR2;

        cOrGate mOR;
        

};

class cThreeBitAdder : public cSubCircuit {
    public:
        cThreeBitAdder();
        virtual ~cThreeBitAdder() {};

        void TestOutputs() override;

    private:
        void ComputeOutput() override;

        cFullAdder mFullAdder1;
        cFullAdder mFullAdder2;
        cHalfAdder mHalfAdder;
        
};



class cSimulation {
    public:
        cSimulation() {};
        ~cSimulation() {};

        void RunSimulation();

    private:
};