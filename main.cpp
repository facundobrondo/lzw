#include <iostream>
#include <fstream>
#include "main.h"
#include "cmdline.h"
#include "LZW.h"

using namespace std;

static option_t options[] = {
	{1, "i",  "input",   "-",		   opt_input,	OPT_DEFAULT},
	{1, "o",  "output",  "-",		   opt_output,	OPT_DEFAULT},
	{1, "p",  "process", ARG_PROCESS_COMPRESS, opt_process,	OPT_DEFAULT},
	{1, "m",  "method",  ARG_METHOD_NORMAL,	   opt_method,	OPT_DEFAULT},
	{0, NULL, NULL,	     NULL,		   NULL,	0},
};

static istream * iss = NULL;
static ostream * oss = NULL;
static fstream ifs;
static fstream ofs;
static process_t process;
static method_t method;

static void opt_input(string const & arg)
{
	if (arg == "-")
		iss = &cin;
	else {
		ifs.open(arg.c_str(), ios::in | ios::binary);
		iss = &ifs;
	}

	*iss >> noskipws;

	if (!iss->good()) {
		cerr << "No se pudo abrir "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}	
}

static void opt_output(string const & arg)
{
	if (arg == "-")
		oss = &cout;
	else {
		ofs.open(arg.c_str(), fstream::out | fstream::binary);
		oss = &ofs;
	}

	if (!oss->good()) {
		cerr << "No se pudo abrir "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void opt_process(string const & str)
{
	if (str == ARG_PROCESS_COMPRESS)
		process = COMPRESS;
	else if (str == ARG_PROCESS_DECOMPRESS)
		process = DECOMPRESS;
	else {
		cerr << "Proceso "
		     << str
		     << " no reconocido."
		     << endl;
		exit(1);
	}
}

static void opt_method(string const & str)
{
	if (str == ARG_METHOD_NORMAL)
		method = METHOD_NORMAL;
	else if (str == ARG_METHOD_LIST)
		method = METHOD_LIST;
	else if (str == ARG_METHOD_TREE)
		method = METHOD_TREE;
	else {
		cerr << "Método "
		     << str
		     << " no reconocido."
		     << endl;
		exit(1);
	}
}

int main(int argc, char * const argv[])
{
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	process == COMPRESS ? compress(*iss, *oss, method) : decompress(*iss, *oss, method);

	return EXIT_SUCCESS;
}
