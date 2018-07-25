//
// Created by dfzhang on 2018/4/18.
//

#include "Comm.h"
#include "HookLogic.h"
#include "util.h"
#include <sys/types.h>
#include <unistd.h>
#import "Hooker.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef void* (*FN_dlopen)(const char* filename, int flags);
FN_dlopen prev_dlopen = NULL;
void* fake_dlopen(const char* filename, int flags){
    void *dl = NULL;
    if(prev_dlopen){
        dl = prev_dlopen(filename, flags);
    }

    return dl;
}

static bool hook_linker_dlopen(){

    void *dlopen_ = (void *)&dlopen;

    MSHookFunction(dlopen_, (void *)&fake_dlopen, (void **)&prev_dlopen);
    return true;
}

bool startHook(){
    return hook_linker_dlopen();
}

bool stopHook(){

    return true;
}

