// File: circuit.cpp
// Author: Dylan George
// Date Modified: 1st September 2025
// Description: Implementation file for circuit-related classes and functions.

#include "circuits.hpp"

//---cSubCircuit Implementation------------------------------------------------
cSubCircuit::cSubCircuit(int aNumInputs, int aNumOutputs) 
    : cLogicGate( aNumInputs, aNumOutputs) {

        ComputeOutput(); // Compute initial output values
}


//---cHalfAdder Implementation------------------------------------------------
cHalfAdder::cHalfAdder() : cSubCircuit(/*inputs*/2, /*outputs*/2) {
    ComputeOutput(); // Compute initial output values
}
//---
void cHalfAdder::ComputeOutput() {
    mAND.DriveInput(0, mInputs[HA_A]); // Set first input of AND gate
    mAND.DriveInput(1, mInputs[HA_B]); // Set second input of AND gate
    mAND.ComputeOutput(); // Calculate AND gate output

    mXOR.DriveInput(0, mInputs[HA_A]); // Set first input of XOR gate
    mXOR.DriveInput(1, mInputs[HA_B]); // Set second input of XOR gate
    mXOR.ComputeOutput(); // Calculate XOR gate output

    mOutputValues[HA_SUM] = mXOR.GetOutputState(0); // Store XOR output as SUM
    mOutputValues[HA_CARRY] = mAND.GetOutputState(0); // Store AND output as CARRY
}
//---
void cHalfAdder::TestOutputs() {
    std::cout << "\nTest Output for Half Adder" << std::endl;
    std::cout << "A B | Sum Cout" << std::endl;
    std::cout << "----------------" << std::endl;
    for (int i = 0; i < 4; i++) {
        int A = (i >> 1) & 1;
        int B = i & 1;
        DriveInput(0, A ? LOGIC_HIGH : LOGIC_LOW);
        DriveInput(1, B ? LOGIC_HIGH : LOGIC_LOW);
        ComputeOutput();
        int Sum = GetOutputState(SUM_OUTPUT);
        int Cout = GetOutputState(CARRY_OUTPUT);
        std::cout << A << " " << B << " |  " << Sum << "    " << Cout << std::endl;
    }
}


//---cFullAdder Implementation------------------------------------------------
cFullAdder::cFullAdder() : cSubCircuit(/*inputs*/3, /*outputs*/2) {
    ComputeOutput();
}
//---
void cFullAdder::ComputeOutput() {
    mAND1.DriveInput(0, mInputs[FA_A]); // Set first input of AND gate
    mAND1.DriveInput(1, mInputs[FA_B]); // Set second input of AND gate
    mAND1.ComputeOutput(); // Calculate AND gate output

    mXOR1.DriveInput(0, mInputs[FA_A]); // Set first input of XOR gate
    mXOR1.DriveInput(1, mInputs[FA_B]); // Set second input of XOR gate
    mXOR1.ComputeOutput(); // Calculate XOR gate output

    mXOR2.DriveInput(0, mXOR1.GetOutputState(0));
    mXOR2.DriveInput(1, mInputs[FA_CIN]);
    mXOR2.ComputeOutput();

    mOutputValues[FA_SUM] = mXOR2.GetOutputState(0); // Store XOR2 output as SUM

    mAND2.DriveInput(0, mXOR1.GetOutputState(0));
    mAND2.DriveInput(1, mInputs[FA_CIN] );
    mAND2.ComputeOutput();

    mOR.DriveInput(0, mAND1.GetOutputState(0));
    mOR.DriveInput(1, mAND2.GetOutputState(0));
    mOR.ComputeOutput();

    mOutputValues[FA_CARRY] = mOR.GetOutputState(0); // Store OR output as CARRY
}
//---
void cFullAdder::TestOutputs() {
    std::cout << "\nTest Output for Full Adder " << std::endl;
    std::cout << "A B Cin | Sum Cout" << std::endl;
    std::cout << "------------------" << std::endl;

    // Loop through all input combinations (0 to 7)
    for (int i = 0; i < 8; i++) {
        // Extract bits for A, B, Cin
        int A   = (i >> 2) & 1;  // MSB
        int B   = (i >> 1) & 1;  // Middle bit
        int Cin =  i       & 1;  // LSB

        // Drive inputs
        DriveInput(0, A ? LOGIC_HIGH : LOGIC_LOW);
        DriveInput(1, B ? LOGIC_HIGH : LOGIC_LOW);
        DriveInput(2, Cin ? LOGIC_HIGH : LOGIC_LOW);

        // Compute output if needed
        ComputeOutput();

        // Read outputs
        int Sum  = GetOutputState(SUM_OUTPUT);
        int Cout = GetOutputState(CARRY_OUTPUT);

        // Print in ordered table
        std::cout << A << " " << B << "  " << Cin
                  << "   |  " << Sum << "    " << Cout << std::endl;
    }
}



//---cThreeBitAdder Implementation------------------------------------------------
// Constructor for ThreeBitAdder, sets up a 6-input, 4-output subcircuit
cThreeBitAdder::cThreeBitAdder() : cSubCircuit(/*inputs*/6, /*outputs*/4) {
    ComputeOutput();
};
//---
void cThreeBitAdder::ComputeOutput() {
    // Stage 0: LSB uses Half Adder on A0, B0
    mHalfAdder.DriveInput(0, mInputs[A0]);
    mHalfAdder.DriveInput(1, mInputs[B0]);
    eLogicLevel s0   = mHalfAdder.GetOutputState(SUM_OUTPUT);    // from half adder
    eLogicLevel c01  = mHalfAdder.GetOutputState(CARRY_OUTPUT);  // carry to next stage
    mOutputValues[S0] = s0;

    // Stage 1: Full Adder on A1, B1 with Cin = c01
    mFullAdder1.DriveInput(0, mInputs[A1]);           // A1
    mFullAdder1.DriveInput(1, mInputs[B1]);           // B1
    mFullAdder1.DriveInput(2, c01);                   // Cin from previous stage
    eLogicLevel s1   = mFullAdder1.GetOutputState(SUM_OUTPUT);
    eLogicLevel c12  = mFullAdder1.GetOutputState(CARRY_OUTPUT);  // carry to next stage
    mOutputValues[S1] = s1;

    // Stage 2 (MSB): Full Adder on A2, B2 with Cin = c12
    mFullAdder2.DriveInput(0, mInputs[A2]);           // A2
    mFullAdder2.DriveInput(1, mInputs[B2]);           // B2
    mFullAdder2.DriveInput(2, c12);                   // Cin from previous stage
    eLogicLevel s2   = mFullAdder2.GetOutputState(SUM_OUTPUT);
    eLogicLevel cout = mFullAdder2.GetOutputState(CARRY_OUTPUT);
    mOutputValues[S2]  = s2;
    mOutputValues[COUT]= cout;
}
//---
void cThreeBitAdder::TestOutputs() {
    std::cout << "\nTest Output for 3-bit Adder\n";
    std::cout << "A2 A1 A0 | B2 B1 B0 || COUT S2 S1 S0\n";
    std::cout << "-------------------------------------\n";

    // Iterate all 3-bit A and B values
    for (int A = 0; A < 8; ++A) {
        for (int B = 0; B < 8; ++B) {
            // Drive inputs (A2..A0, B2..B0)
            DriveInput(A2, (A & 0b100) ? LOGIC_HIGH : LOGIC_LOW);
            DriveInput(A1, (A & 0b010) ? LOGIC_HIGH : LOGIC_LOW);
            DriveInput(A0, (A & 0b001) ? LOGIC_HIGH : LOGIC_LOW);

            DriveInput(B2, (B & 0b100) ? LOGIC_HIGH : LOGIC_LOW);
            DriveInput(B1, (B & 0b010) ? LOGIC_HIGH : LOGIC_LOW);
            DriveInput(B0, (B & 0b001) ? LOGIC_HIGH : LOGIC_LOW);

            // Read outputs (ComputeOutput() is already triggered by DriveInput/reads)
            int s0   = GetOutputState(S0);
            int s1   = GetOutputState(S1);
            int s2   = GetOutputState(S2);
            int cout = GetOutputState(COUT);

            std::cout
                << ((A>>2)&1) << "  " << ((A>>1)&1) << "  " << (A&1)
                << " | "
                << ((B>>2)&1) << "  " << ((B>>1)&1) << "  " << (B&1)
                << " ||   "
                << cout << "    " << s2 << "  " << s1 << "  " << s0
                << "\n";
        }
    }
}


// Runs the simulation by creating a HalfAdder, testing its outputs, and cleaning up
void cSimulation::RunSimulation() {

    cHalfAdder* HalfAdder = new cHalfAdder; // Create a new HalfAdder
    HalfAdder->TestOutputs(); // Run all test cases for HalfAdder
    delete HalfAdder; // Clean up

    cFullAdder* FullAdder = new cFullAdder; // Create a new FullAdder
    FullAdder->TestOutputs(); // Run all test cases for FullAdder
    delete FullAdder; // Clean up

    cThreeBitAdder* ThreeBitAdder = new cThreeBitAdder; // Create a new FullAdder
    ThreeBitAdder->TestOutputs(); // Run all test cases for FullAdder
    delete ThreeBitAdder; // Clean up

}