#include <iostream>
#include "LZW.h"
#include "Dictionary.h"

void compress(std::istream & is, std::ostream & os, method_t method)
{
	unsigned char c;
	uint16_t i, aux;
	Dictionary dic;
	Symbol symbol; // Símbolo auxiliar

	symbol.setPrefijo(NULL_SYMBOL);

	while (is.read(reinterpret_cast<char *>(&c), 1))
	{
		symbol.setSufijo(c);

		if ((i = dic.FindSymbol(symbol, method)) != NULL_SYMBOL)
			symbol.setPrefijo(i);
		else
		{
			dic.AddSymbol(symbol, method);
			aux = symbol.getPrefijo();
			os.write(reinterpret_cast<char *>(&aux), sizeof(uint16_t));
			symbol.setPrefijo((uint16_t)symbol.getSufijo());

			if (dic.IsFull())
				dic.Restart();
		}
	}
	if ((i = symbol.getPrefijo()) != NULL_SYMBOL)
		os.write(reinterpret_cast<char *>(&i), sizeof(uint16_t));
}

void decompress(std::istream & is, std::ostream & os, method_t method)
{
	uint16_t index, old_index;
	Dictionary dic;
	Symbol symbol; // Símbolo auxiliar

	is.read(reinterpret_cast<char *>(&index), sizeof(uint16_t));
	if (is.good())
		dic.PrintSymbol(os, index);

	for (old_index = index;
	     is.read(reinterpret_cast<char *>(&index), sizeof(uint16_t));
	     old_index = index)
	{
		if (dic.HasIndex(index))
		{
			dic.PrintSymbol(os, index);
			symbol.setPrefijo(old_index);
			symbol.setSufijo(dic.GetStartingSymbol(index).getSufijo());
			dic.AddSymbol(symbol, method);
		}
		else
		{
			symbol.setPrefijo(old_index);
			symbol.setSufijo(dic.GetStartingSymbol(old_index).getSufijo());
			dic.PrintSymbol(os, dic.AddSymbol(symbol, method));
		}

		if (dic.IsFull())
			dic.Restart();
	}
}
