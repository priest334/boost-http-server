// auth_server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <sstream>
#include <string>
#include "server.h"

#ifndef _WIN32
#include <unistd.h>
#endif // !_WIN32

namespace opts = boost::program_options;

int main(int argc, char* argv[]) {
	opts::options_description desc;
	desc.add_options()
		("daemon", opts::bool_switch()->default_value(false))
		("host", opts::value<std::string>()->default_value("127.0.0.1"))
		("port", opts::value<int>()->default_value(2020))
		("threads", opts::value<int>()->default_value(20));

	opts::variables_map args;
	opts::store(opts::parse_command_line(argc, argv, desc), args);

	if (args["daemon"].as<bool>()) {
#ifndef _WIN32
		pid_t pid = fork();
		if (pid != 0) {
			return 0;
		}
#endif // !_WIN32
	}

	std::ostringstream oss;
	oss << args["port"].as<int>();

	ntq::HttpServer server(args["threads"].as<int>());
	server.Start(args["host"].as<std::string>(), oss.str());
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
