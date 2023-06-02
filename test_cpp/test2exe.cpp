
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>  // 包含Windows API头文件


//E:\\PyCharmWorkPlace\\my_mmdeploy_onnx_demo\\dll\\onnx_inference.dll
//batch_inference
//cpu
//E:\\PyCharmWorkPlace\\my_mmdeploy_onnx_demo\\onnx
//E:\\PyCharmWorkPlace\\my_mmdeploy_onnx_demo\\images
//E:\\PyCharmWorkPlace\\my_mmdeploy_onnx_demo\\results

//cmd run below
//test2exe 

int main(int argc, char* argv[]) {
    // //获得命令行参数
    // //得到动态链接库的路径
    // const char* arg1 = argv[1];
    // //得到调用函数的名称
    // const char* arg2 = argv[2];
    // //设置推理backend为cpu
    // const char* arg3 = argv[3];
    // //设置推理文件所在的onnx文件夹路径
    // const char* arg4 = argv[4];
    // //设置测试图片文件夹路径
    // const char* arg5 = argv[5];
    // //设置保存推理结果路径
    // const char* arg6 = argv[6];
    // std::cout << "arg1: " << arg1 << std::endl;
    
    HMODULE hDll = LoadLibraryEx("onnx_inference.dll", NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    
    std::cout << "hDll: " << hDll << std::endl;

    if (hDll == NULL) {
        std::cout << "Failed to load the DLL" << std::endl;
        return 1;
    }

    // 获取动态链接库中的函数指针
    typedef int(*ObjectdetectionFunc)(const char *, const char *, const char *, const char *);  // 替换为实际的函数类型
    
    ObjectdetectionFunc batch_inference = (ObjectdetectionFunc)GetProcAddress(hDll, "batch_inference");

    if (batch_inference == NULL) {
        std::cout << "Failed to get the function from DLL" << std::endl;
        return 1;
    }

    // 调用动态链接库中的函数
    int result = batch_inference("cpu", "onnx", "images", "results");
    
    std::cout << "Result: " << result << std::endl;

    // 卸载动态链接库
    FreeLibrary(hDll);

    return 0;
}


