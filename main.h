#ifndef MAIN__H
#define MAIN__H

#include <iostream>

#define ARG_PROCESS_COMPRESS	"compress"
#define ARG_PROCESS_DECOMPRESS	"decompress"
#define ARG_METHOD_NORMAL	"normal"
#define ARG_METHOD_LIST		"list"
#define ARG_METHOD_TREE		"tree"

typedef enum {
	COMPRESS,
	DECOMPRESS
} process_t;

static void opt_input(std::string const &);
static void opt_output(std::string const &);
static void opt_process(std::string const &);
static void opt_method(std::string const &);

#endif
