#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "vector"
#include "iostream"
#include "utils.h"

using namespace cv;
using namespace std;

void show_result(Mat img1, Mat img2, vector<KeyPoint> keyImg1, vector<KeyPoint> keyImg2, vector<DMatch> bestMatches)
{
	Mat result;
	drawMatches(img1, keyImg1, img2, keyImg2, bestMatches, result);
	imshow("Result", result);
}

int main(int argc, char **argv)
{
	vector<Mat> images = get_images(argc, argv);
	Mat img1 = images[0];
	Mat img2 = images[1];

	auto [keyImg1, keyImg2, descImg1, descImg2, matches] = match_image(img1, img2);
	Ptr<DescriptorMatcher> descriptorMatcher = DescriptorMatcher::create("BruteForce");

	Mat distances = calc_distance(matches);
	vector<DMatch> bestMatches = get_best_matches(matches, distances);

	show_result(img1, img2, keyImg1, keyImg2, bestMatches);
	waitKey();
	return 0;
}