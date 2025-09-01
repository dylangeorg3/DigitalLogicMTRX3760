// File: logic_gates.cpp
// Author: Dylan George
// Date Modified: 1st September 2025
// Description: Implementation file for logic gate classes and functions.

//--Includes-------------------------------------------------------------------
#include "logic_gates.hpp"
#include <iostream>

//---cWire Implementation------------------------------------------------------
cWire::cWire() {
  mNumOutputConnections = 0; // Initialize number of output connections to zero
}
//---
void cWire::AddOutputConnection( cLogicGate* apGateToDrive, int aGateInputToDrive ) {

  mpGatesToDrive[mNumOutputConnections] = apGateToDrive;        // Store pointer to gate to drive
  mGateInputIndices[mNumOutputConnections] = aGateInputToDrive; // Store which input of the gate to drive
  ++mNumOutputConnections; // Increment number of output connections
}
//---
void cWire::DriveLevel( eLogicLevel aNewLevel ) {

  for( int i=0; i<mNumOutputConnections; ++i ) // For each connected output
    mpGatesToDrive[i]->DriveInput( mGateInputIndices[i], aNewLevel ); // Set the input of the gate to the new level
}


//---cLogicGate Implementation------------------------------------------------
cLogicGate::cLogicGate(int aNumInputs, int aNumOutputs)
  : mInputs(aNumInputs, LOGIC_UNDEFINED),
    mOutputValues(aNumOutputs, LOGIC_UNDEFINED),
    mpOutputConnections(aNumOutputs, nullptr) {}
//---
cLogicGate::~cLogicGate() {}
//---
eLogicLevel cLogicGate::GetOutputState(int aOutputIndex) {
  ComputeOutput();
  return mOutputValues[aOutputIndex]; // Return the current output value
}
//---
void cLogicGate::ConnectOutput(int aOutputIndex, cWire* apOutputConnection ) {

  mpOutputConnections[aOutputIndex] = apOutputConnection; // Set the output wire connection
}
//---
void cLogicGate::DriveInput( int aInputIndex, eLogicLevel aNewLevel ) {

  mInputs[aInputIndex] = aNewLevel; // Set the specified input to the new logic level
  ComputeOutput(); // Recompute the output value
}


//---cAndGate Implementation--------------------------------------------------
cAndGate::cAndGate() : cLogicGate(/*inputs*/2, /*outputs*/1) {}
cAndGate::~cAndGate() {}
//---
void cAndGate::ComputeOutput() {

  eLogicLevel NewVal = LOGIC_LOW; // Default to LOW (AND gate)

  if( mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED ) {
    NewVal = LOGIC_UNDEFINED; // If any input is undefined, output is undefined
  }
  else if( mInputs[0] == LOGIC_HIGH && mInputs[1] == LOGIC_HIGH ) {
    NewVal = LOGIC_HIGH; // Both inputs HIGH, output HIGH
  }

  mOutputValues[0] = NewVal;
  
  if( mpOutputConnections[0] != NULL ) {
    mpOutputConnections[0]->DriveLevel( mOutputValues[0] ); // Drive output wire
  }
}
//---
void cAndGate::TestOutputs() {
    std::cout << "\nTest Output for AND Gate" << std::endl;
    std::cout << "A B | Out" << std::endl;
    std::cout << "-------------" << std::endl;
    for (int i = 0; i < 4; i++) {
        int A = (i >> 1) & 1;
        int B = i & 1;
        DriveInput(0, A ? LOGIC_HIGH : LOGIC_LOW);
        DriveInput(1, B ? LOGIC_HIGH : LOGIC_LOW);
        ComputeOutput();
        int Out = GetOutputState(0);
        std::cout << A << " " << B << " |  " << Out << std::endl;
    }
}


//---cNandGate Implementation--------------------------------------------------
cNandGate::cNandGate() : cLogicGate(/*inputs*/2, /*outputs*/1) {}
cNandGate::~cNandGate() {}
//---
void cNandGate::ComputeOutput() {

  eLogicLevel NewVal = LOGIC_HIGH; // Default to HIGH (NAND gate)

  if( mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED ) {
    NewVal = LOGIC_UNDEFINED; // If any input is undefined, output is undefined
  }
  else if( mInputs[0] == LOGIC_HIGH && mInputs[1] == LOGIC_HIGH ) {
    NewVal = LOGIC_LOW; // Both inputs HIGH, output LOW
  }

  mOutputValues[0] = NewVal;
  
  if( mpOutputConnections[0] != NULL ) {
    mpOutputConnections[0]->DriveLevel( mOutputValues[0] ); // Drive output wire
  }
}
//---
void cNandGate::TestOutputs() {
    std::cout << "\nTest Output for NAND Gate" << std::endl;
    std::cout << "A B | Out" << std::endl;
    std::cout << "-------------" << std::endl;
    for (int i = 0; i < 4; i++) {
        int A = (i >> 1) & 1;
        int B = i & 1;
        DriveInput(0, A ? LOGIC_HIGH : LOGIC_LOW);
        DriveInput(1, B ? LOGIC_HIGH : LOGIC_LOW);
        ComputeOutput();
        int Out = GetOutputState(0);
        std::cout << A << " " << B << " |  " << Out << std::endl;
    }
}


//---cOrGate Implementation---------------------------------------------------
cOrGate::cOrGate() : cLogicGate(/*inputs*/2, /*outputs*/1) {}
cOrGate::~cOrGate() {}
//---
void cOrGate::ComputeOutput() {

  eLogicLevel NewVal = LOGIC_LOW; // Default to LOW (OR gate)

  if( mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED ) {
    NewVal = LOGIC_UNDEFINED; // If any input is undefined, output is undefined
  }
  else if( mInputs[0] == LOGIC_LOW && mInputs[1] == LOGIC_LOW ) {
    NewVal = LOGIC_LOW; // Both inputs LOW, output LOW
  }
  else {
    NewVal = LOGIC_HIGH; // Any input HIGH, output HIGH
  }

  mOutputValues[0] = NewVal;
  
  if( mpOutputConnections[0] != NULL ) {
    mpOutputConnections[0]->DriveLevel( mOutputValues[0] ); // Drive output wire
  }
}
//---
void cOrGate::TestOutputs() {
    std::cout << "\nTest Output for OR Gate" << std::endl;
    std::cout << "A B | Out" << std::endl;
    std::cout << "-------------" << std::endl;
    for (int i = 0; i < 4; i++) {
        int A = (i >> 1) & 1;
        int B = i & 1;
        DriveInput(0, A ? LOGIC_HIGH : LOGIC_LOW);
        DriveInput(1, B ? LOGIC_HIGH : LOGIC_LOW);
        ComputeOutput();
        int Out = GetOutputState(0);
        std::cout << A << " " << B << " |  " << Out << std::endl;
    }
}


//---cXorGate Implementation--------------------------------------------------
cXorGate::cXorGate() : cLogicGate(/*inputs*/2, /*outputs*/1) {}
cXorGate::~cXorGate() {}
//---
void cXorGate::ComputeOutput() {

  eLogicLevel NewVal = LOGIC_LOW; // Default to LOW (XOR gate)

  if( mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED ) {
    NewVal = LOGIC_UNDEFINED; // If any input is undefined, output is undefined
  }
  else if((mInputs[0] == LOGIC_HIGH && mInputs[1] == LOGIC_LOW) || 
          (mInputs[0] == LOGIC_LOW && mInputs[1] == LOGIC_HIGH)) {
    NewVal = LOGIC_HIGH; // Inputs differ, output HIGH
  }

  mOutputValues[0] = NewVal;
  
  if( mpOutputConnections[0] != NULL ) {
    mpOutputConnections[0]->DriveLevel( mOutputValues[0] ); // Drive output wire
  }
}
//---
void cXorGate::TestOutputs() {
    std::cout << "\nTest Output for XOR Gate" << std::endl;
    std::cout << "A B | Out" << std::endl;
    std::cout << "-------------" << std::endl;
    for (int i = 0; i < 4; i++) {
        int A = (i >> 1) & 1;
        int B = i & 1;
        DriveInput(0, A ? LOGIC_HIGH : LOGIC_LOW);
        DriveInput(1, B ? LOGIC_HIGH : LOGIC_LOW);
        ComputeOutput();
        int Out = GetOutputState(0);
        std::cout << A << " " << B << " |  " << Out << std::endl;
    }
}