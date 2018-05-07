//
// Created by dfzhang on 2018/4/18.
//

#include "Comm.h"
#include "HookLogic.h"


extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    LOG("JNI_OnLoad...");

    do{
        if(startHook()){
            LOG("startHook Finish Success");
        }else{
            LOG("startHook Failed");
        }

    }while(false);

    return JNI_VERSION_1_2;
}
