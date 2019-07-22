package com.df.xposedboot;

import org.mozilla.javascript.Function;
import org.mozilla.javascript.NativeObject;
import org.mozilla.javascript.Scriptable;

import java.util.Map;

/**
 * 封装了rhino这个js引擎，方便调用js
 */
public class JSEngine {
    private static JSEngine s_instance = new JSEngine();
    private org.mozilla.javascript.Context rhino = null;
    private Scriptable scope = null;

    public static JSEngine getInstance(){
        return s_instance;
    }

    public boolean init(String jsContent, int lineCnt) throws Exception{
        rhino = org.mozilla.javascript.Context.enter();
        rhino.setOptimizationLevel(-1);

        try{
            scope = rhino.initStandardObjects();
            rhino.evaluateString(scope, jsContent, "JavaScript", lineCnt, null);
        }catch (Exception e){
            throw e;
        }

        return true;
    }

    /**
     * 调用js函数
     * @param jsScope - js所在的命名空间
     * @param jsFuncName - js函数名
     * @param params - js函数的参数
     * @param retClass - 返回类型
     * @return
     */
    public Object callJSFunction(String jsScope, String jsFuncName, Object []params, Class retClass) throws Exception{
        Object obj = scope.get(jsScope, scope);
        if(null == obj){
            throw new Exception("scope not found=>" + jsScope);
        }

        Map objMap = (Map)obj;
        if(objMap.size() <= 0){
            throw new Exception("scope contains nothing=>" + jsScope);
        }

        String[] funcNames = jsFuncName.split(".");

        Object objFunc = null;
        for(String funcName:funcNames){
            Object objNext = objMap.get(funcName);
            if(objNext instanceof Function){
                objFunc = objNext;
                break;
            }

            objMap = (Map)objNext;
        }

        if(null != objFunc){
            Function jsFunction = (Function)objFunc;
            Object result = jsFunction.call(rhino, scope, scope, params);

            if(result instanceof NativeObject){
                NativeObject nativeResult = (NativeObject)result;
                return nativeResult.getDefaultValue(retClass);
            }
        }

        throw new Exception("no js function called, can not find=>" + jsScope + "." + jsFuncName);
    }
}
