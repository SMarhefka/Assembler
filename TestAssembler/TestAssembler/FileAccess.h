// Svetlana Marhefka
// File access to source file.

// This is the way that multiple inclusions are 
// defended against often used in UNIX
#ifndef _FILEACCESS_H
// We use pramas in Visual Studio.  
// See other include files
#define _FILEACCESS_H

#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess
{
public:
	// Opens the file.
	FileAccess(int argc, char *argv[]);

	// Closes the file.
	~FileAccess();

	// Get the next line from the source file.
	bool GetNextLine(string &a_buff);

	// Put the file pointer back to the beginning of the file.
	// Changed r to uppercase to keep with the sytling
	void Rewind();

	bool AtEndOfFile();

private:
	// Source file object.
	ifstream m_sfile;
};
#endif

