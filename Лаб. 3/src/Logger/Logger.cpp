/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 17.10.2019
 */

#include "Logger.h"
#include <iostream>
#include <ctime>

/*
 * This file defines methods of class Logger,
 * which is described in Logger.h.
 * See all interface description in the header file.
 */

using namespace std;


Logger logger("log.txt");


std::string Logger::_get_current_time()
{
	std::time_t now = time(0);
	std::tm *tm_struct;
	char buf[80];

	tm_struct = localtime(&now);
	strftime(buf, sizeof(buf), "%F.%X", tm_struct);

	return buf;
}

Logger::Logger(const std::string& file_name, bool std_output)
	: _log_file(file_name, std::ios::out | ios::trunc), _std_output(std_output) {}

void Logger::open(const std::string& file_name)
{
	std::lock_guard guard(_locker);
	if (_log_file.is_open()) {
		_log_file.close();
	}

	_log_file.open(file_name, std::ios::out | ios::trunc);
}

