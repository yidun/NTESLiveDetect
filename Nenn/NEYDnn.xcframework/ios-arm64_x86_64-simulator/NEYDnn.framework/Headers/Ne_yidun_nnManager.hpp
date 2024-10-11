
#ifndef Ne_yidun_nnManager_hpp
#define Ne_yidun_nnManager_hpp

#include <functional>
#include <map>
#include <string>
#include <memory>
#include <Ne_yidun_nnConfig.h>
#include <Ne_yidun_nnTensor.hpp>

namespace NENN {

class NENN_PUBLIC Ne_yidun_nnManager {
   public:
    Ne_yidun_nnManager();

    ~Ne_yidun_nnManager();

    int createFromModelFile(const char* file);

    int createFromModelBuffer(const void* buffer, size_t size);

    NennErrCode createContainer(const NennConfig& config);

    bool releaseContainer();

    void resizeTensor(int batch, int channel, int height, int width,
                      const char* name);

    void releaseModel();

    void runNetModel();

    Ne_yidun_nnTensor* getTensor(const char* name);

    Ne_yidun_nnTensor* getIntputTensor(const char* name);

    Ne_yidun_nnTensor* getOutputTensor(const char* name);

   private:
    void updateInputAndOutput();

   private:
    void* mSessionObject = nullptr;
    void* mInterpreter = nullptr;

    std::map<std::string, std::shared_ptr<Ne_yidun_nnTensor>> mInputs;
    std::map<std::string, std::shared_ptr<Ne_yidun_nnTensor>> mOutputs;
    NennConfig* mConfig;
};
}  // namespace NENN
#endif /* Ne_yidun_nnManager_hpp */
