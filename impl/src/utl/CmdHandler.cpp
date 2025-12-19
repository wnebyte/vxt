#include <list>
#include <poll.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include "utl/CmdHandler.hpp"

#define NUM_OF_FDS 1
#define POLL_TIMEOUT 50

using namespace vxt;
using namespace utl;
using CommandMap = std::map<std::string, CmdHandler::Command>;

CommandMap CmdHandler::m_cmds;
extern char **environ;

CmdHandler::CmdHandler()
	: ufw::thread("CmdHandler")
{
	if (!set_priority(PRIORITY_MIN)) {
		UFW_ASSERT((false) && ("failed to set thread priority"));
	}

	m_cmds.insert(std::make_pair("setenv", &handleSetEnv));
	m_cmds.insert(std::make_pair("print", &handlePrint));
}

void CmdHandler::handleSetEnv(const std::string &args)
{
	const std::vector<std::string> v{ufw::split(args, ' ')};
	
	if (v.size() >= 2) {
		setenv(v[0].c_str(), v[1].c_str(), 1);
	}
}

void CmdHandler::handlePrint(const std::string &args)
{
	const std::vector<std::string> v{ufw::split(args, ' ')};
	std::list<std::string> queue{v.begin(), v.end()}; 

	if (queue.empty()) {
		char **env = environ;
		for (; *env != NULL; ++env) {
			/// TODO: should probably only print the env if it starts with VXT_
			std::printf("%s\n", *env);
		}
	}

	while (!queue.empty()) {
		const char *name = queue.front().c_str();
		const char *env = std::getenv(name);
		std::printf("%s=%s\n", name, (env != NULL) ? env : "NULL");
		queue.pop_front();
	}
}

void CmdHandler::handleCommand(const std::string &cmd)
{
	static const std::string delimiter = " ";
	const std::size_t index = cmd.find(delimiter);
	const std::string token = cmd.substr(0, index);
	CommandMap::iterator iter = m_cmds.find(token);

	if (iter != m_cmds.end()) {
		const std::string args = (cmd.length() > token.length()) ? cmd.substr(index + 1) : "";
		(iter->second)(args);
	}
}

void CmdHandler::run(void)
{
	pollfd fds[NUM_OF_FDS];

	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	while (!is_interrupted()) {
		if (poll(fds, ARRAY_SIZE(fds), POLL_TIMEOUT) > 0) {
			std::string line;
			getline(std::cin, line);
			handleCommand(line);
		}
	}
}
