//
// Created by Administrator on 2016/10/30.
//

#ifndef JNICALLJAVA_JNI_LOG_H
#define JNICALLJAVA_JNI_LOG_H

// Enable logging? 1=true/0=false
#define LOG_ENABLED 1


// If log enabled?
#if LOG_ENABLED == 1

#include <android/log.h>

// Make a string from value
#define STRINGIZE2(x) #x
#define STRINGIZE(x) STRINGIZE2(x)


// Android log tag and macros
#define  LOG_TAG    "libepub3 [" __FILE__ ":" STRINGIZE(__LINE__) "]"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#else

// Make a string from value
#define STRINGIZE2(x) #x
#define STRINGIZE(x) STRINGIZE2(x)
// Dummy tag and macros
#define  LOG_TAG    ""
#define  LOGI(...)  ((void)0)
#define  LOGD(...)  ((void)0)
#define  LOGW(...)  ((void)0)
#define  LOGE(...)  ((void)0)

#endif // If log enabled?

#endif //JNICALLJAVA_JNI_LOG_H
