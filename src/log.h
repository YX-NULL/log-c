/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#define LOG_VERSION "0.1.0"

typedef struct {
  va_list ap;
  const char *fmt;
  const char *file;
  struct tm *time;
  void *udata;
  int line;
  int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

const char* log_level_string(int level);
void log_set_lock(log_LockFn fn, void *udata);/*多线程 加锁管理注册回调函数来进行加锁和解锁*/
void log_set_level(int level);/*设置log 等级*/
void log_set_quiet(bool enable);/*停止打印在终端*/
int log_add_callback(log_LogFn fn, void *udata, int level);
int log_add_fp(FILE *fp, int level);/*写入到文件*/

void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif

//test log
/**
#include <stdio.h>
#include "log.h"

int main(int argc ,char* argv[])
{
    FILE* fp = fopen("/tmp/test_log.log" ,"a+");
    if ( fp == NULL){
        printf("fopen failed\n");
    }

    log_set_level(LOG_TRACE);
    log_add_fp(fp , LOG_INFO);

    
    log_trace("HELLO TRACE");
    log_debug("HELLO TRACE");
    log_info("HELLO TRACE");
    log_warn("HELLO TRACE");
    log_error("HELLO TRACE");
    log_fatal("HELLO TRACE");

    log_set_quiet(1);
    log_trace("HELLO quite");
    log_debug("HELLO quite");
    log_info("HELLO quite");
    log_warn("HELLO quite");
    log_error("HELLO quite");
    log_fatal("HELLO quite");

    fclose(fp);
    return 0;
}
*/
