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

using namespace std;

class LOG {
	CONSTS consts;

	/**
	 * Получить текущее время
	 * 
	 * @return string
	 */
	string getTime(){
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		return asctime(timeinfo);
	}

	/**
	 * Удалить \n 
	 * 
	 * @param string
	 * @return string
	 */
	string trim(string str){
		string::size_type pos = str.find_first_not_of("\n");
    	string::size_type pos1 = str.find_last_not_of("\n");
    	return str.substr(pos,pos1-pos+1);
	}

public:
	/**
	 * Печать лога по заданному типу
	 * 
	 * @param
	 * @param
	 */
	void print_log(string str, string type){
		printf("{%s} [%s] %s\n", 
			this->trim(this->getTime()).c_str(), 
			(consts.find(type) + type + ENDC).c_str(), 
			this->trim(str).c_str()
		);
	}
};