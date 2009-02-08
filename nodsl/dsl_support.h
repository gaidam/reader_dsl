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
* Internal DSL example.
*
* Support code for non-dsl implementation. 
*
* The idea is to use syntax of overloaded operator <<  as the basis of DSL 
* constructions, state machine for addressing next operator call and hide 
* "syntactic noise" by wrapping it into parametrized macros.
*
*******************************************************************************/

Reader ConfigureReader() { 
	Reader reader;
	{
		ReaderStrategy strategy("SVCL", Storable::typeServiceCall);
		strategy.AddFieldExtractor(4, 18, "CustomerName");
		strategy.AddFieldExtractor(19, 23, "CustomerID");
		strategy.AddFieldExtractor(24, 27, "CallTypeCode");
		strategy.AddFieldExtractor(28, 35, "DateOfCallString");
		reader.AddStrategy(strategy);
	}
	{
		ReaderStrategy strategy("USGE", Storable::typeUsage);
		strategy.AddFieldExtractor(4, 8, "CustomerID");
		strategy.AddFieldExtractor(9, 22, "CustomerName");
		strategy.AddFieldExtractor(30, 30, "Cycle");
		strategy.AddFieldExtractor(31, 36, "ReadDate");
		reader.AddStrategy(strategy);
	}
	return reader;	
} 

