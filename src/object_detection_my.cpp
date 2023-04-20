#include <fstream>
#include <string>
#include<vector>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "mmdeploy/detector.h"


extern "C"{
__declspec(dllexport) int main(char* argv[]);
}

//推理函数
vector<string> do_inference(auto device_name, auto model_path, auto image_path, int status, mmdeploy_detector_t detector){

  cv::Mat img = cv::imread(image_path);

  mmdeploy_detection_t* bboxes{};
  
  mmdeploy_mat_t mat{
      img.data, img.rows, img.cols, 3, MMDEPLOY_PIXEL_FORMAT_BGR, MMDEPLOY_DATA_TYPE_UINT8};
  
  if (!img.data) {
    fprintf(stderr, "failed to load image: %s\n", image_path);
    return 1;
  }

  int* res_count{};
  status = mmdeploy_detector_apply(detector, &mat, 1, &bboxes, &res_count);
  if (status != MMDEPLOY_SUCCESS) {
    fprintf(stderr, "failed to apply detector, code: %d\n", (int)status);
    return 1;
  }

  fprintf(stdout, "bbox_count=%d\n", *res_count);
  vector<string> results;
  for (int i = 0; i < *res_count; ++i) {
    const auto& box = bboxes[i].bbox;
    const auto& mask = bboxes[i].mask;

    fprintf(stdout, "box %d, left=%.2f, top=%.2f, right=%.2f, bottom=%.2f, label=%d, score=%.4f\n",
            i, box.left, box.top, box.right, box.bottom, bboxes[i].label_id, bboxes[i].score);
    
    string tmp = "box: " + i + ", left=" + box.left + ", top=" + box.top + ", right=" + box.right + ", bottom=" + box.bottom + ", label=" + bboxes[i].label_id + ", score=" + bboxes[i].score;
    
    // 添加到vector数组中
    results.push_back(tmp);

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

    cv::rectangle(img, cv::Point{(int)box.left, (int)box.top},
                  cv::Point{(int)box.right, (int)box.bottom}, cv::Scalar{0, 255, 0});
  }
  cv::imwrite("output_detection.png", img);
}


//传入字符串
int main(char* argv[]) {
   //得到需要的推理变量，以空格分开
  auto device_name = argv[0];
  auto model_path = argv[1];
  auto image_path = argv[2];

  //调用do_inference函数，处理图片
  //todo: batch processing images
  mmdeploy_detector_t detector{};
  int status{};
  status = mmdeploy_detector_create_by_path(model_path, device_name, 0, &detector);

  if (status != MMDEPLOY_SUCCESS) {
    fprintf(stderr, "failed to create detector, code: %d\n", (int)status);
    return 1;
  }
  

  do_inference(device_name, model_path, image_path, status, detector);
  
  mmdeploy_detector_release_result(bboxes, res_count, 1);
  mmdeploy_detector_destroy(detector);

  return 0;
}
