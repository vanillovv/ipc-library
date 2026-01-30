#include "windows.h"
#include "library.h"
#include <iostream>
#include <map>
#include <vector>

static std::map<int, HANDLE> pipes;
static int g_index = 0;

JNIEXPORT jint JNICALL Java_com_ferra13671_discordipc_Native_create(JNIEnv* env, jobject, jstring name) {
    const char *cstr = env->GetStringUTFChars(name, NULL);
    env->ReleaseStringUTFChars(name, cstr);

    HANDLE pipe = CreateFile(
        TEXT(cstr),
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    int index = g_index++;

    pipes.insert({index, pipe});

    return index;
}

JNIEXPORT void JNICALL Java_com_ferra13671_discordipc_Native_write(JNIEnv* env, jobject, jint index, jbyteArray bytes) {
    auto it = pipes.find(index);
    if (it == pipes.end()) return;

    HANDLE pipe = it->second;

    jbyte* data = env->GetByteArrayElements(bytes, NULL);
    jsize length = env->GetArrayLength(bytes);

    DWORD dword;
    BOOL write = WriteFile(pipe, data, length, &dword, NULL);

    if (!write) return

    env->ReleaseByteArrayElements(bytes, data, 0);
}

JNIEXPORT jbyteArray JNICALL Java_com_ferra13671_discordipc_Native_read(JNIEnv* env, jobject, jint index, jint size, jint offset) {
    auto it = pipes.find(index);

    if (it == pipes.end() || size <= 0) {
        return env->NewByteArray(0);
    }

    HANDLE pipe = it->second;

    std::vector<jbyte> vector(size);

    DWORD dword = 0;
    BOOL read = ReadFile(pipe,vector.data(), size, &dword, NULL);

    if (!read) return env->NewByteArray((0));

    if (dword == 0 || offset >= dword) {
        return env->NewByteArray(0);
    }

    jint g_size = dword - offset;
    jbyteArray result = env->NewByteArray(g_size);

    env->SetByteArrayRegion(result, 0, g_size, vector.data() + offset);

    return result;
}

JNIEXPORT void JNICALL Java_com_ferra13671_discordipc_Native_close(JNIEnv*, jobject, jint index){
    auto it = pipes.find(index);
    if (it == pipes.end()) return;

    CloseHandle(it->second);
    pipes.erase(it);
}