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
* Internal DSL example 1. 
*
* Support code. 
*
* The idea is to use syntax of function with variable-length argument list
* as the basis of DSL constructions and hide "syntactic noise" by wrapping
* it into parametrized macros.
*
*******************************************************************************/

const int afterLastField = -1;

ReaderStrategy mapping(const char *code, Storable::Type type, ...) {

	ReaderStrategy strategy(code, type);

	va_list arg;
	va_start(arg, type);	
	for (;;) {
		int start = va_arg(arg, int);
		if (start == afterLastField)
			break;
		int end = va_arg(arg, int);
		const char *name = va_arg(arg, const char*);
		strategy.AddFieldExtractor(start, end, name);
	}
	va_end(arg);

	return strategy;
}

Reader FillReader(const char *name, ...) {
	Reader reader;

	va_list arg;
	va_start(arg, name);	
	for (;;) {
		ReaderStrategy strategy = va_arg(arg, ReaderStrategy);
		if (strategy.Code() == "NULL")
			break;
		reader.AddStrategy(strategy);
	}
	va_end(arg);

	return reader;
}

#define begin_reader_dsl \
	Reader ConfigureReader() { \
		return FillReader("DUMMY", \

#define begin_mapping(code, className) \
	mapping(code, Storable::type##className \

#define end_mapping \
		afterLastField) \

#define end_reader_dsl \
		, ReaderStrategy("NULL")); \
	} \


