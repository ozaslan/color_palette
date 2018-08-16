#include "color_palette.hh"

#include "boost_assert_helper.hpp" // This has to come first due to a define macro
#include <boost/assert.hpp>

#include <cmath>
#include <fstream>

namespace color_utils{

uint32_t ColorPalette::loadFromFile(const fs::path &path){

	_colors.clear();
	_colors.reserve(__init_size);

	if( !fs::exists(path) ){
		std::stringstream ss;
		ss << "In ColorPalette::" << __FUNCTION__ << ", ";
		ss << "path <" << path.string() << "> does not exist ";
		ss << "at file : " << __FILE__ << " line " << __LINE__;
		throw ss.str();
	} else if( !fs::is_regular_file(path) ){
		std::stringstream ss;
		ss << "In ColorPalette::" << __FUNCTION__ << ", ";
		ss << "path <" << path.string() << "> is not of a regular file ";
		ss << "at file : " << __FILE__ << " line " << __LINE__;
		throw ss.str();
	}

	_name = path.stem().string();

	std::ifstream ifs(path.string(), std::ifstream::in);

	while(ifs.good()){
		Eigen::Vector3f color;
		ifs >> color(0) >> color(1) >> color(2);
		_colors.push_back(color);
	}

	ifs.close();

	return _colors.size();
}

uint32_t ColorPalette::loadFromFile(const std::string& path){
	return this->loadFromFile(fs::path(path));
}

ColorPalette::ColorPalette(){}

ColorPalette::ColorPalette(const std::string& path){
	this->loadFromFile(path);
}

Color ColorPalette::operator[](float idx) const {

	BOOST_ASSERT_MSG(0 <= idx && idx <= 1, "0 <= idx <= 1 should hold.");
	BOOST_ASSERT_MSG(_colors.empty() == false, "Color palette is empty, _colors.empty() == true .");

    // Size of the palette
	uint32_t num_colors = _colors.size();

    // Remapped index
	idx *= num_colors;

	float fractpart, intpart;
	fractpart = std::modf( idx, &intpart );

	return _colors[intpart] + (_colors[intpart + 1] - _colors[intpart]) * fractpart;
}

void ColorPalette::print() const {
	std::cout << *this;
}

std::ostream& operator<<(std::ostream &stream, const ColorPalette &palette) {
	stream << "----------------------------------" << std::endl;
	stream << "Palette name : [ " << palette.name() << " ]" << std::endl;

	char buffer[1024];
	for( uint32_t i = 0 ; i < palette.size() ; i++ ){
		Color color = palette[(float)i / palette.size()];
		sprintf(buffer, "[ %2d ] : [ %.2f, %.2f, %.2f ]\n", i, color(0), color(1), color(2));
		stream << buffer;
	}
	stream << "----------------------------------" << std::endl;
}

};