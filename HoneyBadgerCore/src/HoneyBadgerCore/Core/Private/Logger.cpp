#include "hbpch.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"

namespace HoneyBadger
{
    uint16_t Logger::logError = 1;
    uint16_t Logger::logWarning = 2;
    uint16_t Logger::logMessage = 3;

    std::string Logger::logLines[loggedLineBufferMaxCount] = {};
    LogVerbosity Logger::logLinesVerbosity[loggedLineBufferMaxCount] = {};
    uint16_t Logger::loggedLineBufferCurrCount = 0;
    
#ifdef HB_DEBUG
    uint16_t Logger::logLevel = 0;
    bool Logger::logToFile = true;
#else
    uint16_t Logger::logLevel = 3;
    bool Logger::logToFile = false;
#endif
}