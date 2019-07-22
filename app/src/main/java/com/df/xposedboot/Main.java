package com.df.xposedboot;

import android.app.Application;
import android.content.Context;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedBridge;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

public class Main implements IXposedHookLoadPackage{

    //!!!!!!!!!!!注意这里是必须要修改的
    private final String XposedModule = "com.df.xposedboot";

    //!!!!!!!!!!注意这里是必须要修改的
    private final String packageName = "xxx";

    private final boolean isNativeHookEnable = false;

    private void log(String logTxt){
        XposedBridge.log("[XposedBooter]" + logTxt);
    }

    private ClassLoader appClassLoader = null;

    private boolean init(){
        //load hookhelper
        return loadNativeHook();
    }

    private boolean loadNativeHook(){
        if(isNativeHookEnable){
            String libPath = "/data/data/" + XposedModule + "/lib/libHookHelper.so";
            System.load(libPath);
        }

        return true;
    }

    @Override
    public void handleLoadPackage(final XC_LoadPackage.LoadPackageParam lpparam) throws Throwable{

        if(lpparam.packageName.equals(packageName)){
            log("Start Hook..." + packageName);

            //1. normal init here
            init();

            XposedHelpers.findAndHookMethod(Application.class, "attach", Context.class, new XC_MethodHook() {
                @Override
                protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                    appClassLoader = ((Context)param.args[0]).getClassLoader();

                    startJavaHook(lpparam, appClassLoader);
                }
            });
        }
    }

    // write JavaHook here
    private void startJavaHook(XC_LoadPackage.LoadPackageParam lpparam, ClassLoader clsLoader) throws Throwable{

    }
}
