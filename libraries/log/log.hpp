/**
 * LOG
 *
 * v 1.0
 */

#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>

#include "consts.h"

// using namespace std;

class LOG {
	CONSTS consts;

	/**
	 * Получить текущее время
	 *
	 * @return string
	 */
	std::string getTime() {
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		return asctime(timeinfo);
	}

	/**
	 * Remove \n
	 *
	 * TODO: перевести на сссылки | remake with using pointer
	 *
	 * @param string
	 * @return string
	 */
	std::string trim(std::string str) {
		std::string::size_type pos = str.find_first_not_of("\n");
		std::string::size_type pos1 = str.find_last_not_of("\n");
		return str.substr(pos, pos1 - pos + 1);
	}

public:
	/**
	 * Печать лога по заданному типу
	 *
	 * @param
	 * @param
	 */
	void print_log(std::string str, std::string type) {
		printf("{%s} [%s] %s\n",
			(this->trim(this->getTime().c_str())).c_str(),
		    (consts.find(type) + type + ENDC).c_str(),
		    this->trim(str).c_str()
		);
	}
};