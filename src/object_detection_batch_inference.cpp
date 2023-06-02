#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <mmdeploy/detector.h>

extern "C"{
  __declspec(dllexport) int batch_inference(const char* device_name, const char* model_path, const char* image_dir, const char* result_dir);
  __declspec(dllexport) int do_inference(const char *device_name, const char *model_path, const char *image_path, const char *result_path);
}

//批处理函数
int batch_inference(const char* device_name, const char* model_path, const char* image_dir, const char* result_dir) {
    std::string search_path = std::string(image_dir) + "\\*";
    WIN32_FIND_DATAA file_data;
    HANDLE hFind;

    hFind = FindFirstFileA(search_path.c_str(), &file_data);
    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to open directory: %s\n", image_dir);
        return 1;
    }
    

    do {
        if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // 跳过目录
            continue;
        }

        std::string filename(file_data.cFileName);
        std::string image_path = std::string(image_dir) + "\\" + filename;
        std::string result_path = std::string(result_dir) + "\\" + filename;

        //对于每张图片调用do_inference实现推理和结果保存
        do_inference(device_name, model_path, image_path.c_str(), result_path.c_str());

    } while (FindNextFileA(hFind, &file_data) != 0);

    FindClose(hFind);
    
    return 0;
}


//单张图片推理函数
int do_inference(const char *device_name, const char *model_path, const char *image_path, const char *result_path) {

  //初始化mmdeploy_detector对象
  mmdeploy_detector_t detector{};
  int status{};
  status = mmdeploy_detector_create_by_path(model_path, device_name, 0, &detector);
  if (status != MMDEPLOY_SUCCESS) {
    fprintf(stderr, "failed to create detector, code: %d\n", (int)status);
    return 1;
  }

  //单张图片处理操作
  cv::Mat img = cv::imread(image_path);
  if (!img.data) {
    fprintf(stderr, "failed to load image: %s\n", image_path);
    return 1;
  }

  mmdeploy_mat_t mat{
      img.data, img.rows, img.cols, 3, MMDEPLOY_PIXEL_FORMAT_BGR, MMDEPLOY_DATA_TYPE_UINT8};

  mmdeploy_detection_t* bboxes{};
  int* res_count{};
  status = mmdeploy_detector_apply(detector, &mat, 1, &bboxes, &res_count);
  if (status != MMDEPLOY_SUCCESS) {
    fprintf(stderr, "failed to apply detector, code: %d\n", (int)status);
    return 1;
  }

  fprintf(stdout, "bbox_count=%d\n", *res_count);

  for (int i = 0; i < *res_count; ++i) {
    const auto& box = bboxes[i].bbox;
    const auto& mask = bboxes[i].mask;

    fprintf(stdout, "box %d, left=%.2f, top=%.2f, right=%.2f, bottom=%.2f, label=%d, score=%.4f\n",
            i, box.left, box.top, box.right, box.bottom, bboxes[i].label_id, bboxes[i].score);

    // skip detections with invalid bbox size (bbox height or width < 1)
    if ((box.right - box.left) < 1 || (box.bottom - box.top) < 1) {
      continue;
    }

    // skip detections less than specified score threshold
    if (bboxes[i].score < 0.3) {
      continue;
    }

    // generate mask overlay if model exports masks
    if (mask != nullptr) {
      fprintf(stdout, "mask %d, height=%d, width=%d\n", i, mask->height, mask->width);

      cv::Mat imgMask(mask->height, mask->width, CV_8UC1, &mask->data[0]);
      auto x0 = std::max(std::floor(box.left) - 1, 0.f);
      auto y0 = std::max(std::floor(box.top) - 1, 0.f);
      cv::Rect roi((int)x0, (int)y0, mask->width, mask->height);

      // split the RGB channels, overlay mask to a specific color channel
      cv::Mat ch[3];
      split(img, ch);
      int col = 0;  // int col = i % 3;
      cv::bitwise_or(imgMask, ch[col](roi), ch[col](roi));
      merge(ch, 3, img);
    }

    std::string label;
    if (bboxes[i].label_id == 0)
        label = "rust";
    else if (bboxes[i].label_id == 1)
        label = "scratch";
    else if (bboxes[i].label_id == 2)
        label = "spot";
    else
        label = "unknown";

    cv::rectangle(img, cv::Point{(int)box.left, (int)box.top},
                  cv::Point{(int)box.right, (int)box.bottom}, cv::Scalar{0, 255, 0});

    // 绘制类别名称和置信度分数
    std::string text = label + ": " + std::to_string(bboxes[i].score);
    cv::putText(img, text, cv::Point{(int)box.left, (int)box.top - 5}, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar{0, 0, 255}, 2);
    
  }

  //保存图像到result_path中
  cv::imwrite(result_path, img);

  mmdeploy_detector_release_result(bboxes, res_count, 1);

  mmdeploy_detector_destroy(detector);

  return 0;
}
