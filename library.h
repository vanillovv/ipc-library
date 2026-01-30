#ifndef IPC_LIBRARY_LIBRARY_H
#define IPC_LIBRARY_LIBRARY_H

#include <jni.h>

JNIEXPORT jint       JNICALL Java_ru_vanilla_ipc_Native_create(JNIEnv*, jclass, jstring name);
JNIEXPORT void       JNICALL Java_ru_vanilla_ipc_Native_write(JNIEnv*, jclass, jint index, jbyteArray);
JNIEXPORT jbyteArray JNICALL Java_ru_vanilla_ipc_Native_read(JNIEnv*, jclass, jint index, jint size, jint offset);
JNIEXPORT void       JNICALL Java_ru_vanilla_ipc_Native_close(JNIEnv*, jclass, jint index);

#endif // IPC_LIBRARY_LIBRARY_H