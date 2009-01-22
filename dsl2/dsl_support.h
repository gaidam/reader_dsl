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
* Internal DSL example 2. 
*
* Support code. 
*
* The idea is to use syntax of initializer for array of structures as the basis 
* of DSL constructions and hide "syntactic noise" by wrapping it into 
* parametrized macros.
*
*******************************************************************************/

struct FieldDescr {
	int start;
	int end;
	const char *name;
};

FieldDescr afterLastField = {
	-1, -1, ""
};

const int MAX_FIELDS = 100;

struct StrategyDescr {
	const char *code;
	Storable::Type type;
	FieldDescr fields[MAX_FIELDS];
};

Reader FillReader(StrategyDescr strategies [], unsigned count) {
	Reader reader;	
	for (unsigned i = 0; i < count; i++) {
		const StrategyDescr &d = strategies[i];
		ReaderStrategy strategy(d.code, d.type);
		for (unsigned j = 0;; j++) {
			const FieldDescr &f = d.fields[j];
			if (f.start == -1)
				break;
			strategy.AddFieldExtractor(f.start, f.end, f.name);
		}		
		reader.AddStrategy(strategy);
	}
	return reader;
}

#define begin_reader_dsl \
	Reader ConfigureReader() { \
		StrategyDescr array [] = \
		{ \

#define end_reader_dsl \
	};	\
	unsigned count = sizeof(array)/sizeof(StrategyDescr); \
	return FillReader(array, count); \
} \

#define begin_mapping(code, className) \
	{ \
	code, Storable::type##className, \
		{ \

#define end_mapping \
		, afterLastField \
		} \
	} \


