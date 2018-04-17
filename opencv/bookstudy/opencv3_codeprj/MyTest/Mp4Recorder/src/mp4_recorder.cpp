#include <iostream>
#include<string>
#include <chrono>
#include <ctime>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

#define KEY_EXIT 113 //keyboard q
static int64_t GetEpochTimeMs() {
  std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  return  time.count();
}
static std::string TimeMstoStringMs(int64_t timeMs) {
  auto ttime_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point(std::chrono::milliseconds(timeMs)));
  auto tp_sec = std::chrono::system_clock::from_time_t(ttime_t);
  int ms = (timeMs % 1000);

  std::tm * ttm = localtime(&ttime_t);
  char date_time_format[] = "%Y%m%d-%H%M%S";
  char time_str[] = "yyyy.mm.dd.HH-MM.SS.fff";
  strftime(time_str, strlen(time_str), date_time_format, ttm);
  sprintf(&time_str[strlen(time_str)], "_%03d", ms);
  return time_str;
}
void Usage() {
  std::cout << "./Mp4Recorder device_id save_path max_slice_time(unit:min) fps width height" << std::endl;
}
int main(int argc, char* argv[])
{
  if (argc < 7) {
    Usage();
    getchar();
    return -1;
  }
  int device_index = atoi(argv[1]);
  std::string save_path = argv[2];
  std::string mp4_name = save_path;
  if (mp4_name.rfind("/") != std::string::npos) { // path is unix style
    mp4_name += "/";
  }
  else if (mp4_name.rfind("\\") != std::string::npos) { //path is windows style
    if (mp4_name.rfind("\\") != mp4_name.length() - 2) {
      mp4_name += "\\";
    }
  }
  else {
    std::cout << "save path " << mp4_name << " invalid!!" << std::endl;
    getchar();
    return -1;
  }

  mp4_name += TimeMstoStringMs(GetEpochTimeMs());
  mp4_name += ".mp4";
  int max_slice_time = atoi(argv[3]);
  int fps = atoi(argv[4]);
  int dst_width = atoi(argv[5]);
  int dst_height = atoi(argv[6]);
  if (fps > 30 || fps < 1) {
    Usage();
    getchar();
    return -1;
  }
  cv::VideoCapture capture(device_index);
  if (!capture.isOpened()) {
    std::cout << "can not open camera device " << device_index << std::endl;
    getchar();
    return -1;
  }
  int src_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
  int src_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
  cv::VideoWriter write;
  cv::Size src_size(src_width, src_height);
  cv::Size dst_size(dst_width, dst_height);
  //double fps_src = capture.get(CV_CAP_PROP_FPS);
  //std::cout << "camera fps is " << fps_src << std::endl;
  bool status = write.open(mp4_name, CV_FOURCC('H', '2', '6', '4'), fps, dst_size, true);
  if (!status) {
    std::cout << "video writer open " << mp4_name << " failed!!, fps = " << fps << std::endl;
    capture.release();
    write.release();
    getchar();
    return -1;
  }
  bool running = true;
  cv::Mat frame;
  cv::Mat dstframe;
  int64_t history_time = GetEpochTimeMs();
  int64_t cur_time = GetEpochTimeMs();
  int64_t slice_time = max_slice_time * 60 * 1000; // ms
  while (running) {
    if (!capture.read(frame)) {
      std::cout << "capture failed" << std::endl;
      continue;
    }
    cv::imshow("video", frame);
    if(src_size != dst_size)
      cv::resize(frame, dstframe, dst_size);
    write << dstframe;
    int key = cv::waitKey(10);
    if (key == KEY_EXIT)
      break;
    cur_time = GetEpochTimeMs();
    if (cur_time - history_time >= slice_time) {
      //std::cout << "cur_time " << cur_time << ", history_time = " << history_time << ", delt = " << cur_time - history_time << ", slice_time = " << slice_time << std::endl;
      history_time = cur_time;
      write.release();
      //============create new file============>
      mp4_name = save_path;
      if (mp4_name.rfind("/") != std::string::npos) { // path is unix style
        mp4_name += "/";
      }
      else if (mp4_name.rfind("\\") != std::string::npos) { //path is windows style
        if (mp4_name.rfind("\\") != mp4_name.length() - 2) {
          mp4_name += "\\";
        }
      }
      mp4_name += TimeMstoStringMs(GetEpochTimeMs());
      mp4_name += ".mp4";
      status = write.open(mp4_name, CV_FOURCC('H', '2', '6', '4'), fps, dst_size, true);
      if (!status) {
        std::cout << "video writer open " << mp4_name << " failed!!, fps = " << fps << std::endl;
        capture.release();
        write.release();
        getchar();
        return -1;
      }
    }
  }

  capture.release();
  write.release();
  return 0;
}

