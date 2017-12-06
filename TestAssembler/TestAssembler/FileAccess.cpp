// Svetlana Marhefka
// Implementation of file access class.

#include "stdafx.h"
#include "FileAccess.h"

#pragma once 

/**/
/*
FileAccess::FileAccess() FileAccess::FileAccess()

NAME
FileAccess::FileAccess - Opens the file.

SYNOPSIS
FileAccess::FileAccess(int argc, char *argv[])
argc --> the number of strings that make up the command line arguement.
argv --> the arguement values that contains the strings of argc.

DESCRIPTION
This is the constructor.  It is responsible for reading 
in command line arguements and running the requested
programs.  The second arguement should be file name.

RETURNS
Returns nothing.
*/
/**/
FileAccess::FileAccess(int argc, char *argv[])
{
	// Check that there is exactly one run time parameter.
	if (argc != 2)
	{
		cerr << "Usage: Assem <FileName>" << endl;
		exit(1);
	}
	// Open the file.
	// One might question if this is the best place to open the file.
	// One might also question whether we need a file access class.
	m_sfile.open(argv[1], ios::in);

	// If the open failed, report the error and terminate.
	if (!m_sfile)
	{
		cerr << "Source file could not be opened, assembler terminated." << endl;
		exit(1);
	}
}

/**/
/*
FileAccess::~FileAccess() FileAccess::~FileAccess()

NAME
FileAccess::~FileAccess - Closes the file.

SYNOPSIS
FileAccess::~FileAccess()

DESCRIPTION
This is the destructor.  It is responsible for closing the
file

RETURNS
Returns nothing.
*/
/**/
FileAccess::~FileAccess()
{
	m_sfile.close();
}

/**/
/*
FileAccess::GetNextLine() FileAccess::GetNextLine()

NAME
FileAccess::GetNextLine - Get the next line.

SYNOPSIS
bool FileAccess::GetNextLine(string &a_buff)
a_buff --> the line from the file that will be placed into
this variable

DESCRIPTION
The purpose of this function is to get the next line from
the file and put it into a_buff.

RETURNS
Returns true if there are no error and it could get the
next line.  Returns false if there are any issues.
*/
/**/
bool FileAccess::GetNextLine(string &a_buff)
{
	// If there is no more data, return false.
	if (m_sfile.eof())
	{

		return false;
	}
	getline(m_sfile, a_buff);

	// Return indicating success.
	return true;
}

/**/
/*
FileAccess::Rewind() FileAccess::Rewind()

NAME
FileAccess::Rewind - Get to the beginning of the file.

SYNOPSIS
void FileAccess::Rewind()

DESCRIPTION
The purpose of this function is to get to the beginning of 
the file.  This is accomplished by simply seeking to the 
0 position of the file.

RETURNS
Returns nothing.
*/
/**/
void FileAccess::Rewind()
{
	// Clean tall file flags and go back to the beginning of the file.
	m_sfile.clear();
	m_sfile.seekg(0, ios::beg);
}

/**/
/*
FileAccess::AtEndOfFile() FileAccess::AtEndOfFile()

NAME
FileAccess::AtEndOfFile - Check to see if we are at the 
end of our file.

SYNOPSIS
bool FileAccess::AtEndOfFile()

DESCRIPTION
The purpose of this function is to check weather or not
we are at the end of the file.  This is accomplished by
returning true if we are at the end of our file and false
if we are not at the end of the file.

RETURNS
Returns true if we reached the end of our file and false
if we haven't.
*/
/**/
bool FileAccess::AtEndOfFile()
{
	// This goes to the end of the file and if it
	// reaches the end then it returns true otherwise
	// it returns false.
	if(!m_sfile.eof())
	{
		return false;
	}
	else
	{
		return true;
	}
}