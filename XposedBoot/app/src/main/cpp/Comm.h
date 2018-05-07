//
// Created by dfzhang on 2018/4/18.
//

#ifndef XPOSEDRESEARCH_HOOKCOMM_H_H
#define XPOSEDRESEARCH_HOOKCOMM_H_H

#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include <string.h>
#include <dlfcn.h>
#include <vector>
#include <string>

#define TAG "[XposedResearch]"
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)


typedef const void *MSImageRef;
typedef MSImageRef (*FN_MSGetImageByName)(const char *file);
typedef void *(*FN_MSFindSymbol)(MSImageRef image, const char *name);
typedef void (*FN_MSHookFunction)(void *symbol, void *replace, void **result);


#endif //XPOSEDRESEARCH_HOOKCOMM_H_H
