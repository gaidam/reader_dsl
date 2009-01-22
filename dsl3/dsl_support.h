/******************************************************************************
* C++ implementation of internal DSL from Martin Fowler's article.
* See http://martinfowler.com/articles/languageWorkbench.html for more 
* information.
*
* Author:
*   Dmitry Gaidamovitch 
*	gaidam@mail.ru
*
* dsl_support.h
*
* Internal DSL example 3.
*
* Support code. 
*
* The idea is to use syntax of overloaded operator <<  as the basis of DSL 
* constructions, state machine for addressing next operator call and hide 
* "syntactic noise" by wrapping it into parametrized macros.
*
*******************************************************************************/

class ReaderStrategyFiller {
public:

	// Exception classes for input error handling
	class Error {};
	class BeginExpected : Error {};
	class EndExpected : Error {};
	class NameExpected : Error {};

	// State for addressing next << call
	enum State { sBegin, sEnd, sName };

	ReaderStrategyFiller(const string &code, Storable::Type target) 
		: strategy(code, target), currentState(sBegin) {}

	ReaderStrategyFiller &operator << (int n) {
		switch (currentState) {
		case sBegin:
			begin = n;
			currentState = sEnd;
			break;
		case sEnd:
			end = n;
			currentState = sName;
			break;
		default:
			throw NameExpected();
		}
		return *this;
	}

	ReaderStrategyFiller &operator << (const string &str) {
		switch (currentState) {
		case sBegin:
			throw BeginExpected();
		case sEnd:
			throw EndExpected();
		}
		currentState = sBegin;
		strategy.AddFieldExtractor(begin, end, str);
		return *this;
	}

	operator ReaderStrategy& () { return strategy; }


private:
	ReaderStrategy strategy;
	State currentState;

	int begin;
	int end;
};


#define begin_reader_dsl \
	Reader ConfigureReader() { \
		Reader reader; \

#define end_reader_dsl \
	return reader;	\
	} \
	

#define begin_mapping(code, className) \
	{ \
	ReaderStrategyFiller strategy(code, Storable::type##className); \
	strategy \

#define end_mapping \
	; reader.AddStrategy(strategy); \
	} \

