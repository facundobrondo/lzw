#ifndef SYMBOL_H
#define SYMBOL_H

#include <iostream>

#define NULL_SYMBOL 65535

class Symbol {
	private:
		uint16_t prefijo;
		unsigned char sufijo;
		uint16_t primero; // Primer símbolo con este como prefijo
				  // Usado en lista y árbol
		uint16_t siguiente; // Siguiente símbolo con  mismo prefijo
				    // Usado en lista
		uint16_t izquierdo; // Nodo izquierdo del árbol de símbolos
				    // de mismo prefijo
		uint16_t derecho;   // Nodo derecho del árbol de símbolos
				    // de mismo prefijo

	public:
		Symbol();
		Symbol(unsigned char); // Crea el símbolo < ø ,c >
		Symbol(uint16_t, unsigned char); //Símbolo con un índice al símbolo previo
		Symbol(const Symbol &);
		~Symbol();
		Symbol const & operator=(Symbol const &);
		bool operator==(const Symbol &) const;
		bool operator!=(const Symbol &) const;
		friend std::ostream & operator<<(std::ostream &, const Symbol &);
		void setPrefijo(uint16_t);
		void setSufijo(unsigned char);
		void setPrimero(uint16_t);
		void setSiguiente(uint16_t);
		void setIzquierdo(uint16_t);
		void setDerecho(uint16_t);
		uint16_t getPrefijo(void) const;
		unsigned char getSufijo(void) const;
		uint16_t getPrimero(void) const;
		uint16_t getSiguiente(void) const;
		uint16_t getIzquierdo(void) const;
		uint16_t getDerecho(void) const;
		bool IsFirstSymbol(void) const;
};

#endif
