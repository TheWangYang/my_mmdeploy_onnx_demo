
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>  // 包含Windows API头文件


int main() {
    // 加载动态链接库
    // HMODULE hDll = LoadLibrary("");
    HMODULE hDll = LoadLibraryEx("E:\\PyCharmWorkPlace\\my_mmdeploy_onnx_demo\\dll\\objectdetection.dll", NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    
    std::cout << "hDll: " << hDll << std::endl;

    if (hDll == NULL) {
        std::cout << "Failed to load the DLL" << std::endl;
        return 1;
    }

    // 获取动态链接库中的函数指针
    typedef int(*ObjectdetectionFunc)(const char *, const char *, const char *);  // 替换为实际的函数类型
    
    ObjectdetectionFunc do_inference = (ObjectdetectionFunc)GetProcAddress(hDll, "do_inference");

    if (do_inference == NULL) {
        std::cout << "Failed to get the function from DLL" << std::endl;
        return 1;
    }

    // 调用动态链接库中的函数
    int result = do_inference("cpu", "E:/PyCharmWorkPlace/my_mmdeploy_onnx_demo/onnx", "E:/PyCharmWorkPlace/my_mmdeploy_onnx_demo/images/test.jpg");
    
    std::cout << "Result: " << result << std::endl;

    // 卸载动态链接库
    FreeLibrary(hDll);

    return 0;
}


