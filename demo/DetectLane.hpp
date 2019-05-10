#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>


int test(cv::Mat in) {
	int pos;
	for(int i=0; i<in.rows; i++) {
		for(int j=0; j<in.cols; j++) {
			pos = 3*(i*in.cols + j);
			in.data[pos] = 0;
			in.data[pos+1] = 255;
			in.data[pos+2] = 0;
		}
	}
	return 0;
}

int HoughLineSegmentDetect(cv::Mat in, cv::Mat out) {
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(in, lines, 4, CV_PI/6, 40, 10, 5);
	for( size_t i = 0; i < lines.size(); i++ ) {
		line( out, cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2], lines[i][3]), cv::Scalar(0,0,255), 1, 8 );
	}
	return 0;
}


int HoughLineDetect(cv::Mat in, cv::Mat out) {
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(in, lines, 4, CV_PI/30, 50 );

	for( size_t i = 0; i < lines.size(); i++ ) {
		float rho = lines[i][0];
		float theta = lines[i][1];
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		cv::Point pt1(cvRound(x0 + 1000*(-b)), cvRound(y0 + 1000*(a)));
		cv::Point pt2(cvRound(x0 - 1000*(-b)), cvRound(y0 - 1000*(a)));
		cv::line( out, pt1, pt2, cv::Scalar(0,0,255), 1, 8 );
	}
	return 0;
}

int FillLaneArea(cv::Mat in, cv::Mat out) {
	const int upper_limit = 150;
	const int cx = 170;
	const int cy = 239;
	int posp, posm;
	int y;
	bool flagp, flagm;

	out.data[(out.cols*cy + cx)] = 255;

	
	for(int i=in.rows-1; i>=upper_limit; i--) {
		y = in.cols*i;
		flagp = true;
		flagm = true;
		for(int j=1; j<in.cols; j++) {
			posp = y + cx + j;
			posm = y + cx - j;
			if ((cx + j) < in.cols && in.data[posp] < 100 && flagp)
				out.data[posp] = 255;
			else	flagp = false;
			if ((cx - j) >= 0 && in.data[posm] < 100 && flagm)
				out.data[posm] = 255;
			else	flagm = false;
		}
	}
	return 0;
}

int InterpolationLaneArea(cv::Mat in, cv::Mat out) {
	const int upper_limit = 140;
	int y0 = 0;
	int y1 = 0;
//	cv::Mat map;
//	map.create(in.rows, in.cols, CV_8UC1);
	
	for(int i=upper_limit; i<in.rows; i++) {
		y0 = in.cols*(i-1);
		y1 = in.cols*i;
		for(int j=0; j<in.cols; j++) {
			if (in.data[y1 + j] == 0 && (in.data[y0 + j] > 0 || out.data[y0 + j] > 0)) {
				out.data[y1 + j] = 100;
			}
		}
	}

	for(int i=in.rows-2; i>=upper_limit; i--) {
		y0 = in.cols*(i+1);
		y1 = in.cols*i;
		for(int j=0; j<in.cols; j++) {
			if (in.data[y1 + j] == 0 && out.data[y1 + j] > 0 
				&& (in.data[y0 + j] > 0 || out.data[y0 + j])) {
				out.data[y1 + j] = 255;
			}
		}
	}
	return 0;
}

int DetectLaneEdge(cv::Mat in, cv::Mat out) {
	const int cx = 160;
	const int cy = 239;
	int posp, posm;
	int y;
	bool flagp, flagm;

	out.data[(out.cols*cy + cx)] = 255;
	
	for(int i=in.rows-1; i>=in.rows/2; i--) {
		y = in.cols*i;
		flagp = true;
		flagm = true;
		for(int j=1; j<in.cols; j++) {
			posp = y + cx + j;
			posm = y + cx - j;
			if ((cx + j) < in.cols && in.data[posp] > 100 && flagp) {
				out.data[posp] = 255;
				flagp = false;
			}
			if ((cx - j) >= 0 && in.data[posm] > 100 && flagm) {
				out.data[posm] = 255;
				flagm = false;
			}
		}
	}
	return 0;
}
