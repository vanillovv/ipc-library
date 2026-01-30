#ifndef IPC_LIBRARY_LIBRARY_H
#define IPC_LIBRARY_LIBRARY_H

#include <jni.h>

JNIEXPORT jint       JNICALL Java_ru_vanilla_ipc_Native_create(JNIEnv*, jobject, jstring name);
JNIEXPORT void       JNICALL Java_ru_vanilla_ipc_Native_write(JNIEnv*, jobject, jint, jbyteArray);
JNIEXPORT jbyteArray JNICALL Java_ru_vanilla_ipc_Native_read(JNIEnv*, jobject, jint, jint, jint);
JNIEXPORT void       JNICALL Java_ru_vanilla_ipc_Native_close(JNIEnv*, jobject, jint);

#endif // IPC_LIBRARY_LIBRARY_H