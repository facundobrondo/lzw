#include "Dictionary.h"
#include "Symbol.h"

Dictionary::Dictionary()
{
	for (uint16_t c = 0; c < ASCII_ELEMENTS; c++)
		arr[c] = Symbol((unsigned char)c);

	len = ASCII_ELEMENTS;
}

Dictionary::~Dictionary()
{}

// Pone el diccionario en un estado limpio
void Dictionary::Restart(void)
{
	Dictionary();
}

// Agrega el símbolo al diccionario y devuelve el índice añadido.
// Si el arreglo ya se llenó, no hace nada y devuelve MAX_ELEMENTS
uint16_t Dictionary::_AddSymbolNormal(const Symbol & s)
{
	if (len == MAX_ELEMENTS)
		return len;

	arr[len] = s;

	return len++;
}

// Agrega el símbolo al diccionario y devuelve el índice añadido.
// Si el arreglo ya se llenó, no hace nada y devuelve MAX_ELEMENTS
uint16_t Dictionary::_AddSymbolList(const Symbol & s)
{
	if (len == MAX_ELEMENTS)
		return len;

	arr[len] = s;
	arr[len].setPrimero(NULL_SYMBOL);
	// el siguiente de s es el primero de su prefijo
	arr[len].setSiguiente(arr[s.getPrefijo()].getPrimero());
	// el primero del prefijo es el índice de s
	arr[s.getPrefijo()].setPrimero(len);

	return len++;
}

// Agrega el símbolo al diccionario y devuelve el índice añadido.
// Si el símbolo ya estaba en el diccionario, devuelve su índice.
// Si el arreglo ya se llenó, no hace nada y devuelve MAX_ELEMENTS
uint16_t Dictionary::_AddSymbolTree(const Symbol & s)
{
	uint16_t raiz, nodo;

	if (len == MAX_ELEMENTS)
		return len;

	raiz = arr[s.getPrefijo()].getPrimero();

	if (raiz == NULL_SYMBOL) {
		arr[s.getPrefijo()].setPrimero(len);
		arr[len] = s;
		return len++;
	}

	nodo = raiz;

	for (;;) {
		if (s.getSufijo() < arr[nodo].getSufijo()) {
			if (arr[nodo].getIzquierdo() != NULL_SYMBOL) {
				nodo = arr[nodo].getIzquierdo();
			} else {
				arr[nodo].setIzquierdo(len);
				arr[len] = s;
				return len++;
			}
		} else if (s.getSufijo() > arr[nodo].getSufijo()) {
			if (arr[nodo].getDerecho() != NULL_SYMBOL) {
				nodo = arr[nodo].getDerecho();
			} else {
				arr[nodo].setDerecho(len);
				arr[len] = s;
				return len++;
			}
		} else
			return nodo;
	}
}
				
uint16_t Dictionary::AddSymbol(const Symbol & s, method_t method)
{
	switch (method) {
		case METHOD_NORMAL:
			return _AddSymbolNormal(s);
		case METHOD_LIST:
			return _AddSymbolList(s);
		case METHOD_TREE:
			return _AddSymbolTree(s);
		default:
			return NULL_SYMBOL;
	}
}

void Dictionary::PrintSymbol(std::ostream & os, uint16_t i)
{
	if (!(arr[i].IsFirstSymbol()))
		PrintSymbol(os, arr[i].getPrefijo());

	os << arr[i];
}

// Si encuentra el símbolo, devuelve su índice
// caso contrario devuelve NULL_SYMBOL
uint16_t Dictionary::_FindSymbolNormal(const Symbol & s)
{
	if (s.getPrefijo() == NULL_SYMBOL)
		return (uint16_t)s.getSufijo(); // los primeros elementos tienen
						// índice == sufijo

	for (uint16_t i = ASCII_ELEMENTS; i < len; ++i)
		if (s == arr[i])
			return i;

	return NULL_SYMBOL;
}

// Si encuentra el símbolo, devuelve su índice
// caso contrario devuelve NULL_SYMBOL
uint16_t Dictionary::_FindSymbolList(const Symbol & s)
{
	uint16_t i;
	if (s.getPrefijo() == NULL_SYMBOL)
		return (uint16_t)s.getSufijo(); // los primeros elementos tienen
						// índice == sufijo

	i = arr[s.getPrefijo()].getPrimero();

	while (i != NULL_SYMBOL && arr[i] != s)
		i = arr[i].getSiguiente();

	return i;
}

// Si encuentra el símbolo, devuelve su índice.
// caso contrario devuelve NULL_SYMBOL
uint16_t Dictionary::_FindSymbolTree(const Symbol & s)
{
	uint16_t i;
	if (s.getPrefijo() == NULL_SYMBOL)
		return (uint16_t)s.getSufijo(); // los primeros elementos tienen
						// índice == sufijo

	i = arr[s.getPrefijo()].getPrimero();

	while (i != NULL_SYMBOL && arr[i] != s) {
		if (s.getSufijo() < arr[i].getSufijo())
			i = arr[i].getIzquierdo();
		else
			i = arr[i].getDerecho();
	}

	return i;
}

uint16_t Dictionary::FindSymbol(const Symbol & s , method_t method)
{
	switch (method) {
		case METHOD_NORMAL:
			return _FindSymbolNormal(s);
		case METHOD_LIST:
			return _FindSymbolList(s);
		case METHOD_TREE:
			return _FindSymbolTree(s);
		default:
			return NULL_SYMBOL;
	}
}

bool Dictionary::HasIndex(uint16_t i)
{
	return i < len;
}

bool Dictionary::IsFull(void)
{
	return len >= MAX_ELEMENTS;
}

const Symbol & Dictionary::GetStartingSymbol(uint16_t i) const
{
	if (arr[i].IsFirstSymbol())
		return arr[i];

	return GetStartingSymbol(arr[i].getPrefijo());
}
