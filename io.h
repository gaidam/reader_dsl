/******************************************************************************
* C++ implementation of internal DSL from Martin Fowler's article.
* See http://martinfowler.com/articles/languageWorkbench.html for more 
* information.
*
* Author:
*   Dmitry Gaidamovitch 
*	gaidam@mail.ru
*
* io.h
*
* Simple input-output helpers for Storable objects.
*
* Function ConfigureReader() must be implemented somewhere in the rest code.
* As we want to illustrate different approaches of implementing the internal DSL,
* we configure our reader with the different kinds of it.
*
*******************************************************************************/

Reader ConfigureReader();

void operator >> (istream &in, StorableVector &objects) {	
	ConfigureReader().Process(in, objects);
}

ostream & operator << (ostream &stream, Storable &storable) {
	for (Storable::iterator i = storable.begin(); i != storable.end(); i++)
		stream << i->first << " = " << i->second << endl;
	return stream;
}

void operator << (ostream &stream, StorableVector &objects) {
	for (unsigned i = 0; i < objects.size(); i++)
		stream << (*objects[i]) << endl;
}

