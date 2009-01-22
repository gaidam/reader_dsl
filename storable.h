/******************************************************************************
* C++ implementation of internal DSL from Martin Fowler's article.
* See http://martinfowler.com/articles/languageWorkbench.html for more 
* information.
*
* Author:
*   Dmitry Gaidamovitch 
*	gaidam@mail.ru
*
* storable.h
*
* We don't have reflection in C++ to put the value into the target object,
* and we don't want to use special libraries  for the purpose of simple example. 
* And so we use map as base class for our "storable" classes.
*
* We don't have "object" class and Activator.CreateInstance() that creates the 
* object of target class by its type. Instead of this we use typical C++ approach: 
* we create base class Storable for all target classes such as ServiceCall and 
* Usage. Static function Create() in class Storable works as a factory method. 
* We derive classes ServiceCall, Usage from base class Storable and we use Create() 
* to allocate specific object by its class type, returning pointer to the base 
* class, in ReaderStrategy. 
*
* StorableVector is simple vector for polymorphous Storable-based objects,
* with automatic memory release in destructor.
*
*******************************************************************************/

struct Storable : public map<string, string> {
	enum Type { typeServiceCall, typeUsage };
	static Storable *Create(Type);
	virtual ~Storable() {}
};

struct ServiceCall : public Storable {};

struct Usage : public Storable {};

Storable *Storable::Create(Storable::Type type) {
	if (type == typeServiceCall)
		return new ServiceCall();
	return new Usage();
}

struct StorableVector : public vector<Storable*> {
	~StorableVector() {
		for (iterator i = begin(); i != end(); i++)
			delete *i;
	}
};

