#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID };

#if 1
int CalibRPY(const char *config_filename,double &pitch, double &yaw, double &roll) {
    /*one image calibration for huayang */
    int board_width = 8, board_height = 6;
    float x_scale = 2.0f, y_scale = 2.0f;
    float squareSize = 1.0f, aspect_ratio = 1.0f;
    int nframes = 16;
    char image_name[256] = { 0 };

    //camera intrinsic//
    double fx = 1299.65, fy = 1299.09, cx = 633.014, cy = 382.188;

    FILE* fp = fopen(/*"one_shot.txt"*/config_filename, "r");
    if (!fp) {
        printf("opening file failed...");
        return -1;
    }


    while (!feof(fp))
    {
        fscanf(fp, "nframes = %d\n", &nframes);
        fscanf(fp, "board_width = %d\n", &board_width);
        fscanf(fp, "board_height = %d\n", &board_height);
        fscanf(fp, "x_scale = %f\n", &x_scale);
        fscanf(fp, "y_scale = %f\n", &y_scale);
        fscanf(fp, "squareSize = %f\n", &squareSize);
        fscanf(fp, "aspect_ratio = %f\n", &aspect_ratio);
        fscanf(fp, "image_name = %s\n", image_name);
        fscanf(fp, "fx = %lf\n", &fx);
        fscanf(fp, "fy = %lf\n", &fy);
        fscanf(fp, "cx = %lf\n", &cx);
        fscanf(fp, "cy = %lf\n", &cy);
        break;
    }

    fclose(fp);

    cv::Mat view = cv::imread(image_name), viewGray, re_view;
    if (!view.data)
    {
        printf("loading image failed...");
        return -1;
    }
    cv::imshow("origin", view);
    cv::waitKey(0);

    view.copyTo(re_view);
    std::vector<std::vector<cv::Point2f>>image_points;
    cv::cvtColor(view, viewGray, cv::COLOR_BGR2GRAY);
    bool found = false;
    Pattern pattern = CHESSBOARD;
    cv::Size boardSize = cv::Size(board_width, board_height);
    std::vector<cv::Point2f> pointbuf;
    for (int iIdx = 0; iIdx < nframes; iIdx++)
    {

        cv::Mat view_large;//XXXX//
        pointbuf.clear();
        cv::resize(viewGray, view_large, cv::Size(view.cols*x_scale, view.rows * y_scale));//XXXX//
        //pointbuf.clear();
        cv::imshow("test", view_large);
        cv::waitKey(0);
        switch (pattern)
        {
        case CHESSBOARD:

            found = cv::findChessboardCorners(/*viewGray*/view_large, boardSize, pointbuf
                , CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE | CV_CALIB_CB_FILTER_QUADS | CV_CALIB_CB_FAST_CHECK);

            if (!found) {
                printf("cannot find chessboard corners !\n");
                /*return 0;*/
            }

            break;
        case CIRCLES_GRID:
            found = cv::findCirclesGrid(view, boardSize, pointbuf);
            break;
        case ASYMMETRIC_CIRCLES_GRID:
            found = cv::findCirclesGrid(view, boardSize, pointbuf, cv::CALIB_CB_ASYMMETRIC_GRID);
            break;
        default:
            return fprintf(stderr, "Unknown pattern type\n"), -1;
        }

        // improve the found corners' coordinate accuracy
        if (pattern == CHESSBOARD && found) {
            cv::cornerSubPix(/*viewGray*/view_large, pointbuf, cv::Size(11, 11),
                cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        }
        for (int i = 0; i < pointbuf.size(); i++) {
            pointbuf[i].x /= x_scale;
            pointbuf[i].y /= y_scale;
        }//XXXX//

        if (found) {
           cv::drawChessboardCorners(view, boardSize, cv::Mat(pointbuf), found);
           cv::imshow("corner", view);
           cv::waitKey(0);
        }

        if (found)
        {
            image_points.push_back(pointbuf);
        }

        if (!found) {
            continue;
        }

        cv::Point   pt0, pt1, pt2, pt3;

        pt0 = cv::Point(2 * pointbuf[0].x - pointbuf[board_width + 1].x, 2 * pointbuf[0].y - pointbuf[board_width + 1].y);
        pt1 = cv::Point(2 * pointbuf[board_width - 1].x - pointbuf[2 * board_width - 2].x, 2 * pointbuf[board_width - 1].y - pointbuf[2 * board_width - 2].y);
        pt2 = cv::Point(2 * pointbuf[board_height*board_width - 1].x - pointbuf[(board_height - 1)*board_width - 2].x, 2 * pointbuf[board_height*board_width - 1].y - pointbuf[(board_height - 1)*board_width - 2].y);
        pt3 = cv::Point(2 * pointbuf[(board_height - 1)*board_width].x - pointbuf[(board_height - 2)*board_width + 1].x, 2 * pointbuf[(board_height - 1)*board_width].y - pointbuf[(board_height - 2)*board_width + 1].y);

        std::vector<cv::Point>pts;
        pts.push_back(pt0);
        pts.push_back(pt1);
        pts.push_back(pt2);
        pts.push_back(pt3);
        cv::Point pts_arr[1][4] = { pt0,pt1,pt2,pt3 };

        const cv::Point* ppt[1] = { pts_arr[0] };
        int npt[] = { 4 };
#if 1
        //cv::circle(view, pt0, 10, cv::Scalar(0, 0, 255), 2);
        //cv::circle(view, pt1, 20, cv::Scalar(0, 255, 0), 2);
        //cv::circle(view, pt2, 30, cv::Scalar(255, 0, 0), 2);
        //cv::circle(view, pt3, 40, cv::Scalar(0, 255, 255), 2);
        //imshow("view image", view);
        fillPoly(viewGray, ppt, npt, 1, cv::Scalar(255, 255, 255));
        //imshow("virture image", viewGray);
        //char c = cv::waitKey(0);
        //if (c == 'q')
        //    break;
#endif
    }//end for 


    if (image_points.size() != 2)
    {
        printf("Detecting chessboard corners failed...\n");
        return -1;
    }

    cv::Point2d points[2] = { cv::Point2d(0.,0.),cv::Point2d(0.,0.) }, left_point, right_point, mid_point;

    for (int iIdx = 0; iIdx < image_points.size(); iIdx++)
    {
        for (int jIdx = 0; jIdx < image_points[iIdx].size(); jIdx++)
        {
            points[iIdx].x += image_points[iIdx][jIdx].x;
            points[iIdx].y += image_points[iIdx][jIdx].y;
        }

        //normalize//
        points[iIdx].x /= (image_points[iIdx].size() + 0.0000001);
        points[iIdx].y /= (image_points[iIdx].size() + 0.0000001);
    }


    if (points[0].x <= points[1].x)
    {
        left_point = points[0];
        right_point = points[1];
    }
    else
    {
        left_point = points[1];
        right_point = points[0];
    }

    //left_point = cv::Point2d(454.0, 382.5);
    //right_point = cv::Point2d(957.0, 385.0);

    mid_point = (left_point + right_point)*0.5;
    double x = mid_point.x, y = mid_point.y;

    //double pitch, yaw, roll;
    pitch = -(y - cy) / fy;
    yaw = -(x - cx) / fx;
    roll = (right_point.y - mid_point.y) / (right_point.x - mid_point.x);
    printf("pitch:%lf,yaw:%lf,roll:%lf\n", pitch, yaw, roll);
    printf("calibration successful !");
    system("pause");
    return 0;
}
#else
int CalibRPY(const char *config_filename, double &pitch, double &yaw, double &roll) {
  /*one image calibration for huayang */
  int board_width = 8, board_height = 6;
  float x_scale = 2.0f, y_scale = 2.0f;
  float squareSize = 1.0f, aspect_ratio = 1.0f;
  int nframes = 16;
  char image_name[256] = { 0 };

  //camera intrinsic//
  double fx = 1299.65, fy = 1299.09, cx = 633.014, cy = 382.188;

  FILE* fp = fopen(/*"one_shot.txt"*/config_filename, "r");
  if (!fp) {
    printf("opening file failed...");
    return -1;
  }


  while (!feof(fp))
  {
    fscanf(fp, "nframes = %d\n", &nframes);
    fscanf(fp, "board_width = %d\n", &board_width);
    fscanf(fp, "board_height = %d\n", &board_height);
    fscanf(fp, "x_scale = %f\n", &x_scale);
    fscanf(fp, "y_scale = %f\n", &y_scale);
    fscanf(fp, "squareSize = %f\n", &squareSize);
    fscanf(fp, "aspect_ratio = %f\n", &aspect_ratio);
    fscanf(fp, "image_name = %s\n", image_name);
    fscanf(fp, "fx = %lf\n", &fx);
    fscanf(fp, "fy = %lf\n", &fy);
    fscanf(fp, "cx = %lf\n", &cx);
    fscanf(fp, "cy = %lf\n", &cy);
    break;
  }

  fclose(fp);

  cv::Mat view = cv::imread(image_name), viewGray, re_view;
  if (!view.data)
  {
    printf("loading image failed...");
    return -1;
  }

  view.copyTo(re_view);
  std::vector<std::vector<cv::Point2f>>image_points;
  cv::cvtColor(view, viewGray, cv::COLOR_BGR2GRAY);
  bool found = false;
  Pattern pattern = CHESSBOARD;
  cv::Size boardSize = cv::Size(board_width, board_height);

  for (int iIdx = 0; iIdx < nframes; iIdx++)
  {

    cv::Mat view_large;//XXXX//
    std::vector<cv::Point2f> pointbuf;
    cv::resize(viewGray, view_large, cv::Size(view.cols*x_scale, view.rows * y_scale));//XXXX//
                                                                                       //pointbuf.clear();

    switch (pattern)
    {
    case CHESSBOARD:

      found = cv::findChessboardCorners(/*viewGray*/view_large, boardSize, pointbuf
        , CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE /*| CV_CALIB_CB_FILTER_QUADS*//*| CV_CALIB_CB_FAST_CHECK*/);

      if (!found) {
        printf("cannot find chessboard corners !\n");
        /*return 0;*/
      }

      break;
    case CIRCLES_GRID:
      found = cv::findCirclesGrid(view, boardSize, pointbuf);
      break;
    case ASYMMETRIC_CIRCLES_GRID:
      found = cv::findCirclesGrid(view, boardSize, pointbuf, cv::CALIB_CB_ASYMMETRIC_GRID);
      break;
    default:
      return fprintf(stderr, "Unknown pattern type\n"), -1;
    }

    // improve the found corners' coordinate accuracy
    if (pattern == CHESSBOARD && found) {
      cv::cornerSubPix(/*viewGray*/view_large, pointbuf, cv::Size(11, 11),
        cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
    }
    for (int i = 0; i < pointbuf.size(); i++) {
      pointbuf[i].x /= x_scale;
      pointbuf[i].y /= y_scale;
    }//XXXX//

    if (found) {
      cv::drawChessboardCorners(view, boardSize, cv::Mat(pointbuf), found);
    }

    if (found)
    {
      image_points.push_back(pointbuf);
    }

    if (!found) {
      continue;
    }

    cv::Point   pt0, pt1, pt2, pt3;

    pt0 = cv::Point(2 * pointbuf[0].x - pointbuf[board_width + 1].x, 2 * pointbuf[0].y - pointbuf[board_width + 1].y);
    pt1 = cv::Point(2 * pointbuf[board_width - 1].x - pointbuf[2 * board_width - 2].x, 2 * pointbuf[board_width - 1].y - pointbuf[2 * board_width - 2].y);
    pt2 = cv::Point(2 * pointbuf[board_height*board_width - 1].x - pointbuf[(board_height - 1)*board_width - 2].x, 2 * pointbuf[board_height*board_width - 1].y - pointbuf[(board_height - 1)*board_width - 2].y);
    pt3 = cv::Point(2 * pointbuf[(board_height - 1)*board_width].x - pointbuf[(board_height - 2)*board_width + 1].x, 2 * pointbuf[(board_height - 1)*board_width].y - pointbuf[(board_height - 2)*board_width + 1].y);

    std::vector<cv::Point>pts;
    pts.push_back(pt0);
    pts.push_back(pt1);
    pts.push_back(pt2);
    pts.push_back(pt3);
    cv::Point pts_arr[1][4] = { pt0,pt1,pt2,pt3 };

    const cv::Point* ppt[1] = { pts_arr[0] };
    int npt[] = { 4 };

    cv::circle(view, pt0, 10, cv::Scalar(0, 0, 255), 2);
    cv::circle(view, pt1, 20, cv::Scalar(0, 255, 0), 2);
    cv::circle(view, pt2, 30, cv::Scalar(255, 0, 0), 2);
    cv::circle(view, pt3, 40, cv::Scalar(0, 255, 255), 2);
    imshow("view image", view);
    fillPoly(viewGray, ppt, npt, 1, cv::Scalar(255, 255, 255));
    imshow("virture image", viewGray);
    char c = cv::waitKey(0);
    if (c == 'q')
      break;

  }//end for 


  if (image_points.size() != 2)
  {
    printf("Detecting chessboard corners failed...\n");
    return -1;
  }

  cv::Point2d points[2] = { cv::Point2d(0.,0.),cv::Point2d(0.,0.) }, left_point, right_point, mid_point;

  for (int iIdx = 0; iIdx < image_points.size(); iIdx++)
  {
    for (int jIdx = 0; jIdx < image_points[iIdx].size(); jIdx++)
    {
      points[iIdx].x += image_points[iIdx][jIdx].x;
      points[iIdx].y += image_points[iIdx][jIdx].y;
    }

    //normalize//
    points[iIdx].x /= (image_points[iIdx].size() + 0.0000001);
    points[iIdx].y /= (image_points[iIdx].size() + 0.0000001);
  }


  if (points[0].x <= points[1].x)
  {
    left_point = points[0];
    right_point = points[1];
  }
  else
  {
    left_point = points[1];
    right_point = points[0];
  }

  //left_point = cv::Point2d(454.0, 382.5);
  //right_point = cv::Point2d(957.0, 385.0);

  mid_point = (left_point + right_point)*0.5;
  double x = mid_point.x, y = mid_point.y;

  //double pitch, yaw, roll;
  pitch = -(y - cy) / fy;
  yaw = -(x - cx) / fx;
  roll = (right_point.y - mid_point.y) / (right_point.x - mid_point.x);
  printf("pitch:%lf,yaw:%lf,roll:%lf\n", pitch, yaw, roll);
  printf("calibration successful !");
  return 0;
}
#endif
int main() {
  double pitch, yaw, roll;
  CalibRPY("E:/Works/Exercise/references/opencv/bookstudy/opencv3_codeprj/Calibration/one_shot.txt", pitch, yaw, roll);
}