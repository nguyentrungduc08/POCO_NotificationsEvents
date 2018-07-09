
//----------------------------------------
//	include
//----------------------------------------
#include "ScopedLogMessage.h"

#include <Poco/Logger.h>
#include <Poco/Thread.h>
#include <Poco/Format.h>

//----------------------------------------
//	ScopedLogMessageImpl
//		using RAII idiom
//----------------------------------------

class ScopedLogMessage::ScopedLogMessageImpl {
public: 

    ScopedLogMessageImpl(const std::string& commonMsg,
            const std::string& startMsg,
            const std::string& endMsg) :
    m_endMsg(commonMsg + endMsg) {
        Poco::Logger::get(Poco::Logger::ROOT).information(ThreadIDString() + commonMsg + startMsg);
    }

    ~ScopedLogMessageImpl() {
        Poco::Logger::get(Poco::Logger::ROOT).information(ThreadIDString() + m_endMsg);
    }

    void Message(const std::string& msg) const {
        Poco::Logger::get(Poco::Logger::ROOT).information(ThreadIDString() + msg);
    }
private:
    ScopedLogMessageImpl();
    ScopedLogMessageImpl(const ScopedLogMessageImpl&);
    ScopedLogMessageImpl& operator=(const ScopedLogMessageImpl&);

    int GetThreadID(void) const {
        Poco::Thread* p_thread = Poco::Thread::current();
        return (0 == p_thread) ? 0 : p_thread->id();
    }

    std::string ThreadIDString(void) const {
        return Poco::format("[%d] ", GetThreadID());
    }

    const std::string m_endMsg;
};

//----------------------------------------
//	ScopedLogMessage
//----------------------------------------

ScopedLogMessage::ScopedLogMessage(const std::string& commonMsg,
        const std::string& startMsg,
        const std::string& endMsg) :
m_pImpl(new ScopedLogMessageImpl(commonMsg, startMsg, endMsg)) {
}

ScopedLogMessage::~ScopedLogMessage() {
}

void ScopedLogMessage::Message(const std::string& msg) const {
    m_pImpl->Message(msg);
}
