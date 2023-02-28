#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	Mat img1 = imread("../assets/doctor-house.png");
	Mat img2 = imread("../assets/doctor-house-tongue.png");

	if (img1.empty() || img2.empty())
	{
		std::cout << "Erro ao carregar a imagem" << std::endl;
		return -1;
	}

	Mat result;
	int result_cols = img1.cols - img2.cols + 1;
	int result_rows = img1.rows - img2.rows + 1;
	result.create(result_rows, result_cols, CV_32FC1);

	matchTemplate(img1, img2, result, TM_CCOEFF_NORMED);
	Point max_loc;
	minMaxLoc(result, NULL, NULL, NULL, &max_loc);

	rectangle(img1, max_loc, Point(max_loc.x + img2.cols, max_loc.y + img2.rows), Scalar(0, 0, 255), 2);
	imshow("Object detector", img1);

	// X: 464
	// Y: 773

	waitKey(0);
}