/******************************************************************************
* C++ implementation of internal DSL from Martin Fowler's article.
* See http://martinfowler.com/articles/languageWorkbench.html for more 
* information.
*
* Author:
*   Dmitry Gaidamovitch 
*	gaidam@mail.ru
*
* reader_dsl.h
*
* The entry point for the console application.
*
*******************************************************************************/

#include "stdafx.h"
#include "storable.h"
#include "reader.h"
#include "io.h"
#include "dsl_support.h"
#include "dsl_code.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cout << "Input file name as command line parameter\n";
		return 1;
	}
	ifstream in(argv[1]);
	if (!in) {
		cout << "Cannot open file\n";
		return 2;
	}
	StorableVector objects;
	in >> objects;

	cout  << endl << "Inspecting objects just read:" << endl << endl;
	cout << objects;
	return 0;
}

