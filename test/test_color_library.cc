#include "color_library.hh"

#include <boost/filesystem.hpp>
namespace fs = ::boost::filesystem;

#include <string>
#include <iostream>
#include <ros/package.h>

#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/imgproc.hpp>

namespace cv{
	typedef Vec<unsigned char, 3> Vec3u;
}

using namespace color_utils;

int main (int argc, char *argv[]){ 

	fs::path palette_path = ros::package::getPath("color_utils");
	palette_path /= "palettes";

	std::cout << "Testing ColorLibrary::SetRoot(...)" << std::endl;
	ColorLibrary::SetRoot(palette_path);
	std::cout << ColorLibrary();

	std::cout << "Testing ColorLibrary::SetRootFromPackageName(...)" << std::endl;
	ColorLibrary::SetRootFromPackageName("color_utils");
	std::cout << ColorLibrary();

	std::cout << "Testing ColorLibrary::GetPaletteNames(...)" << std::endl;
	std::vector<std::string> palette_names = ColorLibrary::GetPaletteNames();
	for(auto pname : palette_names)
		std::cout << "<" << pname << "> ";
	std::cout << std::endl << std::endl;
	
	// palette_names.erase(palette_names.begin() + 1, palette_names.end());

	int num_color_levels = 64;
	cv::Mat colors(num_color_levels, palette_names.size(), CV_8UC3);

	std::cout << "Testing ColorLibrary::PickColor(...)" << std::endl;
	for(uint32_t pind = 0 ; pind < palette_names.size() ; pind++){

		ColorLibrary::SetPalette(palette_names[pind]);

		std::cout << "[" << pind << "] - " << palette_names[pind] << std::endl;

		for(int32_t i = 0 ; i < num_color_levels ; i++){
			Color color = ColorLibrary::PickColor((float)i / num_color_levels) * 255;
			cv::Vec3u &c = colors.at<cv::Vec3u>(i, pind);
			c[0] = color(2);
			c[1] = color(1);
			c[2] = color(0);
		}
	}

	cv::namedWindow("Color Palettes", cv::WINDOW_NORMAL);
	cv::imshow("Color Palettes", colors);
	std::cout << "Press <q> to close the OpenCV window." << std::endl;
	while(cv::waitKey(1) != 'q');
	return 0;
}