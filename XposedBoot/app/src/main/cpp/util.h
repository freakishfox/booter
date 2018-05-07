//
// Created by dfzhang on 2018/4/19.
//

#ifndef XPOSEDRESEARCH_UTIL_H_H
#define XPOSEDRESEARCH_UTIL_H_H

#include <sys/types.h>
#include "Comm.h"

// 在指定进程中获取模块加载地址
unsigned long get_module_base(pid_t pid, const char *module_name);

//字符串分割
std::vector<std::string> split_string(char *src, const char *delmiter);

//删除重复的空格
std::string remove_repeated_space(std::string src);

//把char的内容以十六进制打印出来
std::string bytes_to_hex(char *src, size_t size);

#endif //XPOSEDRESEARCH_UTIL_H_H
