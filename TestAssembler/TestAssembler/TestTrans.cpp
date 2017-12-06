#include "stdafx.h"
#include "Errors.h"
#include "TestTrans.h"

/**/
/*
TestTrans::TranslateInstruction() TestTrans::TranslateInstruction()

NAME
TestTrans::TranslateInstruction - Translate machine or
assembly language.

SYNOPSIS
FileAccess::FileAccess(int argc, char *argv[])
a_intype --> the instruction type
a_inst --> the instruction itself
a_symbol --> the system table
a_instloc --> the location of the instruction

DESCRIPTION
The purpose of this function is to translate either
assembly instructions or machine language and output
the result to the console.

This was only supposed to be temporary but due to time
constraints on the project has now become more permanant.

RETURNS
Returns nothing.
*/
/**/
void TestTrans::TranslateInstruction(Instruction::InstructionType a_intype, Instruction a_inst, SymbolTable a_symbol, int a_instloc)
{
	string a_ErrorMsgs;

	if(a_intype == Instruction::ST_AssemblerInstr)
	{
		// If the operation code is either DS or ORG
		if(a_inst.GetOpCode() == "DS" || a_inst.GetOpCode() == "ORG")
		{
			// Then output the location of the instruction instruction
			// and the original instruction
			cout << setw(20) << left << a_instloc << a_inst.GetOrigInstruction() << endl;
		}
		if(a_inst.GetOpCode() == "DC")
		{
			
			// If the operand value is less than 99999 then we
			// have enough memory
			if(a_inst.GetOperandValue() < 99999)
			{
				// This will be used to read in the operand value
				// so that we can chage the value from an int to
				// a string
				ostringstream a_intopvalue;

				a_intopvalue << a_inst.GetOperandValue();
				// Change the operand value from an int to a string
				m_AddressString = a_intopvalue.str();
				for(int count = m_AddressString.size(); count < 6; count++)
				{
					m_AddressString.insert(0, "0");
				}
				// Then output the location of the instruction 
				// instruction and the original instruction
				cout << setw(10) << left << a_instloc << 
					setw(10) << left << m_AddressString 
					<< a_inst.GetOrigInstruction() << endl;
			}
			// If our address is too big then that means that 
			// our value is greater than 99999 because
			// we can only store 5 memory locations
			else
			{
				// This will be used to read in the operand value
				// so that we can chage the value from an int to
				// a string
				ostringstream a_intopvalue;

				a_ErrorMsgs = "Error: Address is too big for memory\n";
				Errors::RecordError(a_ErrorMsgs);
				// Proceed to fixing the memory by reading in the
				// first 6 values of the operand
				a_intopvalue << a_inst.GetOperandValue();
				// Change the operand value from an int to a string
				m_AddressString = a_intopvalue.str();
				// Get the first 5 characters of the string
				m_AddressString = m_AddressString.substr(0, 6);
				// Then output the location of the instruction instruction
				// and the original instruction
				cout << setw(10) << left << a_instloc <<
					setw(10) << left << m_AddressString
					<< a_inst.GetOrigInstruction() << endl;
			}
		}
	}
	else if(a_intype == Instruction::ST_MachineLanguage)
	{
		// This will be used to read in the operand value
		// so that we can chage the value from an int to
		// a string
		ostringstream a_intopvalue;
		// read in the operand value
		a_intopvalue << a_inst.GetOperandValue();
		// Change the operand value from an int to a string
		m_AddressString = a_intopvalue.str();
		
		// Initialize a variable that will point to a specific
		// location from our symbol table
		int a_pointloc;
		
		// If our code is not 'HALT', so all of our opCode 
		// besides halt
		if(a_inst.GetOpCode() != "HALT")
		{
			a_symbol.LookupSymbol(a_inst.GetOperand(), a_pointloc);
			// We need to check for symbols that are defined multiple
			// times. We do this by seeing if the pointer location is
			// = to -999
			if(a_pointloc == -999)
			{
				a_ErrorMsgs = "Error: The symbol has been defined multiple times\n";
				Errors::RecordError(a_ErrorMsgs);
			}
			// If we can find the location
			if(a_symbol.LookupSymbol(a_inst.GetOperand(), a_pointloc) == true)
			{
				// If the operation code is only 1 character
				if(m_AddressString.size() == 1)
				{
					// Then we are going to add a 0 to the front
					m_AddressString.insert(0, "0");
				}
				// If the operation code is 5 character
				else if(m_AddressString.size() == 5)
				{
					// Then we are going to add a 0 to the end
					m_AddressString.insert(2, "0");
				}
				// Then output the location of the instruction instruction
				// and the original instruction
				cout << setw(10) << left << a_instloc <<
					setw(10) << left << m_AddressString << setw(10) 
					<< left << a_inst.GetOrigInstruction() << endl;
			}
			// This assumes that we are unable to find the location
			else
			{
				// If the operation code is only 1 character
				if(m_AddressString.size() == 1)
				{
					// Then we are going to add a 0 to the front
					m_AddressString.insert(0, "0");
				}
				m_AddressString = m_AddressString + "????";
				// Then output the location of the instruction instruction
				// and the original instruction
				cout << setw(10) << left << a_instloc <<
					setw(10) << left << m_AddressString << setw(10)
					<< left << a_inst.GetOrigInstruction() << endl;
			}
		}
		// Then our operation code is HALT
		else
		{
			for(int count = m_AddressString.size(); count < 6; count++)
			{
				m_AddressString.insert(2, "0");
			}
			// Then output the location of the instruction 
			// instruction and the original instruction
			cout << setw(10) << left << a_instloc <<
				setw(10) << left << m_AddressString
				<< a_inst.GetOrigInstruction() << endl;
		}
	}
}
