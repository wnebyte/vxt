#ifndef VXT_CMD_HANDLER_HPP
#define VXT_CMD_HANDLER_HPP

#include <map>
#include <functional>

#include "Types.hpp"

namespace vxt {
namespace utl
{
class CmdHandler : public ufw::thread {
public:
	typedef std::function<void(const std::string &args)> Command;

public:
	CmdHandler();
	~CmdHandler() noexcept = default;

protected: // thread implementation
	void run(void) override;

private:
	static void handleCommand(const std::string &cmd);
	static void handleSetEnv(const std::string &args);
	static void handlePrint(const std::string &args);

private:
	static std::map<std::string, Command> m_cmds;
};
} // namespace utl
} // namespace vxt

#endif // VXT_CMD_HANDLER_HPP
