// Svetlana Marhefka
// Implementation of the Error class.

#include "stdafx.h"
#include "Errors.h"

// Initialize the m_ErrrorMsgs vector
vector<string> Errors::m_ErrorMsgs;

/**/
/*
Errors::InitErrorReporting() Emulator::InitErrorReporting()

NAME
Errors::InitErrorReporting - Initialize error reporting.

SYNOPSIS
void Errors::InitErrorReporting()

DESCRIPTION
The purpose of this function is to initialize our error
reporting.  We initialize this function by simply clearing
all of our errror messages

RETURNS
Returns nothing.
*/
/**/
void Errors::InitErrorReporting()
{
	// Want to clear all errror messages so that
	// we start with a clean slate
	Errors::m_ErrorMsgs.clear();
}

/**/
/*
Errors::RecordError() Emulator::RecordError()

NAME
Errors::RecordError - records any errors.

SYNOPSIS
void Errors::RecordError(string &a_emsg)
a_emsg --> The message that will be recorded into m_ErrorMsgs

DESCRIPTION
The purpose of this function is to record any error 
messages.  This is accomplished by pushing a_emsg to
our m_ErrorMsgs vector

RETURNS
Returns nothing.
*/
/**/
void Errors::RecordError(string &a_emsg)
{
	// The purpose of this function is to push
	// any errors into the m_ErrorMsgs vector
	Errors::m_ErrorMsgs.push_back(a_emsg);
}

/**/
/*
Errors::DisplayErrors() Emulator::DisplayErrors()

NAME
Errors::DisplayErrors - displays any errors.

SYNOPSIS
void Errors::DisplayErrors()

DESCRIPTION
The purpose of this function is to display any error
messages.  This is accomplished by outputting the error
messages stored in our m_ErrorMsgs vector.

RETURNS
Returns nothing.
*/
/**/
void Errors::DisplayErrors()
{
	// The purpose of this function is to display
	// any errors held in the m_ErrorMsgs vector
	for(int MsgNum = 0; MsgNum < m_ErrorMsgs.size(); MsgNum++)
	{
		// This displays the error message
		cout << m_ErrorMsgs[MsgNum];
	}
}

/**/
/*
Errors::IsVectorEmpty() Emulator::IsVectorEmpty()

NAME
Errors::IsVectorEmpty - Checks m_ErrorMsgs vector.

SYNOPSIS
bool Errors::IsVectorEmpty()

DESCRIPTION
The purpose of this function is to check and see if we
have any error messages in our vector. This is accomplished
by checking the size of our m_ErrorMsgs vector.

RETURNS
Returns nothing.
*/
/**/
bool Errors::IsVectorEmpty()
{
	// The purpose of this function is to determine
	// weather or not the vector is empty
	if(m_ErrorMsgs.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}