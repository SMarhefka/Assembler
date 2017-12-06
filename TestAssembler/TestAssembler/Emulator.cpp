// Svetlana Marhefka
// Implementation of the emulation class.

#include "stdafx.h"
#include "SymTab.h"
#include "Emulator.h"
#include "Errors.h"

/**/
/*
Emulator::InsertMemory() Emulator::InsertMemory()

NAME
Emulator::InsertMemory - Constructor for the emulator.

SYNOPSIS
bool Emulator::InsertMemory(int a_location, int a_contents)
a_location	--> The location that the contents will be placed in memory.
a_contents	--> The actual content

DESCRIPTION
The purpose of this function is to insert a_contents into 
m_memory. The memory specific memory location is 
a_location.  If a_location is greater than 9999 then our
contents is not inserted

RETURNS
Returns true is we have no errors. Returns false if the
contents cannot be inseretd for any reason

*/
/**/
bool Emulator::InsertMemory(int a_location, int a_contents)
{
	// VC3600 does not have more than 10000 memory locations. Cannot insert.
	if(a_location > (MEMSZ - 1))
	{
		return false;
	}
	// Adds to memory location.
	else
	{
		m_memory[a_location] = a_contents;
		return true;
	}
}

/**/
/*
Emulator::RunProgram() Emulator::RunProgram()

NAME
Emulator::RunProgram - Runs VC3600 program.

SYNOPSIS
bool Emulator::RunProgram()

DESCRIPTION
The purpose of this function is to run the VC3600 program.
The emulator is just one big switch statement that has been
prepared with 13 cases.

RETURNS
Returns true if the program runs. Returns false if program
runs into errors

*/
/**/
bool Emulator::RunProgram()
{
	// Check to see if we have any errors
	if(Errors::IsVectorEmpty() == false)
	{	// If it isn't empty then we return false
		return false;
	}

	// Initialize the location variable
	int em_location = 0;
	// Initialize the operation code
	int em_opCode = 0;
	// Initialize the address location
	int em_operand = 0;
	// Initialize the user input this is used
	// in case #7
	string a_input;

	// Initialize the accumulator variable
	m_acceumulator = 0;
	
	for(em_location = 100; em_location < MEMSZ; em_location++)
	{
		// Check to make sure that our memory is not = 0
		if(m_memory[em_location] != 0)
		{
			// The operation code the the result of dividing
			// the memory location and 1000
			em_opCode = m_memory[em_location] / 1000;
			// The operand is the remainder between the memory 
			// location and 1000
			em_operand = m_memory[em_location] % 1000;

			// Check to see if we have enough memory
			if(m_acceumulator > 999999)
			{
				// If we don't then we take the remainder
				m_acceumulator = m_acceumulator % 1000000;
				cout << "In line 75 of Emulator.cpp\n";
				cout << "m_acceumulator: " << m_acceumulator << endl;
			}
			// Check to see if our operand value is too big
			if(em_operand > 9999)
			{
				// If
				cout << "Error: Memory location is not valid\n";
				return false;
			}
		}

		switch(em_opCode)
		{
			// ADD CASE
			case 1:
			// ADD = ACC <- c(ACC) + c(ADDR)
			m_acceumulator = m_acceumulator + m_memory[em_operand];
			break;

			// SUB CASE
			case 2:
			// SUB = ACC <- c(ACC) - c(ADDR)
			m_acceumulator = m_acceumulator - m_memory[em_operand];
			break;

			// MULTIPLY CASE
			case 3:
			// MULTIPLY = ACC <- c(ACC) * c(ADDR)
			m_acceumulator = m_acceumulator * m_memory[em_operand];
			break;

			// DIVIDE CASE
			case 4:
			// DIVIDE = ACC <- c(ACC) / c(ADDR)
			m_acceumulator = m_acceumulator / m_memory[em_operand];
			break;

			// LOAD CASE
			case 5:
			// LOAD = ACC <- c(ADDR)
			m_acceumulator = m_memory[em_operand];
			break;

			// STORE CASE
			case 6:
			// STORE = ADDR <- c(ACC)
			m_memory[em_operand] = m_acceumulator;
			break;

			// READ CASE
			case 7:
			// This prompts the user for an input
			cout << "?";
			cin >> a_input;

			// Check the length of the string
			// 0 - 5 is 6 characters
			if(a_input.length() > 5)
			{
				// If the length is more than 6 characters
				// then get the first 6 characters
				a_input = a_input.substr(0, 5);
			}
			// Convert the string to an integer
			m_memory[em_operand] = stoi(a_input);
			break;

			// WRITE CASE
			case 8:
			// c(ADDR) is displayed.
			cout << m_memory[em_operand] << endl;
			break;

			// BRANCH CASE
			case 9:
			// Go to ADDR for next instruction
			em_location = em_operand;
			break;

			// BRANCH MINUS
			case 10:
			if(m_acceumulator < 0)
			{
				em_location = em_operand;
			} // Go to ADDR if c(ACC) < 0.
			break;

			// BRANCH ZERO
			case 11:
			// Go to ADDR if c(ACC) = 0.
			if(m_acceumulator == 0)
			{
				em_location = em_operand;
			} 
			break;

			// BRANCH PLUS
			case 12:
			// Go to ADDR if c(ACC) > 0.
			if(m_acceumulator > 0)
			{
				em_location = (em_operand--);
			} 
			break;

			//	HALT CASE
			case 13:
			// This case will stop the program so all we need
			// to do is return true
			return true;
			break;

			// This is our error case
			default:
			string m_Error;
			m_Error = "Error: Illegal OpCode found\n";
			Errors::RecordError(m_Error);
			cout << m_Error << endl;
			return false;
			break;
		}
	}
	return true;
}