/*
* Svetlana Marhefka
*
* Assembler class. This class is a container for the entire
* assembler. It contains the objects necessary to build the 
* assembler and the functions for the major elements.
*/

#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"
#include "Errors.h"
#include "TestTrans.h"

class Assembler
{
public:
	Assembler(int argc, char *argv[]);

	~Assembler( );

	// Pass I - establish the locations of the symbols
	void PassI( );

	// Pass II - generate a translation
	void PassII( );

	// Display the symbols in the symbol table.
	void DisplaySymbolTable( )
	{
		cout << "Symbol Table:\n";
		cout << left << setw(10) << "Symbol #"
			<< right << setw(10) << "Symbol"
			<< right << setw(10) << "Location" << endl;

		m_symtab.DisplaySymbolTable();

		cout << "========================================\n";
	}

	// Run emulator on the translation.
	void RunEmulator()
	{
		//if the program cannot be run
		if (!(m_emul.RunProgram( )))
		{
			//output the following message
			cout << "\n";
			cout << "The following errors occurred\n";
			//display any errors if they occured
			Errors::DisplayErrors( );
			//message to continue the program
			cout << "\n";
			cout << "Please press enter to continue: \n";
			//wait for user input
			cin.get( );
		}
		//if there are no issues then run the program
		else
		{
			m_emul.RunProgram( );
			cout << "Emulator ran successfully\n";
		}
	}  

private:
	// File Access object
	FileAccess m_facc;
	// Symbol table object
	SymbolTable m_symtab;
	// Instruction object
	Instruction m_inst;
	// Emulator object
	Emulator m_emul;
	// Translate object
	// This is temporary
	TestTrans m_testrans;
};

