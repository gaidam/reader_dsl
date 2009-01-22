/******************************************************************************
* C++ implementation of internal DSL from Martin Fowler's article.
* See http://martinfowler.com/articles/languageWorkbench.html for more 
* information.
*
* Author:
*   Dmitry Gaidamovitch 
*	gaidam@mail.ru
*
* reader.h
*
* Classes: Reader, ReaderStrategy, FieldExtractor.
*
* This code is simple port of Java one in article to C++. Differences
* caused by not using reflection and Activator. Instead we use Storable-based
* classes and factory method in storable.h
*******************************************************************************/

class FieldExtractor {
public:
	FieldExtractor(int _begin, int _end, const string &_targetPropertyName) : 
		begin(_begin), end(_end), targetPropertyName(_targetPropertyName) {}

	void ExtractField(const string &line, Storable &targetObject) {
		targetObject[targetPropertyName] = string(line, begin, end - begin);
	}
private:
	int begin;
	int end;
	string targetPropertyName;
};


class ReaderStrategy {		
public:
	ReaderStrategy() : code("SVCL"), target(Storable::typeServiceCall) { }

	ReaderStrategy(const string &_code, Storable::Type _target = Storable::typeServiceCall)
		: code(_code), target(_target) {}

	string Code() { return code; }

	Storable *Process(const string &line) {
		Storable *object = Storable::Create(target);
		for (unsigned i = 0; i < extractors.size(); i++)
			extractors[i].ExtractField(line, *object);
		return object;
	}

	void AddFieldExtractor(int _begin, int _end, const string &_targetPropertyName) {
		extractors.push_back(FieldExtractor(_begin, _end, _targetPropertyName));
	}
private:
	string code;
	Storable::Type target;
	vector<FieldExtractor> extractors;
};


class Reader {
public:
	typedef map<string, ReaderStrategy> Strategies;

	static const int CODE_LEN = 4;

	class UnknownTypeCodeException {};

	void Process(istream &in, StorableVector &result) {
		string line;
		while (getline(in, line))
			ProcessLine(line, result);
	}

	void ProcessLine(const string &line, StorableVector &result) {		
		if (!IsBlank(line) && !IsComment(line)) {
			string typeCode = GetTypeCode(line);
			Strategies::iterator iter = strategies.find(typeCode);
			if (iter == strategies.end())
				throw UnknownTypeCodeException();			
			result.push_back(iter->second.Process(line));
		}
	}

	static string GetTypeCode(const string &line) {
		return string(line, 0, CODE_LEN);
	}

	static bool IsComment(const string &line) {  return line[0] == '#';      }

	static bool IsBlank(const string &line)   {  return line.length() == 0;  }

	void AddStrategy(ReaderStrategy &strategy) {   strategies[strategy.Code()] = strategy;  }

	Reader() {}

private:
	Strategies strategies;
};

