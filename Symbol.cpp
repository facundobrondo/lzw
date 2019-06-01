#include <iostream>
#include "Symbol.h"


Symbol::Symbol() {
	prefijo = sufijo = primero = siguiente = izquierdo = derecho = NULL_SYMBOL;
}

Symbol::~Symbol()
{}

Symbol::Symbol(unsigned char c) {
	prefijo = primero = siguiente = izquierdo = derecho = NULL_SYMBOL;
	sufijo = c;
}

Symbol::Symbol(uint16_t i, unsigned char c) {
	primero = siguiente = izquierdo = derecho = NULL_SYMBOL;
	prefijo = i;
	sufijo = c;
}

Symbol::Symbol(const Symbol & s) {
	primero = siguiente = izquierdo = derecho = NULL_SYMBOL;
	prefijo = s.prefijo;
	sufijo = s.sufijo;
}

Symbol const & Symbol::operator=(Symbol const & s)
{
	prefijo = s.prefijo;
	sufijo = s.sufijo;
	primero = s.primero;
	siguiente = s.siguiente;
	izquierdo = s.izquierdo;
	derecho = s.derecho;

	return *this;
}

bool Symbol::operator==(const Symbol & s) const
{
	if (s.getPrefijo() == prefijo && s.getSufijo() == sufijo)
		return true;

	return false;
}

bool Symbol::operator!=(const Symbol & s) const
{
	return !(*this == s);
}

std::ostream & operator<<(std::ostream & os, const Symbol & s)
{
	return os.write(reinterpret_cast<const char *>(&(s.sufijo)), 1);
}

void Symbol::setPrefijo(uint16_t i)
{
	prefijo = i;
}

void Symbol::setSufijo(unsigned char c)
{
	sufijo = c;
}

void Symbol::setPrimero(uint16_t i)
{
	primero = i;
}

void Symbol::setSiguiente(uint16_t i)
{
	siguiente = i;
}

void Symbol::setIzquierdo(uint16_t i)
{
	izquierdo = i;
}

void Symbol::setDerecho(uint16_t d)
{
	derecho = d;
}

uint16_t Symbol::getPrefijo(void) const
{
	return prefijo;
}

unsigned char Symbol::getSufijo(void) const
{
	return sufijo;
}

uint16_t Symbol::getPrimero(void) const
{
	return primero;
}

uint16_t Symbol::getSiguiente(void) const
{
	return siguiente;
}

uint16_t Symbol::getIzquierdo(void) const
{
	return izquierdo;
}

uint16_t Symbol::getDerecho(void) const
{
	return derecho;
}

bool Symbol::IsFirstSymbol(void) const
{
	return prefijo == NULL_SYMBOL;
}
