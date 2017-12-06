// Svetlana Marhefka
// Emulator class - supports the emulation of VC3600 programs
#pragma once;

// UNIX way of preventing multiple inclusions.
#ifndef _EMULATOR_H
#define _EMULATOR_H

// Changed to uppercase to match the flow
// to match the flow of the prevous files
class Emulator
{
public:
	// The size of the memory of the VC3600.
	const static int MEMSZ = 10000;

	Emulator()
	{
		memset(m_memory, 0, MEMSZ * sizeof(int));
	}

	// Records instructions and data into VC3600 memory.
	// I changed the "i" to capital to keep with the style
	bool InsertMemory(int a_location, int a_contents);

	// Runs the VC3600 program recorded in memory.
	// I changed the "r" to capital to keep with the style
	bool RunProgram();

private:
	// The memory of the VC3600.
	int m_memory[MEMSZ];
	// The accumulator for the VC3600
	int m_acceumulator;
};

#endif

