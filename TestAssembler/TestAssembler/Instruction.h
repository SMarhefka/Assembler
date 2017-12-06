// Svetlana Marhefka
// Class to parse and provide information about instructions.  
// Note: you will be adding more functionality.
#pragma once

// The elements of an instruction.
class Instruction
{

public:
	// The consturctor
	Instruction(){};

	// The destructor
	~Instruction(){};

	// Codes to indicate the type of instruction we are processing.  
	// Why is this inside the class?
	enum InstructionType
	{
		// A machine language instruction.
		ST_MachineLanguage,
		// Assembler Language instruction.
		ST_AssemblerInstr,
		// Comment
		ST_Comment,
		// end instruction.
		ST_End
	};

	// I decided to use an enum for the operation codes because of
	// several reasons. The first one was because cplusplus.com
	// defined an enum as a bunch of constant values that are sequenced
	// The second reason was due to readability purposes and the third
	// was because there is a smaller chance of making mistakes when
	// using enums because of the organization they provide.
	enum OperationCodes
	{
		ADD = 1,
		SUB = 2,
		MULT = 3,
		DIV = 4,
		LOAD = 5,
		STORE = 6,
		READ = 7,
		WRITE = 8,
		B = 9,
		BM = 10,
		BZ = 11,
		BP = 12,
		HALT = 13
	};

	// Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// Check to make sure that the operation code is
	// valid
	void ValidOpCode(int a_WordNumber, string a_OpCode);

	void ValidOperand(int a_WordNumber, string a_Operand);

	// Initializes the private members of this class
	void InitPrivateVals();

	// Initialize the operation codes
	// This is crutial if I want to use the enum above
	void SetOpCode();

	// Check to make sure that the label is valid
	bool ValidLabel(string a_TestLabel);

	// To access the label
	inline string &GetLabel()
	{
		return m_Label;
	};

	// To access the the operation codes
	inline string &GetOpCode()
	{
		return m_OpCode;
	};

	inline string &GetOperand()
	{
		return m_Operand;
	};

	inline string &GetOrigInstruction()
	{
		return m_Instruction;
	};

	inline int GetNumOpCode()
	{
		return m_NumOpCode;
	};

	inline int GetOperandValue()
	{
		return m_OperandValue;
	};

	// To determine if a label is blank.
	inline bool isLabel()
	{
		return !m_Label.empty();
	};

	// The private elemements of a instruction:
private:

	// The label
	string m_Label;
	// The symbolic op code.
	string m_OpCode;
	// The operand.
	string m_Operand;
	// The original instruction.
	string m_Instruction;
	// The error message;
	string m_ErrorMsgs;

	/******Derived values*******/
	// The type of instruction.
	InstructionType m_Type;
	// The numerical value of the op code.
	int m_NumOpCode;
	// The value of the operand if it is numeric.
	int m_OperandValue;
	// == true if the operand is numeric.
	bool m_IsNumericOperand;

};


