
//----------------------------------------
//	include
//----------------------------------------
#include "PrepareConsoleLogger.h"

//----------------------------------------
//	PrepareConsoleLogger
//----------------------------------------

PrepareConsoleLogger::PrepareConsoleLogger(const std::string& name, int level) :
m_name(name)
, m_pConsoleChannel(new Poco::ConsoleChannel)
, m_pTextFormatter(new Poco::PatternFormatter("%t"))
, m_pFCConsole(new Poco::FormattingChannel(m_pTextFormatter)) {
    m_pFCConsole->setChannel(m_pConsoleChannel);
    m_pFCConsole->open();

    Poco::Logger::create(m_name, m_pFCConsole, level);
}

PrepareConsoleLogger::~PrepareConsoleLogger() {
    Poco::Logger::destroy(m_name);

    m_pFCConsole->close();
}
