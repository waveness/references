//
// Created by Administrator on 2016/10/30.
//

#ifndef JNICALLJAVA_JNI_UTILS_H
#define JNICALLJAVA_JNI_UTILS_H

#include "jni_types.h"


namespace jni {


/*
 * Here we define templates which facilitate using functions
 * Get<PrimitiveType>ArrayRegion and Set<PrimitiveType>ArrayRegion,
 * so that there is no need to explicitly specify the type parameter.
 * The actual type is inferred from the corresponding template parameter.
 */

/*
 * Template utilities for Get/Set<PrimitiveType>ArrayRegion
 */

    template<class NativeType, class ArrayType>
    inline void GetArrayRegion(JNIEnv *env, ArrayType array, jsize start,
                               jsize len, NativeType *buf);
    template<class NativeType, class ArrayType>
    inline void SetArrayRegion(JNIEnv *env, ArrayType array, jsize start,
                               jsize len, NativeType *buf);

/*
 * The implementation of Get/SetArrayRegion functions is given as
 * a macro block, to facilitate their explicit instantiation for
 * all primitive types.
 * Both template functions use the type parameter as an entry into the
 * lookup table, to retrieve NativeType, ArrayType and type signature.
 */

#define ARRAY_REGION_ROUTINES(Type)											 \
inline void GetArrayRegion(JNIEnv *env, ARRAY_TYPE(Type) array, jsize start, \
					jsize len, NATIVE_TYPE(Type) *buf) {					 \
    env->Get##Type##ArrayRegion(array, start, len, buf);					 \
}																			 \
																			 \
inline void SetArrayRegion(JNIEnv *env, ARRAY_TYPE(Type) array, jsize start, \
					jsize len, NATIVE_TYPE(Type) *buf) {					 \
    env->Set##Type##ArrayRegion(array, start, len, buf);					 \
}

/*
 * Explicit instantiation of the above definitions for all primitive types
 */

    INSTANTIATE_FOR_PRIMITIVE_TYPES(ARRAY_REGION_ROUTINES)


} //namespace jni


#endif //JNICALLJAVA_JNI_UTILS_H
