//
// Created by Administrator on 2016/10/30.
//

#ifndef JNICALLJAVA_HELPERS_H
#define JNICALLJAVA_HELPERS_H

#include <jni.h>

#include "jni/jni_log.h"

/*
 * Helpers for Java elements initialization
 */

#define INIT_CLASS(class, class_name) { \
	jclass localRefCls = env->FindClass(class_name); \
	if(localRefCls != NULL) {  \
		class = (jclass) env->NewGlobalRef (localRefCls);  \
		env->DeleteLocalRef (localRefCls);  \
		LOGD("INIT_CLASS(): class '%s' found", class_name); \
	} else { \
		class = NULL; \
		LOGE("INIT_CLASS(): class '%s' not found", class_name); \
	} \
}

#define INIT_CLASS_RET(class, class_name) { \
	jclass localRefCls = env->FindClass(class_name); \
	if(localRefCls != NULL) {  \
		class = (jclass) env->NewGlobalRef (localRefCls);  \
		env->DeleteLocalRef (localRefCls);  \
		LOGD("INIT_CLASS(): class '%s' found", class_name); \
	} else { \
		class = NULL; \
		LOGE("INIT_CLASS(): class '%s' not found", class_name); \
		return; \
	} \
}

#define INIT_CLASS_RETVAL(class, class_name, ret) { \
	jclass localRefCls = env->FindClass(class_name); \
	if(localRefCls != NULL) {  \
		class = (jclass) env->NewGlobalRef (localRefCls);  \
		env->DeleteLocalRef (localRefCls);  \
		LOGD("INIT_CLASS(): class '%s' found", class_name); \
	} else { \
		class = NULL; \
		LOGE("INIT_CLASS(): class '%s' not found", class_name); \
		return ret; \
	} \
}

#define INIT_METHOD_ID(mtd_id, class, class_name, mtd_name, mtd_sig) { \
	mtd_id = env->GetMethodID(class, mtd_name, mtd_sig); \
	if(mtd_id != NULL) { \
		LOGD("INIT_METHOD_ID(): method '%s' found in class '%s'", mtd_name, class_name); \
	} else { \
		LOGE("INIT_METHOD_ID(): method '%s' not found in class '%s'", mtd_name, class_name); \
	} \
}

#define INIT_METHOD_ID_RET(mtd_id, class, class_name, mtd_name, mtd_sig) { \
	mtd_id = env->GetMethodID(class, mtd_name, mtd_sig); \
	if(mtd_id != NULL) { \
		LOGD("INIT_METHOD_ID(): method '%s' found in class '%s'", mtd_name, class_name); \
	} else { \
		LOGE("INIT_METHOD_ID(): method '%s' not found in class '%s'", mtd_name, class_name); \
		return; \
	} \
}

#define INIT_METHOD_ID_RETVAL(mtd_id, class, class_name, mtd_name, mtd_sig, ret) { \
	mtd_id = env->GetMethodID(class, mtd_name, mtd_sig); \
	if(mtd_id != NULL) { \
		LOGD("INIT_METHOD_ID(): method '%s' found in class '%s'", mtd_name, class_name); \
	} else { \
		LOGE("INIT_METHOD_ID(): method '%s' not found in class '%s'", mtd_name, class_name); \
		return ret; \
	} \
}

#define INIT_STATIC_METHOD_ID(mtd_id, class, class_name, mtd_name, mtd_sig) { \
	mtd_id = env->GetStaticMethodID(class, mtd_name, mtd_sig); \
	if(mtd_id != NULL) { \
		LOGD("INIT_STATIC_METHOD_ID(): static method '%s' found in class '%s'", mtd_name, class_name); \
	} else { \
		LOGE("INIT_STATIC_METHOD_ID(): static method '%s' not found in class '%s'", mtd_name, class_name); \
	} \
}

#define INIT_STATIC_METHOD_ID_RET(mtd_id, class, class_name, mtd_name, mtd_sig) { \
	mtd_id = env->GetStaticMethodID(class, mtd_name, mtd_sig); \
	if(mtd_id != NULL) { \
		LOGD("INIT_STATIC_METHOD_ID(): static method '%s' found in class '%s'", mtd_name, class_name); \
	} else { \
		LOGE("INIT_STATIC_METHOD_ID(): static method '%s' not found in class '%s'", mtd_name, class_name); \
		return; \
	} \
}

#define INIT_STATIC_METHOD_ID_RETVAL(mtd_id, class, class_name, mtd_name, mtd_sig, ret) { \
	mtd_id = env->GetStaticMethodID(class, mtd_name, mtd_sig); \
	if(mtd_id != NULL) { \
		LOGD("INIT_STATIC_METHOD_ID(): static method '%s' found in class '%s'", mtd_name, class_name); \
	} else { \
		LOGE("INIT_STATIC_METHOD_ID(): static method '%s' not found in class '%s'", mtd_name, class_name); \
		return ret; \
	} \
}

#define INIT_FIELD_ID(field_id, class, class_name, field_name, field_type) { \
	field_id = env->GetFieldID(class, field_name, field_type); \
	if(field_id != NULL) { \
		LOGD("INIT_FIELD_ID(): field '%s' found in class '%s'", field_name, class_name); \
	} else { \
		LOGE("INIT_FIELD_ID(): field '%s' not found in class '%s'", field_name, class_name); \
	} \
}

#define INIT_FIELD_ID_RET(field_id, class, class_name, field_name, field_type) { \
	field_id = env->GetFieldID(class, field_name, field_type); \
	if(field_id != NULL) { \
		LOGD("INIT_FIELD_ID(): field '%s' found in class '%s'", field_name, class_name); \
	} else { \
		LOGE("INIT_FIELD_ID(): field '%s' not found in class '%s'", field_name, class_name); \
		return; \
	} \
}

#define INIT_FIELD_ID_RETVAL(field_id, class, class_name, field_name, field_type, ret) { \
	field_id = env->GetFieldID(class, field_name, field_type); \
	if(field_id != NULL) { \
		LOGD("INIT_FIELD_ID(): field '%s' found in class '%s'", field_name, class_name); \
	} else { \
		LOGE("INIT_FIELD_ID(): field '%s' not found in class '%s'", field_name, class_name); \
		return ret; \
	} \
}


/*
 * Helpers for UTF-8 strings
 */

#define GET_UTF8(cstring, jstring) { \
	cstring = (char *) env->GetStringUTFChars(jstring, NULL); \
    if(cstring == NULL) { \
		LOGE("GET_UTF8(): GetStringUTFChars returned null. Could not allocate memory to hold the UTF-8 string"); \
    } \
}

#define GET_UTF8_RET(cstring, jstring) { \
	cstring = (char *) env->GetStringUTFChars(jstring, NULL); \
    if(cstring == NULL) { \
		LOGE("GET_UTF8(): GetStringUTFChars returned null. Could not allocate memory to hold the UTF-8 string"); \
        return; \
    } \
}

#define GET_UTF8_RETVAL(cstring, jstring, ret) { \
	cstring = (char *) env->GetStringUTFChars(jstring, NULL); \
    if(cstring == NULL) { \
		LOGE("GET_UTF8(): GetStringUTFChars returned null. Could not allocate memory to hold the UTF-8 string"); \
        return ret; \
    } \
}

#define RELEASE_UTF8(jstring, cstring) { \
	if(cstring != NULL) { \
		env->ReleaseStringUTFChars(jstring, cstring); \
		cstring = NULL; \
	} else { \
		LOGE("RELEASE_UTF8(): received a NULL string"); \
	} \
}

#define RELEASE_UTF8_RET(jstring, cstring) { \
	if(cstring != NULL) { \
		env->ReleaseStringUTFChars(jstring, cstring); \
		cstring = NULL; \
	} else { \
		LOGE("RELEASE_UTF8(): received a NULL string"); \
		return; \
	} \
}

#define RELEASE_UTF8_RETVAL(jstring, cstring, ret) { \
	if(cstring != NULL) { \
		env->ReleaseStringUTFChars(jstring, cstring); \
		cstring = NULL; \
	} else { \
		LOGE("RELEASE_UTF8(): received a NULL string"); \
		return ret; \
	} \
}

#endif //JNICALLJAVA_HELPERS_H
