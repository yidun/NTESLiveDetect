
#ifndef NennConfig_h
#define NennConfig_h

#include <assert.h>
#include <stdio.h>

#ifdef NENN_USE_LOGCAT
#include <android/log.h>
#define NENN_ERROR(format, ...) \
    __android_log_print(ANDROID_LOG_ERROR, "NENNJNI", format, ##__VA_ARGS__)
#define NENN_PRINT(format, ...) \
    __android_log_print(ANDROID_LOG_INFO, "NENNJNI", format, ##__VA_ARGS__)
#else
#define NENN_PRINT(format, ...) printf(format, ##__VA_ARGS__)
#define NENN_ERROR(format, ...) printf(format, ##__VA_ARGS__)
#endif

#define NENN_ASSERT(x)                              \
    {                                               \
        int res = (x);                              \
        if (!res) {                                 \
            NENN_ERROR("Error for %d\n", __LINE__); \
        }                                           \
    }

#if defined(_MSC_VER)
#define NENN_PUBLIC __declspec(dllexport)
#else
#define NENN_PUBLIC __attribute__((visibility("default")))
#endif

enum NennErrCode {
    NENN_SUCCESS = 0,
    NENN_CREATE_ERROR = 1,
};

typedef enum {
    NENN_FORWARD_CPU = 0,
    NENN_FORWARD_METAL = 1,
    NENN_FORWARD_OPENCL = 3,
} NENNForwardType;

typedef enum {
    NENN_TYPE_FP32 = 0,
    NENN_TYPE_INT16 = 1,
    NENN_TYPE_FP16 = 2,
} NENNDataType;

typedef enum {
    NENN_TENSOR_DATA_CPU = 0,
    NENN_TENSOR_DATA_GPU = 1,
} NENNTensorDataType;

typedef enum {
    NENN_DIM_FORMAT_NHWC = 0,
    NENN_DIM_FORMAT_NCHW = 1
} NENNDimFormatType;

typedef enum { NENN_INPUT_TENSOR = 0, NENN_OUTPUT_TENSOR = 1 } NENNTensorType;

struct NennConfig {
    int numThread = 4;
    NENNForwardType forwardType = NENN_FORWARD_CPU;
    NENNDataType dataType = NENN_TYPE_FP32;
    NENNDimFormatType inputFormatType = NENN_DIM_FORMAT_NCHW;
    NENNDimFormatType outputFormatType = NENN_DIM_FORMAT_NCHW;
    NENNTensorDataType inputTensorDataType = NENN_TENSOR_DATA_CPU;
    NENNTensorDataType outputTensorDataType = NENN_TENSOR_DATA_CPU;
    void* mContextHandle = nullptr;
};

#endif /* NennConfig_h */
