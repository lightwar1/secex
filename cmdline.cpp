#include <string>

#include "cmdline.hpp"

using namespace std;

class CMDLINE {
	cmdline::parser argParser;
public:
	CMDLINE(int argc, char *argv[]) {
		// 1st argument is long name
		// 2nd argument is short name (no short name if '\0' specified)
		// 3rd argument is description
		// 4th argument is mandatory (optional. default is false)
		// 5th argument is default value  (optional. it used when mandatory is false)
		argParser.add<string>("host", 'h', "hostname", true, 0);

		// 6th argument is extra constraint.
		// Here, port number must be 1 to 65535 by cmdline::range().
		// a.add<int>("port", 'p', "port number", false, 80, cmdline::range(1, 65535));

		// Run parser.
		// It returns only if command line arguments are valid.
		// If arguments are invalid, a parser output error msgs then exit program.
		// If help flag ('--help' or '-?') is specified, a parser output usage message then exit program.
		argParser.parse_check(argc, argv);
	}
};