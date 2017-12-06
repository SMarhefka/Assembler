// Svetlana Marhefka
// Implementation of the symbol table class.

#include "stdafx.h"
#include "SymTab.h"

/**/
/*
NAME:
AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS:
void AddSymbol( char *a_symbol, int a_loc );
a_symbol --> the symbol
a_loc --> the location of the symbol

DESCRIPTION:
This function will place the symbol "a_symbol"
and its location "a_loc" in the symbol table.

RETURNS
Returns nothing.
*/
/**/
void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
	// If the symbol is already in the symbol table
	// record it as multiply defined.
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);

	if (st != m_symbolTable.end())
	{
		st -> second = multiplyDefinedSymbol;
		return;
	}

	// Record a the  location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
}

/**/
/*
NAME:
DisplaySymbolTable - displays the sybmol table.

SYNOPSIS:
void AddSymbol( char *a_symbol, int a_loc );
a_symbol --> the symbol
a_loc --> the location of the symbol

DESCRIPTION:
This function will iterate through the map and output each 
symbol along with it's location in the symbol table

RETURNS
Returns nothing.
*/
/**/
void SymbolTable::DisplaySymbolTable()
{
	

	// If the symbol is already in the symbol table
	map<string, int>::iterator st;
	// Initialize our count variable
	int count = 0;

	// Go throught the symbol table and display the contents
	for(auto st = m_symbolTable.begin(); st != m_symbolTable.end(); st++)
	{      
		cout << left << setw(10) << count
			<< right << setw(10) << st -> first
			<< right << setw(10) << st -> second << endl;
		count++;
	}

}

/**/
/*
NAME:
LookupSymbol - lookup symbol in the sybmol table.

SYNOPSIS:
void AddSymbol( char *a_symbol, int a_loc );
a_symbol --> the symbol
a_loc --> the location of the symbol

DESCRIPTION:
This function look for a specific symbol in the sybol table

RETURNS
Returns nothing.
*/
/**/
bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)
{
	// Look through each symbol in the symbol table
	map<string, int>::iterator st;

	st = m_symbolTable.find(a_symbol);
	if(st != m_symbolTable.end())
	{
		// Record a the  location in the symbol table.
		// Statement taken from the first function and
		// rearranged
		a_symbol = st->first;
		a_loc = st->second;
		return true;
	}
	else
	{
		//a_loc = multiplyDefinedSymbol;
		return false;
	}
}