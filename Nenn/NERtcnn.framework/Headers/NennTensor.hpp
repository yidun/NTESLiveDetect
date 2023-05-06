
#ifndef NennTensor_hpp
#define NennTensor_hpp

#include <functional>
#include <map>
#include <string>
#include <memory>
#include "NERtcnn/NennConfig.h"

namespace NENN {


class NENN_PUBLIC NennTensor{

public:
    NennTensor();

    NennTensor(int width, int height, int channel, int batch);

    NennTensor(void* pTensor, NennConfig* config, NENNTensorType tensorType);

    ~NennTensor();

    int width(){return mWidth;};

    int height(){return mHeight;}

    int channel(){return mChannel;}

    int batch(){return mBatch;}

    int elementSize(); //{return mElementSize;}

    void setTextureId(uint64_t textureId);

    uint64_t getTextureId();

    template <typename T>
    T* getDataPtr(){
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
    NENNTensorDataType mTensorDataType = NENNTensorDataType::NENN_TENSOR_DATA_CPU;
};
}
#endif /* NennTensor_hpp */
