// Svetlana Marhefka
// Implementation of the Assembler class.


// This must be present if you use precompiled headers 
// which you will use.
#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"
#include "SymTab.h"

/**/
/*
Instruction::ParseInstruction() Instruction::ParseInstruction()

NAME

Instruction::ParseInstruction - Parses the instruction.

SYNOPSIS

Instruction::InstructionType Instruction::ParseInstruction(string&a_buff);

a_buff --> the buffer for the line currently being worked on.

DESCRIPTION
The purose of this function is to parse the instruction
that are read into a_buff.

To accomplish this we must first check to see if there is a
comment in a_buff.  A commment is denoted with as ";". 
If a_buff is only a comment then the instruction type is 
set to a comment it is returned.  However, if the buffer 
contains a comment at any point, then it is removed. 

Next we read in each word into a vector.  With every word
that we read in, we increment the count by one.  Then 
depending on how many words have been read in we do what is
necessary.

This function also checks to make sure that our labels, 
operands, and operation codes are valid.

RETURNS
This function returns m_type which could be COMMENT, END, 
MachineLanguage, or AssemblyInstr
*/
/**/
Instruction::InstructionType 
Instruction::ParseInstruction(string &a_buff)
{
	// We begin by clearing/intializing our private member variables
	// that way we can start fresh
	InitPrivateVals();
	
	// If we read in a blank line
	if (a_buff == "")
	{
		// Set the instruction type to a comment
		m_Type = ST_Comment;
		// Return the instruction type
		return m_Type;
	}

	// Checks buffer to see if is only made up of spaces
	if(a_buff.find_first_not_of(" ") == string::npos)
	{
		// Set the instruction type to a comment
		m_Type = ST_Comment;
		// Return the instruction type
		return m_Type;

	}
	// Check our line for any comments
	else
	{
		// Initialize a variable named a_ComBuff which will be
		// equal to any comments that we find
		string a_ComBuff;
		// this will hold the position of the comment
		size_t a_ComPos;

		// Set the original instruction to what we are reading in
		m_Instruction = a_buff;
		// Record the position of the comment
		a_ComPos = a_buff.find(";");
		
		// If we do find a comment then life is good
		if(a_ComPos != string::npos)
		{
			//set comment to the buffer
			a_ComBuff = a_buff.substr(a_ComPos);
			//earse the comment 
			a_buff = a_buff.erase(a_ComPos, a_ComBuff.length());
		}

		// If there is nothing else then our line only held a comment
		if (a_buff == "")
		{
			// Then set the instruction type to a comment
			m_Type = ST_Comment;
			// Return the instruction type
			return m_Type;  
		}
	}


	// Need a string variable to hold the word that we are
	// reading in
	string a_ReadWord;
	// We want to create a vector to store our words
	vector<string> a_WordsVector;
	// Need to keep track of the number of words that
	// we have read in. Start by initializing it to 0
	int a_WordNumber = 0;
	// This is help us read in the instructions
	stringstream a_IncomingInstr(a_buff);

	// Here we read in every word
	while(a_IncomingInstr >> a_ReadWord)
	{
		// Want to get the word to all uppercase
		transform(a_ReadWord.begin(), a_ReadWord.end(),
				  a_ReadWord.begin(), ::toupper);
		
		//placed here for testing purposes
		//cout << a_ReadWord << endl;

		// Then we push the transformed word into our vector
		a_WordsVector.push_back(a_ReadWord);
		// Finally we increment the count by 1
		a_WordNumber++;
	}

	// Check to make sure that the number of words is
	// greater than 3. If it is then we have an error
	if(a_WordNumber > 3)
	{
		m_ErrorMsgs = "Error: Read in too many operands\n";
		Errors::RecordError(m_ErrorMsgs);
	}
	else
	{
		// Initialize three string values
		// These will be used to test the validity of
		// the label, operation code, or operand depending
		// on the situation
		string a_TestLabel;

		switch(a_WordNumber)
		{
			// Case if we read in 3 words
			case 3:
			// The first word should be the label
			a_TestLabel = a_WordsVector[0];
			// Check to see if the label is valid
			if(ValidLabel(a_TestLabel) == true)
			{
				// Set our testerlabel to m_Label
				m_Label = a_TestLabel;
			}
			else
			{
				m_Label = "????";
			}
			// The second word should be the operation code
			m_OpCode = a_WordsVector[1];
			// Set it up
			SetOpCode();
			// Check to see if that is valid
			ValidOpCode(a_WordNumber, m_OpCode);

			m_Operand = a_WordsVector[2];
			ValidOperand(a_WordNumber, m_Operand);
			return m_Type;
			break;

			// Case if we read in 2 words
			case 2:
			// The first word should be the operation code
			m_OpCode = a_WordsVector[0];
			// Set it up
			SetOpCode();
			// Check to see if that is valid
			ValidOpCode(a_WordNumber, m_OpCode);

			m_Operand = a_WordsVector[1];
			ValidOperand(a_WordNumber, m_Operand);
			return m_Type;
			break;

			// Case if we read in 1 word
			case 1:
			m_OpCode = a_WordsVector[0];
			SetOpCode();
			ValidOpCode(a_WordNumber, m_OpCode);
			return m_Type;
			break;
		}
	}
};

/**/
/*
Instruction::LocationNextInstruction()Instruction::LocationNextInstruction()

NAME
Instruction::LocationNextInstruction - Get the location of 
the next instruction

SYNOPSIS

int Instruction::LocationNextInstruction(int a_loc)

a_loc --> the location of the current instruction

DESCRIPTION
The purose of this function is to take a_loc and use the 
values that we determined earlier to figure out the next 
location of the instruction.

RETURNS
Returns the location of the next instruction
*/
/**/
int Instruction::LocationNextInstruction(int a_loc)
{
	// If the operand is not a numeric value or
	// If the operand is a numeric value and its opcode 
	// is = "DC"
	if (m_IsNumericOperand != true)
	{
		a_loc = a_loc + 1;
	}
	// If the operand is a numeric value
	else
	{
		if (m_OpCode == "ORG")
		{
			a_loc = m_OperandValue;
		}
		else if (m_OpCode == "DS")
		{
			a_loc = a_loc + m_OperandValue;
		}
		else
		{
			a_loc = a_loc + 1;
		}
	}
	return a_loc;
}

/**/
/*
Instruction::ValidOpCode() Instruction::ValidOpCode()

NAME
Instruction::ValidOpCode - Get the location of
the next instruction

SYNOPSIS
bool Instruction::ValidOpCode(int a_WordNumber, string a_TestOpCode)

a_WordNumber --> the number of words in our vector
a_TestOpCode --> the operation code that we are testing
to see if it is valid

DESCRIPTION
The purose of this function is to determine wheather or not
our operation codes are valid

RETURNS
Returns true if our operation code is valid and false if it
is not
*/
/**/
void Instruction::ValidOpCode(int a_WordNumber, string m_OpCode)
{
	switch(a_WordNumber)
	{
		// If we read in 1 word
		case 1:
		// If our operation code is 'HALT' then
		// we can set the m_Type to MachineLanguage
		// and return true
		if(m_OpCode == "HALT")
		{
			m_Type = ST_MachineLanguage;
		}
		// If our operation code is 'END' then
		// we can set the m_Type to ST_END
		// and return true
		else if(m_OpCode == "END")
		{
			m_Type = ST_End;
		}
		// Otherwise it is an invalid operation code
		else
		{
			m_OpCode = "??";
			m_Type = ST_MachineLanguage;
			m_ErrorMsgs = "Error: Invalid Operation Code\n";
			Errors::RecordError(m_ErrorMsgs);
		}
		break;
		// If we read in two words
		case 2:
		if(m_NumOpCode != 0)
		{
			m_Type = ST_MachineLanguage;
		}
		else if(m_NumOpCode == 0)
		{
			if(m_OpCode == "ORG")
			{
				m_Type = ST_AssemblerInstr;
			}
			else if(m_OpCode != "ORG")
			{
				m_OpCode = "??";
				m_Type = ST_MachineLanguage;
				m_ErrorMsgs = "Error: Invalid Operation Code\n";
				Errors::RecordError(m_ErrorMsgs);
			}
			
		}
		break;
		// If we read in three words
		case 3:
		if(m_NumOpCode != 0)
		{
			m_Type = ST_MachineLanguage;
		}
		else if(m_NumOpCode == 0)
		{
			if(m_OpCode == "DS" || m_OpCode == "DC")
			{
				m_Type = ST_AssemblerInstr;
			}
			else
			{
				m_ErrorMsgs = "Error: Invalid Operation Code\n";
				Errors::RecordError(m_ErrorMsgs);
				m_OpCode = "??";
				m_Type = ST_MachineLanguage;
			}
		}
		break;
	}
}

/**/
/*
Instruction::ValidOperand() Instruction::ValidOperand()

NAME
Instruction::ValidOperand - Get the location of
the next instruction

SYNOPSIS
bool Instruction::ValidOperand(int a_WordNumber, string a_TestOpCode)

a_WordNumber --> the number of words in our vector
a_TestOpCode --> the operation code that we are testing
to see if it is valid

DESCRIPTION
The purose of this function is to determine wheather or not
our operand is valid.  Note: I switched this from a boolean
to a void function

RETURNS
Returns nothing
*/
/**/
void Instruction::ValidOperand(int a_WordNumber, string m_Operand)
{
	switch(a_WordNumber)
	{
		// If we read in two words
		case 2:
		if(m_NumOpCode == 0 && m_OpCode == "ORG")
		{
			// If the first character of the operand is not
			// a letter (so its a number)
			if(isalpha(m_Operand[0]) == 0)
			{
				// Set the m_IsNumericOperand to true
				m_IsNumericOperand = true;
				m_OperandValue = stoi(m_Operand);
			}
			else
			{
				m_IsNumericOperand = false;
				m_ErrorMsgs = "Error: ORG must have a numeric value\n";
				Errors::RecordError(m_ErrorMsgs);
			}
			return;
		}
		break;

		case 3:
		if(m_OpCode == "DS" || m_OpCode == "DC")
		{
			if(isalpha(m_Operand[0]) == 0)
			{
				m_IsNumericOperand = true;
				m_OperandValue = stoi(m_Operand);
			}
			else
			{
				m_IsNumericOperand = false;
				m_ErrorMsgs = "Error: DS or DC must have a numeric value\n";
				Errors::RecordError(m_ErrorMsgs);
				m_Type = ST_AssemblerInstr;
			}
			return;
		}
		break;
	}
	// If the operand length is greater than 10 characters
	// then it is considered invalid
	if(m_Operand.size() > 10)
	{
		m_ErrorMsgs = "Error: Operand name is greater than 10 characters\n";
		Errors::RecordError(m_ErrorMsgs);
	}
	if(isalpha(m_Operand[0]) == 0)
	{
		if(m_NumOpCode != 0)
		{
			m_ErrorMsgs = "Error: Symbolic Operatoin Code can't have a number\n";
			Errors::RecordError(m_ErrorMsgs);
		}
		else
		{
			m_ErrorMsgs = "Error: Label has to start with a  letter\n";
			Errors::RecordError(m_ErrorMsgs);
		}
	}
}

/**/
/*
Instruction::ValidLabel() Instruction::ValidLabel()

NAME
Instruction::ValidLabel - Get the location of
the next instruction

SYNOPSIS
bool Instruction::ValidLabel(string a_TestLabel)

a_TestLabel --> the string that we are testing to see if
it is valid

DESCRIPTION
The purose of this function is to determine wheather or not
our label is valid

RETURNS
Returns true if our label is valid and false if it
is not
*/
/**/
bool Instruction::ValidLabel(string a_TestLabel)
{
	// If our label is greater than 10 characters
	// then it is considered invalid
	if(a_TestLabel.size() > 10)
	{
		m_ErrorMsgs = "Error: Label has too many characters\n";
		Errors::RecordError(m_ErrorMsgs);
		return false;
	}
	// Or if the first character of test label is not a 
	// letter than it is also considered invalid
	else if(isalpha(a_TestLabel[0]) == false)
	{
		m_ErrorMsgs = "Error: Label cannot begin with a number\n";
		Errors::RecordError(m_ErrorMsgs);
		return false;
	}
	// Otherwise we are okay
	else
	{
		return true;
	}
}

/**/
/*
Instruction::InitPrivateVals() Instruction::InitPrivateVals()

NAME
Instruction::InitPrivateVals - Initilize the private values

SYNOPSIS
bool Instruction::ValidLabel(string a_TestLabel)

DESCRIPTION
The purose of this function is to initialize all of the
private values from the instruction class

RETURNS
Returns nothing.
*/
/**/
void Instruction::InitPrivateVals()
{
	// Initialize the label value
	string m_Label = "";
	// Initialize the symbolic op code.
	string m_OpCode = "";
	// Initialize the operand.
	string m_Operand = "";
	// Initialize the original instruction.
	string m_instruction = "";

	/******Derived values*******/
	// Initialize the numerical value of the op code.
	int m_NumOpCode = 0;
	// Initialize the value of the operand if it is numeric.
	int m_OperandValue = 0;
	// Initialize m_IsNumericOperand to false remember
	// m_IsNumericOperand == true if the operand is numeric.
	bool m_IsNumericOperand = false;
}

/**/
/*
Instruction::SetOpCode() Instruction::SetOpCode()

NAME
Instruction::SetOpCode - Sets up operation code

SYNOPSIS
void Instruction::SetOpCode()

DESCRIPTION
The purose of this function is to set up our operation 
codes.

RETURNS
Returns nothing.
*/
/**/
void Instruction::SetOpCode()
{
	// Going down in order we are going to set
	// the string version of our opCode (m_OpCode)
	// to the numerical value which will come from
	// the enum that I created in the instruction header
	if(m_OpCode == "ADD")
	{
		//setting the numeric operation code to ADD (1)
		m_NumOpCode = ADD;
	}
	else if(m_OpCode == "SUB")
	{
		//setting the numeric operation code to SUB (2)
		m_NumOpCode = SUB;
	}
	else if(m_OpCode == "MULT")
	{
		//setting the numeric operation code to MULT (3)
		m_NumOpCode = MULT;
	}
	else if(m_OpCode == "DIV")
	{
		//setting the numeric operation code to DIV (4)
		m_NumOpCode = DIV;
	}
	else if(m_OpCode == "LOAD")
	{
		//setting the numeric operation code to LOAD (5)
		m_NumOpCode = LOAD;
	}
	else if(m_OpCode == "STORE")
	{
		//setting the numeric operation code to STORE (6)
		m_NumOpCode = STORE;
	}
	else if(m_OpCode == "READ")
	{
		//setting the numeric operation code to READ (7)
		m_NumOpCode = READ;
	}
	else if(m_OpCode == "WRITE")
	{
		//setting the numeric operation code to WRITE (8)
		m_NumOpCode = WRITE;
	}
	else if(m_OpCode == "B")
	{
		//setting the numeric operation code to B (9)
		m_NumOpCode = B;
	}
	else if(m_OpCode == "BM")
	{
		//setting the numeric operation code to BM (10)
		m_NumOpCode = BM;
	}
	else if(m_OpCode == "BZ")
	{
		//setting the numeric operation code to BZ (11)
		m_NumOpCode = BZ;
	}
	else if(m_OpCode == "BP")
	{
		//setting the numeric operation code to BP (12)
		m_NumOpCode = BP;
	}
	else if(m_OpCode == "HALT")
	{
		//setting the numeric operation code to HALT (13)
		m_NumOpCode = HALT;
	}
	else
	{
		m_NumOpCode = 0;
	}
}