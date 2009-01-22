/******************************************************************************
* C++ implementation of internal DSL from Martin Fowler's article.
* See http://martinfowler.com/articles/languageWorkbench.html for more 
* information.
*
* Author:
*   Dmitry Gaidamovitch 
*	gaidam@mail.ru
*
* dsl_code.h
*
* Internal DSL example 1. 
*
* This code is internal DSL code itself.
*
*******************************************************************************/

begin_reader_dsl	

	begin_mapping("SVCL", ServiceCall),
			4, 18, "CustomerName",
			19, 23, "CustomerID",
			24, 27, "CallTypeCode",
			28, 35, "DateOfCallString", 
		end_mapping,

	begin_mapping("USGE", Usage),
			4, 8, "CustomerID",
			9, 22, "CustomerName",
			30, 30, "Cycle",
			31, 36, "ReadDate",
		end_mapping
				
end_reader_dsl

