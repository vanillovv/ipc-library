#ifndef IPC_LIBRARY_LIBRARY_H
#define IPC_LIBRARY_LIBRARY_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint       JNICALL Java_ru_vanilla_ipc_Native_create(JNIEnv*, jclass, jstring);
JNIEXPORT void       JNICALL Java_ru_vanilla_ipc_Native_write(JNIEnv*, jclass, jint, jbyteArray);
JNIEXPORT jbyteArray JNICALL Java_ru_vanilla_ipc_Native_read(JNIEnv*, jclass, jint, jint, jint);
JNIEXPORT void       JNICALL Java_ru_vanilla_ipc_Native_close(JNIEnv*, jclass, jint);

#ifdef __cplusplus
}
#endif

#endif