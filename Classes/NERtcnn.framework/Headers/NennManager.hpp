
#ifndef NennManager_hpp
#define NennManager_hpp

#include <functional>
#include <map>
#include <string>
#include <memory>
#include "NERtcnn/NennConfig.h"
#include "NERtcnn/NennTensor.hpp"

namespace NENN {

class NENN_PUBLIC NennManager{

public:
    NennManager();

    ~NennManager();

    int createFromModelFile(const char* file);

    int createFromModelBuffer(const void* buffer, size_t size);

    NennErrCode createContainer(const NennConfig& config);

    bool releaseContainer();

    void resizeTensor(int batch, int channel, int height, int width, const char* name);

    void releaseModel();

    void runNetModel();

    NennTensor* getTensor(const char* name);

    NennTensor* getIntputTensor(const char* name);

    NennTensor* getOutputTensor(const char* name);

private:

    void updateInputAndOutput();

private:
    void* mSessionObject = nullptr;
    void* mInterpreter = nullptr;

    std::map<std::string, std::shared_ptr<NennTensor>> mInputs;
    std::map<std::string, std::shared_ptr<NennTensor>> mOutputs;
    NennConfig* mConfig;
};
}
#endif /* NennManager_hpp */
