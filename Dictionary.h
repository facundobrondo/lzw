#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include "Symbol.h"

#define MAX_ELEMENTS 65535
#define ASCII_ELEMENTS 256

typedef enum {
	METHOD_NORMAL,
	METHOD_LIST,
	METHOD_TREE
} method_t;

class Dictionary {
	private:
		Symbol arr[MAX_ELEMENTS];
		uint16_t len;
		uint16_t _AddSymbolNormal(const Symbol &);
		uint16_t _AddSymbolList(const Symbol &);
		uint16_t _AddSymbolTree(const Symbol &);
		uint16_t _FindSymbolNormal(const Symbol &);
		uint16_t _FindSymbolList(const Symbol &);
		uint16_t _FindSymbolTree(const Symbol &);

	public:
		Dictionary();
		~Dictionary();
		void Restart(void);
		uint16_t AddSymbol(const Symbol &, method_t);
		void PrintSymbol(std::ostream &, uint16_t);
		uint16_t FindSymbol(const Symbol &, method_t);
		bool HasIndex(uint16_t);
		bool IsFull(void);
		const Symbol & GetStartingSymbol(uint16_t) const;
};

#endif
