
#ifndef PREPARE_CONSOLE_LOGGER
#define PREPARE_CONSOLE_LOGGER

//----------------------------------------
//	include
//----------------------------------------
#include <string>

#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Logger.h>

//----------------------------------------
//	PrepareConsoleLogger
//----------------------------------------
class PrepareConsoleLogger
{
public:
	PrepareConsoleLogger(const std::string& name, int level=Poco::Message::PRIO_INFORMATION);
	~PrepareConsoleLogger();

private:
	PrepareConsoleLogger();
	PrepareConsoleLogger(const PrepareConsoleLogger&);
	PrepareConsoleLogger& operator = (const PrepareConsoleLogger&);

	const std::string			m_name;
	Poco::AutoPtr<Poco::ConsoleChannel>	m_pConsoleChannel;
	Poco::AutoPtr<Poco::PatternFormatter>	m_pTextFormatter;
	Poco::AutoPtr<Poco::FormattingChannel>	m_pFCConsole;
};

#endif	// PREPARE_CONSOLE_LOGGER
