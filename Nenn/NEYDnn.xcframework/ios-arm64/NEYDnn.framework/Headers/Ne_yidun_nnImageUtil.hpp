
#ifndef Ne_yidun_nnImageUtil_hpp
#define Ne_yidun_nnImageUtil_hpp

#include <functional>
#include <map>
#include <string>
#include <memory>
#include <Ne_yidun_nnConfig.h>
#include <Ne_yidun_nnTensor.hpp>

namespace NENN {

enum ErrCode {
    NONE = 0,
    SIZE_ERROR = 1,
    NULL_PTR = 2,

};

enum DataType {
    int8 = 0,
    fp32 = 1,
};

enum PixelFormat {
    RGBA = 0,
    RGB,
    BGR,
    GRAY,
    BGRA,
};

enum InputeDataType {
    IMAGE_RAW_DATA = 0,
    IMAGE_OPENGL_DATA = 1,
};

enum ScaleFilter { NEAREST = 0, BILINEAR = 1, BICUBIC = 2 };

enum Wrap { CLAMP_TO_EDGE = 0, ZERO = 1, REPEAT = 2 };

extern "C" {
void NENN_PUBLIC Ne_yidun_nn_ModelInput(unsigned char* input, float* output,
                                        int width, int height, int in_channel,
                                        int out_channel);

void NENN_PUBLIC Ne_yidun_nn_ModelOutput(float* input, unsigned char* output,
                                         int width, int height, int channel);
}

class NENN_PUBLIC Ne_yidun_nnImageUtil {
   public:
    struct ImageConfig {
        ScaleFilter filterType = NEAREST;
        PixelFormat sourceFormat = RGBA;
        PixelFormat destFormat = RGBA;
        float mean[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        float normal[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        /** edge wrapper */
        Wrap wrap = CLAMP_TO_EDGE;
    };

   public:
    static Ne_yidun_nnImageUtil* create(const ImageConfig imageConfig);

    static Ne_yidun_nnImageUtil* create(const PixelFormat sourceFormat,
                                        const PixelFormat destFormat,
                                        ImageConfig imageConfig);

    void convert(const uint8_t* source, int iw, int ih, int stride, void* dest,
                 int ow, int oh, int outputStride, DataType datatype);

    void convert(const uint8_t* source, int iw, int ih, int ow, int oh,
                 float rotate, int stride, Ne_yidun_nnTensor* dest,
                 InputeDataType mInputDataType);

    void alphaFuse(uint8_t* srcImg1, uint8_t* srcImg2, float* alpha,
                   uint8_t* dstImg, int width, int height, int channel);

    ~Ne_yidun_nnImageUtil();

   private:
    Ne_yidun_nnImageUtil(const PixelFormat sourceFormat,
                         const PixelFormat destFormat, ImageConfig config);

    Ne_yidun_nnImageUtil(const ImageConfig imageConfig);

    std::shared_ptr<void> mImageHandle = nullptr;
    ImageConfig mImageConfig;

    void gpuImageProcess(const uint8_t* input, int width, int height,
                         Ne_yidun_nnTensor* destTensor, int in_channel);
};
}  // namespace NENN
#endif /* Ne_yidun_nnImageUtil_hpp */
