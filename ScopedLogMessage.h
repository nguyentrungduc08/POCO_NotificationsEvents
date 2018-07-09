
#ifndef SCOPED_LOG_MESSAGE_H
#define SCOPED_LOG_MESSAGE_H

//----------------------------------------
//	include
//----------------------------------------
#include <iostream>
#include <string>
#include <memory>

//----------------------------------------
//	ScopedLogMessage
//----------------------------------------
class ScopedLogMessage
{
public:
	ScopedLogMessage(const std::string& commonMsg,
			const std::string& startMsg,
			const std::string& endMsg);
	~ScopedLogMessage();
	void Message(const std::string& msg) const;

private:
	ScopedLogMessage();
	ScopedLogMessage(const ScopedLogMessage&);
	ScopedLogMessage& operator = (const ScopedLogMessage&);

	class ScopedLogMessageImpl;
	std::auto_ptr<ScopedLogMessageImpl>	m_pImpl;
};

#endif	// SCOPED_LOG_MESSAGE_H
