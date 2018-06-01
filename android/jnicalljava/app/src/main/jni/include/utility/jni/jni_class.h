//
// Created by Administrator on 2016/10/30.
//

#ifndef JNICALLJAVA_JNI_CLASS_H
#define JNICALLJAVA_JNI_CLASS_H

#include <jni.h>

#include "jni_exception.h"
#include "jni_log.h"


namespace jni {


/**
 * Class encapsulates a 'jclass' JNI object.
 * Its only purpose is to provide a variety of constructors of the form
 * Class(JNIEnv *, ProtoClass), where ProtoClass can be 'jclass',
 * 'jobject', or 'const char *' (anything from which a 'jclass' can
 * be constructed.
 * Class also has a casting operator to 'jclass' type, so that a call
 * Class(env, arg) can be used in any place where 'jclass' is required.
 */
    class Class {

    protected:
        /**
         * Class handle
         */
        jclass _clazz;

    public:
        /**
         * Default empty constructor
         */
        Class() : _clazz(NULL) { }

        /**
         * Construct a Class from full java class name like
         * "java/lang/String".
         */
        Class(JNIEnv *env, const char *name) : _clazz(env->FindClass(name)) {
            if (_clazz != NULL) {
                LOGD("Class(): found class '%s'", name);
            } else {
                LOGE("Class(): couldn't find class '%s'", name);
            }
        }

        /**
         * Construct a Class from a JNI jobject.
         */
        Class(JNIEnv *env, jobject obj) : _clazz(env->GetObjectClass(obj)) {
            if (_clazz != NULL) {
                LOGD("Class(): found class from jobject");
            } else {
                LOGE("Class(): couldn't find class from jobject");
            }
        }

    protected:
        /**
         * Check if empty and throw.
         */
        void throwIfEmpty() const {
            if(IsEmpty()) {
                throw Exception("Using empty or invalid Class. Check logcat for details...");
            }
        }

    public:

        /**
         * Construct Class from a JNI jclass.
         */
        Class(JNIEnv *env, jclass clazz) : _clazz(clazz) { }
        Class(jclass clazz) : _clazz(clazz) { }

        /**
         * Casting operators to JNI jclass
         */
        operator jclass() { throwIfEmpty(); return _clazz; }
        operator const jclass() const { throwIfEmpty(); return _clazz; }

        /**
         * Checks if this class is empty
         */
        bool IsEmpty() const { return _clazz == NULL; }
    };


} //namespace jni

#endif //JNICALLJAVA_JNI_CLASS_H
