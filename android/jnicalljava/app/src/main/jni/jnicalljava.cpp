//
// Created by Administrator on 2016/10/30.
//
#include <jnicalljava.h>

JNIEXPORT jint JNICALL Java_com_example_caizb_jnicalljava_jnicall_startcalljava
        (JNIEnv *env, jobject clazz){

    return 0;

}


#ifdef __cplusplus
extern "C" {
#endif


/*
 * Internal constants
 **************************************************/

static const char *javaJniCallClassName = "com/example/caizb/jnicalljava/jnicall";

static const char *javaJniCall_jnicallback_returnvoid_MethodName = "jnicallback";
static const char *javaJniCall_jnicallback_returnvoid_Signature = "(Ljava/lang/String;I)Z";

static const char *javaJniCall_jnicallback_returnint_MethodName = "jnicallback";
static const char *javaJniCall_jnicallback_returnint_Signature = "(Ljava/lang/String;I)I";

static const char *javaJniCall_jnicallback_returnString_MethodName = "jnicallback";
static const char *javaJniCall_jnicallback_returnString_Signature = "(Ljava/lang/String;I)(Ljava/lang/String;)";

/*
 * Exported variables
 **************************************************/

//TODO: Remove when all these when passed to respective classes
jclass javaJniCallClass = NULL;
jmethodID jnicallback_returnvoid_ID;
jmethodID jnicallback_returnint_ID;
jmethodID jnicallback_returnString_ID;


/*
 * Exported functions
 **************************************************/

/**
 * Helper function to get the __nativePtr from the Java object
 * and translate it to a smart pointer on result.
 */
std::shared_ptr <void> getNativePtr(JNIEnv *env, jobject thiz) {
    // Get the native pointer id
    jlong id = jni::Field<jlong>(env, thiz, "__nativePtr");

    // Get the smart pointer
    std::shared_ptr <void> res(jni::Pointer(id).getPtr());

    // Return result
    return res;
}

/**
 * Helper function to create a jstring from a native string.
 * Optionally it may free the native string if the freeNative argument
 * is true.
 */
jstring toJstring(JNIEnv *env, const char *str, bool freeNative = false) {
    if (str == NULL) {
        return NULL;
    }

    jstring jstr = env->NewStringUTF(str);
    if (freeNative) {
        free((void *) str);
    }

    return jstr;
}


void javaJniCall_callback_void(JNIEnv *env, jstring str, jint type) {
    env->CallVoidMethodV(javaJniCallClass, jnicallback_returnvoid_ID, str, type);
}

jint javaJniCall_callback_int(JNIEnv *env, jstring str, jint type) {
    return env->CallIntMethodV(javaJniCallClass, jnicallback_returnint_ID, str, type);
}

jstring javaJniCall_callback_String(JNIEnv *env, jstring str, jint type) {
    return env->CallObjectMethodV(javaJniCallClass, jnicallback_returnString_ID, str, type);
}

/*
 * Internal functions
 **************************************************/

/**
 * Initialize the cached java elements for Container class
 */
static jint onLoad_cacheJavaElements_JniCall(JNIEnv * env) {
    // Cache jnicall class
    INIT_CLASS_RETVAL(javaJniCallClass, javaJniCallClassName, ONLOAD_ERROR);
    // Cache JniCall class methods
    INIT_METHOD_ID_RETVAL(jnicallback_returnvoid_ID, javaJniCallClass, javaJniCallClassName,
                          javaJniCall_jnicallback_returnvoid_MethodName,
                          javaJniCall_jnicallback_returnvoid_Signature, ONLOAD_ERROR);
    INIT_METHOD_ID_RETVAL(jnicallback_returnint_ID, javaJniCallClass, javaJniCallClassName,
                          javaJniCall_jnicallback_returnint_MethodName,
                          javaJniCall_jnicallback_returnint_Signature, ONLOAD_ERROR);
    INIT_METHOD_ID_RETVAL(jnicallback_returnString_ID, javaJniCallClass, javaJniCallClassName,
                          javaJniCall_jnicallback_returnString_MethodName,
                          javaJniCall_jnicallback_returnString_Signature, ONLOAD_ERROR);
    return JNI_VERSION;
}




/*
 * JNI functions
 **************************************************/

/**
 * JNI OnLoad function, called when the library is loaded.
 */
JNIEXPORT jint JNI_OnLoad(JavaVM * vm, void *reserved)
{
    JNIEnv *env;
    if(vm->GetEnv(reinterpret_cast <void **>(&env), JNI_VERSION) != JNI_OK){
        LOGE("JNI_OnLoad(): failed to get environment. VM doesn't support JNI version 1.6");
        return ONLOAD_ERROR;
    }
    if( onLoad_cacheJavaElements_JniCall(vm) ){
        LOGE("JNI_OnLoad(): failed to cache epub3 java elements");
        return ONLOAD_ERROR;
    }
    return JNI_VERSION;
}

/**
 * JNI OnUnload function, called when the library is unloaded.
 */
JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    //TODO: Fill when needed
}

#ifdef __cplusplus
}
#endif

