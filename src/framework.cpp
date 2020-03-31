#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>



cv::Mat& Lightness(Mat& I, int value) {
	CV_Assert(I.depth() != sizeof(uchar));
	switch (I.channels()) {
	case 1:
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = (I.at<uchar>(i, j) / 32) * 32;
		break;
	case 3:
		Mat_<Vec3b> _I = I;
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j) {
				_I(i, j)[0] = checkRange(_I(i, j)[0] + value);
				_I(i, j)[1] = checkRange(_I(i, j)[1] + value);
				_I(i, j)[2] = checkRange(_I(i, j)[2] + value);
			}
		I = _I;
		break;
	}
	return I;
}


cv::Mat& Contrast(Mat& I, int value) {
	CV_Assert(I.depth() != sizeof(uchar));
	switch (I.channels()) {
	case 1:
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = (I.at<uchar>(i, j) / 32) * 32;
		break;
	case 3:
		cv::Mat_<Vec3b> _I = I;
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j) {
				_I(i, j)[0] = checkRange(_I(i, j)[0] * value );
				_I(i, j)[1] = checkRange(_I(i, j)[1] * value );
				_I(i, j)[2] = checkRange(_I(i, j)[2] * value );
			}
		I = _I;
		break;
	}
	return I;
}


cv::Mat& perform(cv::Mat& I){
  CV_Assert(I.depth() != sizeof(uchar));
  switch(I.channels())  {
  case 1:
    for( int i = 0; i < I.rows; ++i)
        for( int j = 0; j < I.cols; ++j )
            I.at<uchar>(i,j) = (I.at<uchar>(i,j)/32)*32;
    break;
  case 3:
    cv::Mat_<cv::Vec3b> _I = I;
    for( int i = 0; i < I.rows; ++i)
        for( int j = 0; j < I.cols; ++j ){
            _I(i,j)[0] = (_I(i,j)[0]/32)*32;
            _I(i,j)[1] = (_I(i,j)[1]/32)*32;
            _I(i,j)[2] = (_I(i,j)[2]/32)*32;
        }
    I = _I;
    break;
  }
  return I;
}

cv::Mat selectMax(cv::Mat& I){
    CV_Assert(I.depth() != sizeof(uchar));
    cv::Mat  res(I.rows,I.cols, CV_8UC3);
    switch(I.channels())  {
    case 3:
        cv::Mat_<cv::Vec3b> _I = I;
        cv::Mat_<cv::Vec3b> _R = res;
        for( int i = 0; i < I.rows; ++i)
            for( int j = 0; j < I.cols; ++j ){
                int sel = (_I(i,j)[0] < _I(i,j)[1])?1:0;
                sel = _I(i,j)[sel] < _I(i,j)[2]?2:sel;
                _R(i,j)[0] = sel==0?255:0;
                _R(i,j)[1] = sel==1?255:0;
                _R(i,j)[2] = sel==2?255:0;
            }
        res = _R;
        break;
    }
    return res;
}


int main(int, char *[]) {
    std::cout << "Start ..." << std::endl;
    cv::Mat image = cv::imread("../img/Lena.png");
    cv::Mat image2 = image(cv::Rect(100,100,100,100));
    perform(image2);
    cv::Mat max = selectMax(image);
    cv::imshow("Lena", image);
    cv::imshow("Max", max);
    std::cout << image2.isContinuous() << max.isContinuous() << std::endl;
    cv::imwrite("../img/Max.png",max);
    cv::waitKey(-1);
    return 0;
}
