#pragma once

#include "hbpch.h"

#define HB_LOG_ERROR(...) \
std::printf("[Error] [%s] ", __FUNCTION__); \
HoneyBadger::Logger::Log(HoneyBadger::LogVerbosity::Error, __VA_ARGS__);

#define HB_LOG_WARNING(...) \
std::printf("[Warning] [%s] ", __FUNCTION__); \
HoneyBadger::Logger::Log(HoneyBadger::LogVerbosity::Warning, __VA_ARGS__);

#define HB_LOG_MESSAGE(...) \
std::printf("[Message] [%s] ", __FUNCTION__); \
HoneyBadger::Logger::Log(HoneyBadger::LogVerbosity::Message, __VA_ARGS__);

namespace HoneyBadger
{
    enum LogVerbosity
    {
        Error = 1,
        Warning = 2,
        Message = 3,
    };

    class Logger
    {
    public:
        /* log if input log level is equal or smaller to log level set */
        template <typename... Args>
        static void Log(LogVerbosity inLogLevel, Args ... args)
        {
            if (logToFile)
            {
                static bool bInitialized = false;
                if (!bInitialized)
                {
                    std::ofstream clearFile("log/log.txt");
                    bInitialized = true;
                }
            }

            if (inLogLevel <= logLevel)
            {
                char buffer[100];
                sprintf_s(buffer, args ...);
                std::cout << buffer << std::endl;

                if (logToFile)
                {
                    std::ofstream ofile("log/log.txt", std::ios::app);
                    ofile << buffer << '\n';
                    ofile.close();
                }

                if (loggedLineBufferCurrCount >= loggedLineBufferMaxCount)
                {
                    for (int i = 0; i < loggedLineBufferMaxCount - 1; i++)
                    {
                        logLinesVerbosity[i] = logLinesVerbosity[i + 1];
                        logLines[i] = logLines[i + 1];
                    }

                    logLinesVerbosity[loggedLineBufferMaxCount - 1] = inLogLevel;
                    logLines[loggedLineBufferMaxCount - 1] = buffer;
                }
                else
                {
                    logLinesVerbosity[loggedLineBufferCurrCount] = inLogLevel;
                    logLines[loggedLineBufferCurrCount] = buffer;
                    loggedLineBufferCurrCount++;
                }
            }
        }

        static void SetLogLevel(uint16_t inLogLevel)
        {
            logLevel = inLogLevel;
        }

        static uint16_t logLevel;
        static uint16_t logError;
        static uint16_t logWarning;
        static uint16_t logMessage;
        static bool logToFile;

        static constexpr uint16_t loggedLineBufferMaxCount = 16;
        static std::string logLines[loggedLineBufferMaxCount];
        static LogVerbosity logLinesVerbosity[loggedLineBufferMaxCount];
        static uint16_t loggedLineBufferCurrCount;
    };
}