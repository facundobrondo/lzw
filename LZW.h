#ifndef LZW__H
#define LZW__H

#include <iostream>
#include "Dictionary.h"

void compress(std::istream &, std::ostream &, method_t);
void decompress(std::istream &, std::ostream &, method_t);

#endif
