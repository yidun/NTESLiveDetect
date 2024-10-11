
#ifndef Ne_yidun_nnTensor_hpp
#define Ne_yidun_nnTensor_hpp

#include <functional>
#include <map>
#include <string>
#include <memory>
#include <Ne_yidun_nnConfig.h>

namespace NENN {

class NENN_PUBLIC Ne_yidun_nnTensor {
   public:
    Ne_yidun_nnTensor();

    Ne_yidun_nnTensor(int width, int height, int channel, int batch);

    Ne_yidun_nnTensor(void* pTensor, NennConfig* config,
                      NENNTensorType tensorType);

    ~Ne_yidun_nnTensor();

    int width() { return mWidth; };

    int height() { return mHeight; }

    int channel() { return mChannel; }

    int batch() { return mBatch; }

    int elementSize();  //{return mElementSize;}

    void setTextureId(uint64_t textureId);

    uint64_t getTextureId();

    template <typename T>
    T* getDataPtr() {
        uint8_t* data = setInternalData();
        return (T*)data;
    };

    void inputConvert();

    void outputConvert();

    void* getInternalTensor();

   private:
    uint8_t* setInternalData();
    void convert_short(void* src, void* dst);
    void convert_float(void* src, void* dst);

   private:
    int mWidth;
    int mHeight;
    int mChannel;
    int mBatch;
    uint64_t* mTextureId;
    int mElementSize;
    int mInternalFormat;
    void* mInternalTensor;
    std::shared_ptr<void> mGpuTensor;
    std::shared_ptr<void> mCpuTensor;
    NennConfig* mConfig;
    void* mBackend = nullptr;
    NENNTensorDataType mTensorDataType =
        NENNTensorDataType::NENN_TENSOR_DATA_CPU;
};
}  // namespace NENN
#endif /* Ne_yidun_nnTensor_hpp */
