#include "Emulator.h"
#include "Instruction.h"
#include "SymTab.h"

#pragma once

class TestTrans
{

public:
	string GetString()
	{
		return m_AddressString;
	}

	void TranslateInstruction(Instruction::InstructionType a_intype, Instruction a_inst, SymbolTable a_symbol, int a_instloc);

private:
	string m_AddressString;

};