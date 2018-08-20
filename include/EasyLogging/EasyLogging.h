#pragma once

#include <log4cplus/loggingmacros.h>  
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <corecrt_io.h>
#include <iostream>


static  log4cplus::Logger& get_logger()
{
	static log4cplus::Logger logger = log4cplus::Logger::getRoot();
	return logger;
}

#define g_Logger get_logger()


static inline bool log_init(const std::string& config_path = "logconfig.cfg")
{
	log4cplus::initialize();

	//默认使用根logger，防止文件不存在
	g_Logger = log4cplus::Logger::getRoot();


	//判断文件是否存在
	if (_access(config_path.c_str(), 0) == -1)
	{
		LOG4CPLUS_FATAL(log4cplus::Logger::getRoot(), LOG4CPLUS_TEXT("log config do not exits..."));
		return false;
	}

	try
	{
		log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_C_STR_TO_TSTRING(config_path));
		g_Logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main_log"));

		LOG4CPLUS_INFO(g_Logger, LOG4CPLUS_TEXT("Log system start!"));
	}
	catch (...)
	{
		LOG4CPLUS_FATAL(log4cplus::Logger::getRoot(), LOG4CPLUS_TEXT("Exception occured..."));
		return false;
	}

	return true;
}

static inline void log_uinit()
{
	LOG4CPLUS_INFO(g_Logger, LOG4CPLUS_TEXT("Log System Stop."));

	log4cplus::Logger::shutdown();
}


/************************************************************************/
/*  Log out  macro                                                                                 */
/************************************************************************/
//#define LOGGER_ROOT          log4cplus::Logger::getRoot()  
#define LOG_ASSERT(cond)     LOG4CPLUS_ASSERT(g_Logger, cond)  
#define LOG_METHOD(logEvent) LOG4CPLUS_TRACE_METHOD(g_Logger, logEvent)  

#define LOG_FATAL(logEvent)  LOG4CPLUS_FATAL(g_Logger, logEvent)  
#define LOG_ERROR(logEvent)  LOG4CPLUS_ERROR(g_Logger, logEvent)  
#define LOG_WARN(logEvent)   LOG4CPLUS_WARN(g_Logger, logEvent)  
#define LOG_INFO(logEvent)   LOG4CPLUS_INFO(g_Logger, logEvent)  
#define LOG_DEBUG(logEvent)  LOG4CPLUS_DEBUG(g_Logger, logEvent)  
#define LOG_TRACE(logEvent)  LOG4CPLUS_TRACE(g_Logger, logEvent)  
							

#if  _MSC_VER > 1400
#define LOG_FATAL_FMT(logFmt, ...) LOG4CPLUS_FATAL_FMT(g_Logger, logFmt, __VA_ARGS__)
#define LOG_ERROR_FMT(logFmt, ...) LOG4CPLUS_ERROR_FMT(g_Logger, logFmt, __VA_ARGS__)
#define LOG_WARN_FMT(logFmt, ...)  LOG4CPLUS_WARN_FMT(g_Logger, logFmt, __VA_ARGS__)
#define LOG_INFO_FMT(logFmt, ...)  LOG4CPLUS_INFO_FMT(g_Logger, logFmt, __VA_ARGS__)
#define LOG_DEBUG_FMT(logFmt, ...) LOG4CPLUS_DEBUG_FMT(g_Logger, logFmt, __VA_ARGS__)
#define LOG_TRACE_FMT(logFmt, ...) LOG4CPLUS_TRACE_FMT(g_Logger, logFmt, __VA_ARGS__)
#endif
	



#define LOG_C_STR_TO_TSTRING(STRING)  LOG4CPLUS_C_STR_TO_TSTRING(STRING)
#define LOG_STRING_TO_TSTRING(STRING) LOG4CPLUS_STRING_TO_TSTRING(STRING)
#define LOG_TSTRING_TO_STRING(STRING) LOG4CPLUS_TSTRING_TO_STRING(STRING)

#define LOG_BUILTIN_EXPECT(exp, c)   LOG4CPLUS_BUILTIN_EXPECT(exp, c)
#define LOGE_LIKELY(cond)             LOG4CPLUS_LIKELY(cond)
#define LOG_UNLIKELY(cond)           LOG4CPLUS_UNLIKELY(cond)

//#define CRUISE_MACRO_FILE()             __FILE__
//#define CRUISE_MACRO_LINE()             __LINE__
#define LOG_MACRO_FUNCTION()         LOG4CPLUS_MACRO_FUNCTION()
#define LOG_CALLER_FILE()            LOG4CPLUS_CALLER_FILE()
#define LOG_CALLER_LINE()            LOG4CPLUS_CALLER_LINE()
#define LOG_CALLER_FUNCTION()        LOG4CPLUS_CALLER_FUNCTION()
