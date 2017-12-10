#ifndef LIB_LOG_H
#define LIB_LOG_H

#include <stdio.h>
#include <stdarg.h>

/* definition of constant log levels */
#define LOG_LEVEL_FATAL 1
#define LOG_LEVEL_ERROR 2
#define LOG_LEVEL_WARN  3
#define LOG_LEVEL_INFO  4

/* function to log the given message */
static inline void log_message(int level, const char *format, ...){
  va_list args;
  switch (level) {
  case LOG_LEVEL_FATAL:
    fprintf(stdout, "[FATAL] : ");
    break;
  case LOG_LEVEL_ERROR:
    fprintf(stdout, "[ERROR] : ");
    break;
  case LOG_LEVEL_WARN:
    fprintf(stdout, "[WARNING] : ");
    break;
  case LOG_LEVEL_INFO:
    fprintf(stdout, "[INFO] : ");
    break;
  default:
    break;
  }
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
}

/*
 * Define the visibility of the log
 */

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

#if LOG_LEVEL >= LOG_LEVEL_FATAL
#define LOG_FATAL(format, ...) log_message(LOG_LEVEL_FATAL, format, ##__VA_ARGS__)
#else
#define LOG_FATAL(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_ERROR(format, ...) log_message(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
#define LOG_WARN(format, ...) log_message(LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#else
#define LOG_WARN(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOG_INFO(format, ...) log_message(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#endif
