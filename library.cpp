#include "windows.h"
#include "library.h"
#include <iostream>
#include <vector>
#include <map>

static std::map<int, HANDLE> pipes;
static int g_index = 0;

JNIEXPORT jint JNICALL Java_ru_vanilla_ipc_Native_create(JNIEnv* env, jclass, jstring name) {
    if (!name) return -1;

    const char *cstr = env->GetStringUTFChars(name, NULL);

    HANDLE pipe = CreateFile(
        cstr,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    env->ReleaseStringUTFChars(name, cstr);

    if (pipe == INVALID_HANDLE_VALUE) return -1;

    int index = g_index++;

    pipes.insert({index, pipe});

    return index;
}

JNIEXPORT void JNICALL Java_ru_vanilla_ipc_Native_write(JNIEnv* env, jclass, jint index, jbyteArray bytes) {
    auto it = pipes.find(index);
    if (it == pipes.end()) return;

    HANDLE pipe = it->second;

    jbyte* data = env->GetByteArrayElements(bytes, NULL);
    jsize length = env->GetArrayLength(bytes);

    DWORD dword;
    BOOL write = WriteFile(pipe, data, length, &dword, NULL);

    env->ReleaseByteArrayElements(bytes, data, 0);
}

JNIEXPORT jbyteArray JNICALL Java_ru_vanilla_ipc_Native_read(JNIEnv* env, jclass, jint index, jint size, jint offset) {
    auto it = pipes.find(index);

    if (it == pipes.end() || size <= 0) {
        return env->NewByteArray(0);
    }

    HANDLE pipe = it->second;

    std::vector<jbyte> vector(size);

    DWORD dword = 0;
    BOOL read = ReadFile(pipe, vector.data(), size, &dword, NULL);

    if (!read) return env->NewByteArray((0));

    if (dword == 0 || offset >= dword) {
        return env->NewByteArray(0);
    }

    jint g_size = dword - offset;
    jbyteArray byteArray = env->NewByteArray(g_size);

    env->SetByteArrayRegion(byteArray, 0, g_size, vector.data() + offset);

    return byteArray;
}

JNIEXPORT void JNICALL Java_ru_vanilla_ipc_Native_close(JNIEnv*, jclass, jint index) {
    auto it = pipes.find(index);
    if (it == pipes.end()) return;

    CloseHandle(it->second);
    pipes.erase(it);
}