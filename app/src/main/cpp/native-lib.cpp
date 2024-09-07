#include <jni.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Credits https://github.com/h5p9sl
#include "hmac_sha256/hmac_sha256.h"
#define SHA256_HASH_SIZE 32

extern "C" JNIEXPORT jstring JNICALL
Java_me_bhamza_hellosignjni_MainActivity_sign(JNIEnv* env, jobject, jstring input_str) {
    std::stringstream ss_result;
    const char* utf8_input_str = env->GetStringUTFChars(input_str, 0);
    const std::string str_key = "b323-a677-587c-f5c9-5410";  // hardcoded

    // Throw in some Java calls from C++ land.
    jclass cls_localdate  = env->FindClass("java/time/LocalDate");
    jmethodID method_now = env->GetStaticMethodID(cls_localdate, "now", "()Ljava/time/LocalDate;");
    jobject obj_localdate = env->CallStaticObjectMethod(cls_localdate, method_now);
    jmethodID method_toString = env->GetMethodID(cls_localdate, "toString", "()Ljava/lang/String;");
    jstring jstr_current_date = (jstring) env->CallObjectMethod(obj_localdate, method_toString);
    const char* current_date_str = env->GetStringUTFChars(jstr_current_date, 0);

    // YoloMAC courtesy from https://blog.trailofbits.com/2024/08/21/yolo-is-not-a-valid-hash-construction/
    std::string message = "YOLOCRYPTO|" + std::string(utf8_input_str) + "|" + std::string(current_date_str);

    // Allocate memory for the HMAC
    std::vector<uint8_t> out(SHA256_HASH_SIZE);

    // Call hmac-sha256 function
    hmac_sha256(str_key.data(), str_key.size(), message.c_str(), message.length(), out.data(), out.size());

    // Convert `out` to string with std::hex
    for (uint8_t x : out) {
        ss_result << std::hex << std::setfill('0') << std::setw(2) << (int)x;
    }

    return env->NewStringUTF(ss_result.str().c_str());
}