#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include "DetectLane.hpp"

//#define USECAM (1)

int main() {
	cv::Mat in;
	cv::Mat edge;
	cv::Mat edge_lane;
	cv::Mat lane_area;
	
	
	cv::VideoCapture cap;
#ifdef USECAM
	cap.open(0);
#else
	cap.open("00000007.AVI");
#endif
	edge.create(240, 320, CV_8UC1);
	edge_lane.create(240, 320, CV_8UC1);
	lane_area.create(240, 320, CV_8UC1);
	cv::namedWindow("edge");
	cv::namedWindow("edge_lane");
	cv::namedWindow("lane_area");

	if (!cap.isOpened())	return -1;
	std::cout << "start cap channel 1\n";
	
	while(1) {
		cap >> in;
		//write main loop
		cv::resize(in, in, cv::Size(320, 240));
		cv::cvtColor(in, edge, CV_RGB2GRAY, 1);
		Canny(edge, edge, 50, 200, 3 );

		edge_lane = cv::Mat::zeros(edge.rows, edge.cols, CV_8UC1);
		//dst = cv::Mat::zeros(edge.rows, edge.cols, CV_8UC1);
		FillLaneArea(edge, edge_lane);

		lane_area = edge_lane.clone();
		InterpolationLaneArea(edge, edge_lane, lane_area);
		
		//Canny(edge_line, dst, 50, 200, 3);	

		cv::imshow("edge",edge);
		cv::imshow("edge_lane",edge_lane);
		cv::imshow("lane_area",lane_area);
		if (cv::waitKey(30)!=255)	break;	//opencv2.4 waitkey() returned -1 when don't press key, but 3.2 return 255!!!!
	}

	return 0;
}

