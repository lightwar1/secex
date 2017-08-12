#define ENDC      "\x1b[0m"
#define HEADER    "\x1b[95m"
#define OKBLUE    "\x1b[94m"
#define	OKGREEN   "\x1b[92m"
#define WARNING   "\x1b[93m"
#define	FAIL      "\x1b[91m"
#define	ENDC      "\x1b[0m"
#define BOLD      "\x1b[1m"
#define UNDERLINE "\x1b[4m"

#define INFO    "\x1b[1;32m"
#define ERROR   "\x1b[1;31m"
#define DEBUG   "\x1b[1;36m"
#define VERBOSE "\x1b[1;35m"

#include <map>
#include <string>

class CONSTS {
public:
	std::map<std::string, std::string> map;

	CONSTS() {
		map = {
			{"INFO", INFO},
			{"DEBUG", DEBUG},
			{"ERROR", ERROR},
			{"VERBOSE", VERBOSE},
			{"ENDC", ENDC}
		};
	}

	/**
	 * Поиск в константах
	 * Search in consts
	 * 
	 * @param string  type of search
	 * @return string bash code
	 */
	std::string find(std::string type) {
		return (*this->map.find(type)).second;
	}
};