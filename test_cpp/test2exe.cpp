
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
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> b43009505c106cd86a24dc01f786b05eafb4d938
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
<<<<<<< HEAD
=======
=======
    //获得命令行参数
    //得到动态链接库的路径
    const char* arg1 = argv[1];
    //得到调用函数的名称
    const char* arg2 = argv[2];
    //设置推理backend为cpu
    const char* arg3 = argv[3];
    //设置推理文件所在的onnx文件夹路径
    const char* arg4 = argv[4];
    //设置测试图片文件夹路径
    const char* arg5 = argv[5];
    //设置保存推理结果路径
    const char* arg6 = argv[6];
    std::cout << "arg1: " << arg1 << std::endl;
    HMODULE hDll = LoadLibraryEx(arg1, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
>>>>>>> ef9016b3dcf9aa164fd1cf7af351663cc77d8e39
>>>>>>> b43009505c106cd86a24dc01f786b05eafb4d938
    
    std::cout << "hDll: " << hDll << std::endl;

    if (hDll == NULL) {
        std::cout << "Failed to load the DLL" << std::endl;
        return 1;
    }

    // 获取动态链接库中的函数指针
    typedef int(*ObjectdetectionFunc)(const char *, const char *, const char *, const char *);  // 替换为实际的函数类型
    
<<<<<<< HEAD
    ObjectdetectionFunc batch_inference = (ObjectdetectionFunc)GetProcAddress(hDll, "batch_inference");
=======
<<<<<<< HEAD
    ObjectdetectionFunc batch_inference = (ObjectdetectionFunc)GetProcAddress(hDll, "batch_inference");
=======
    ObjectdetectionFunc batch_inference = (ObjectdetectionFunc)GetProcAddress(hDll, arg2);
>>>>>>> ef9016b3dcf9aa164fd1cf7af351663cc77d8e39
>>>>>>> b43009505c106cd86a24dc01f786b05eafb4d938

    if (batch_inference == NULL) {
        std::cout << "Failed to get the function from DLL" << std::endl;
        return 1;
    }

    // 调用动态链接库中的函数
<<<<<<< HEAD
    int result = batch_inference("cpu", "onnx", "images", "results");
=======
<<<<<<< HEAD
    int result = batch_inference("cpu", "onnx", "images", "results");
=======
    int result = batch_inference(arg3, arg4, arg5, arg6);
>>>>>>> ef9016b3dcf9aa164fd1cf7af351663cc77d8e39
>>>>>>> b43009505c106cd86a24dc01f786b05eafb4d938
    
    std::cout << "Result: " << result << std::endl;

    // 卸载动态链接库
    FreeLibrary(hDll);

    return 0;
}


