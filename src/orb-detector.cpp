#include "opencv2/core.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2D.hpp"
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

static void help(char *argv[])
{
	cout << "\n This program demonstrates how to detect compute and match ORB BRISK and AKAZE descriptors \n"
					"Usage: \n  "
			 << argv[0] << " --image1=<image1(doctor-house.png as default)> --image2=<image2(doctor-house-tongue.png as default)>\n"
										 "Press a key when image window is active to change algorithm or descriptor";
}

int main(int argc, char **argv)
{
	cv::CommandLineParser parser(
			argc,
			argv,
			"{ @image1 | ../assets/doctor-house.png | }"
			"{ @image2 | ../assets/doctor-house-tongue.png | }"
			"{help h ||}");
	if (parser.has("help"))
	{
		help(argv);
		return 0;
	}

	String fileName1 = samples::findFile(parser.get<string>(0));
	String fileName2 = samples::findFile(parser.get<string>(1));
	Mat img_1 = imread(fileName1, IMREAD_GRAYSCALE);
	Mat img_2 = imread(fileName2, IMREAD_GRAYSCALE);

	Ptr<ORB> detector = ORB::create();
	vector<DMatch> matches;
	// FlannBasedMatcher matcher;
	Ptr<DescriptorMatcher> descriptorMatcher;
	Mat desc_1, desc_2;
	vector<KeyPoint> keypoints_1, keypoints_2;

	detector->detect(img_1, keypoints_1, desc_1);
	// detector->detect(img_2, keypoints_2, desc_2);

	detector->compute(img_1, keypoints_1, desc_1);
	detector->detectAndCompute(img_2, Mat(), keypoints_2, desc_2);

	descriptorMatcher = DescriptorMatcher::create("BruteForce-L1");
	descriptorMatcher->match(desc_1, desc_2, matches, Mat());

	Mat index;
	int nbMatch = int(matches.size());
	Mat tab(nbMatch, 1, CV_32F);
	for (int i = 0; i < nbMatch; i++)
	{
		tab.at<float>(i, 0) = matches[i].distance;
	}
	sortIdx(tab, index, SORT_EVERY_COLUMN + SORT_ASCENDING);
	vector<DMatch> bestMatches;
	for (int i = 0; i < 30; i++)
	{
		bestMatches.push_back(matches[index.at<int>(i, 0)]);
	}

	Mat img_match;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, bestMatches, img_match);
	imshow("Matches", img_match);

	waitKey(10000);
	return 0;
}