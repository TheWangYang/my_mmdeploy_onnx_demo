import ctypes
import os

# 单张图片推理dll库
# os.chdir(r'E:/PyCharmWorkPlace/my_mmdeploy_onnx_demo/dll/')

# object_detection_dll = ctypes.cdll.LoadLibrary('E:/PyCharmWorkPlace/my_mmdeploy_onnx_demo/dll/objectdetection.dll')
# results = object_detection_dll.do_inference(b"cpu", b"E:/PyCharmWorkPlace/my_mmdeploy_onnx_demo/onnx", 
#                                             b"E:/PyCharmWorkPlace/my_mmdeploy_onnx_demo/images/test1.jpg")
# print("调用C DLL动态库得到的结果为: {}".format(results))


# 多张图片批量推理dll库
os.chdir(r'E:/PyCharmWorkPlace/my_mmdeploy_onnx_demo/dll/')

onnx_inference_dll = ctypes.cdll.LoadLibrary('E:\\PyCharmWorkPlace\\my_mmdeploy_onnx_demo\\dll\\onnx_inference.dll')

results = onnx_inference_dll.batch_inference(b"cpu", b"E:\\PyCharmWorkPlace\\my_mmdeploy_onnx_demo\\onnx", 
                                            b"E:\\PyCharmWorkPlace\\my_mmdeploy_onnx_demo\\images",
                                            b"E:\\PyCharmWorkPlace\\my_mmdeploy_onnx_demo\\results")
print("The result obtained by calling the C DLL dynamic library is: {}".format(results))



