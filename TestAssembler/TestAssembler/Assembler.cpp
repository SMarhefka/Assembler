// Svetlana Marhefka
// Implementation of the Assembler class.

#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"


/**/
/*
Assembler::Assembler() Assembler::Assembler()

NAME
Assembler::Assembler - Constructor for the assembler.

SYNOPSIS
Assembler::Assembler(int argc, char *argv[]);

argc --> the number of strings that make up the command line arguement
argv --> the array that contains the strings of argc

DESCRIPTION
This function will pass argc and argv which are command line arguements, to the file access
constructor.

RETURNS
Returns no values.

*/
/**/
Assembler::Assembler(int argc, char *argv[]): m_facc(argc, argv)
{
	// Nothing else to do here at this point.
}

// Destructor currently does nothing.  
// You might need to add something as you develope this project.
Assembler::~Assembler()
{
	// Nothing else to do here at this point.
}

/**/
/*
Assembler::PassI() Assembler::PassI()

NAME
Assembler::PassI - Establishes the location of the labels.

SYNOPSIS
void PassI()

DESCRIPTION
The purpose of this function is to establish the location
of all of the symbols and add them to our symbol table. 
This is done by reading in a line from the file and putting
it into a buffer.  We then parse the line using the parse 
instruction function.  We do this for every line and every 
label that we find is added to our symbol table.  We then 
find the next location using the LocationNextInsturction 
function.

RETURNS
Returns nothing.
*/
/**/
void Assembler::PassI()
{
	// Tracks the location of the instructions to be generated.
	int loc = 0;

	// Successively process each line of source code.
	for(;;)
	{
		// Read the next line from the source file.
		string buff;
		if(!m_facc.GetNextLine(buff))
		{
			// If there are no more lines, we are missing 
			// an end statement.
			// We will let this error be reported by Pass II.
			return;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If this is an end statement, there is nothing 
		// left to do in pass I.
		// Pass II will determine if the end is the last statement.
		if(st == Instruction::ST_End)
		{
			return;
		}

		// Labels can only be on machine language 
		// and assembler language instructions.  
		// So, skip other instruction types.
		if(st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			continue;
		}

		// If the instruction has a label, record it and 
		// its location in the symbol table.
		if(m_inst.isLabel())
		{

			m_symtab.AddSymbol(m_inst.GetLabel(), loc);
		}

		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);
	}
}

/**/
/*
Assembler::PassII() Assembler::PassII()

NAME
Assembler::PassII - Translate Instruction.

SYNOPSIS
void PassII()

DESCRIPTION
The first thing that we do is go to the beggining of the
file using the Rewind function.  Then we make sure to clear
any errors that we may have had from pass I.

We then begin the hard work by parsing our lines.  Any line
with machine or assembly language is then translated using
the TranslateInstruction function.  Then we continue on to
see if the translated line needs to be put into memory.

This function also does the important job of error
checking.  It checks to make sure that we have the correct
types of operation codes, labels, and it checks to make
sure that we have enough memory.

RETURNS
Returns nothing.
*/
/**/
void Assembler::PassII()
{
	// Want to create an empty string for errorMessages
	string a_ErrorMsgs;

	// Tracks the location of the instructions to be generated.
	int loc = 0;

	// Use the rewind function on the file access object to get
	// to the beginning of the file
	m_facc.Rewind();

	// Clear any messages stored in m_ErrorMsgs vector
	Errors::InitErrorReporting();

	// Display everything we need for the translation of the program
	cout << "Translation of Program: " << endl;
	cout << left << setw(10) << "Location" 
        << left << setw(10) << "Contents"
		<< left << setw(10) << "Original Statement" << endl;

	// Successively process each line of source code.
	for(;;)
	{
		// Read the next line from the source file.
		string buff;
		// Check for an 'END' Statement
		if(!m_facc.GetNextLine(buff))
		{
			// If we don't see the 'END' statement
			if(m_inst.GetOpCode() != "END")
			{
				// Display an error message
				a_ErrorMsgs = "Error: The 'END' statement is missing\n";
				Errors::RecordError(a_ErrorMsgs);
				return;
			}
			else
			{
				return;
			}
		}

		/******************** At this point we are translating instructions ********************/
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If the instruction type is a comment
		if(st == Instruction::ST_Comment)
		{
			cout << "                    " << m_inst.GetOrigInstruction() << endl;
		}
		// If the instruction type is an 'END' statement
		if(st == Instruction::ST_End)
		{
			// Check to see if the 'END' statement is
			// at the end of the file
			if(!m_facc.GetNextLine(buff))
			{
				cout << "                    " << m_inst.GetOrigInstruction() << endl;
				return;
			}
			// Else it is before the end of the file
			// which means that there is an error
			{
				a_ErrorMsgs = "Error: The 'END' statement is before the end of the file\n";
				Errors::RecordError(a_ErrorMsgs);
				return;
			}
		}
		if(st != Instruction::ST_AssemblerInstr && st != Instruction::ST_MachineLanguage)
		{
			continue;
		}
		// Translate our instruction
		// Use the instruction type, the instruction
		// the symbol table, and the location as our
		// inputs
		m_testrans.TranslateInstruction(st, m_inst, m_symtab, loc);

		//This will store integer value of the contents
		int a_contvalue;

		if(m_inst.GetOpCode() == "DC" || st == Instruction::ST_MachineLanguage)
		{
			a_contvalue = stoi(m_testrans.GetString());
			// Insert the content into memory at a sepcific location
			m_emul.InsertMemory(loc, a_contvalue);
		}
		// Get the location of the next instruction
		loc = m_inst.LocationNextInstruction(loc);
		
		// Check to make sure that we have enough memory
		if(loc > 9999)
		{
			a_ErrorMsgs = "Error: Not enough memory for translation\n";
			Errors::RecordError(a_ErrorMsgs);
			return;
		}
	}
}