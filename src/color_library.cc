#include "color_library.hh"

#include "boost_assert_helper.hpp" // This has to come first due to a define macro
#include <boost/assert.hpp>

#include <ros/package.h> // This is in <roslib>

#include <iomanip>

namespace color_utils{

	std::map<std::string, ColorPalette> ColorLibrary::_palettes;
	fs::path ColorLibrary::_root_dir = "";
	ColorPalette * ColorLibrary::_active_palette = NULL;

	void ColorLibrary::_loadColorPalettes(){

		_palettes.clear();

		fs::path    root(_root_dir);
		std::string ext(".palette");

		std::cout << "Searching for files with <.palette> extension at <" << root << ">" << std::endl;

		if( !fs::exists(root) ){
			std::stringstream ss;
			ss << "In ColorLibrary::" << __FUNCTION__ << ", ";
			ss << "root directory <" << root.string() << "> does not exist ";
			ss << "at file : " << __FILE__ << " line " << __LINE__;
			throw ss.str();
		} else if( !fs::is_directory(root) ) {
			std::stringstream ss;
			ss << "In ColorLibrary::" << __FUNCTION__ << ", ";
			ss << "path <" << root.string() << "> is not a directory ";
			ss << "at file : " << __FILE__ << " line " << __LINE__;
			throw ss.str();
		}

		fs::recursive_directory_iterator it(root);
		fs::recursive_directory_iterator endit;

		while(it != endit){

			std::cout << " - found : <" << *it << ">" << std::endl;

			if(fs::is_regular_file(*it) && it->path().extension() == ext) {
				std::string palette_name = it->path().stem().string();
        		// This either pulls the exising palette or initializes a new one.
				ColorPalette &cp = _palettes[palette_name];
				cp.loadFromFile(it->path());
			}

			++it;
		}
	}

	void ColorLibrary::SetRoot(const fs::path &root_dir){

		_root_dir = root_dir;
		_loadColorPalettes();
	}

	void ColorLibrary::SetRootFromPackageName(const std::string &pkg_name){
		_root_dir = ros::package::getPath(pkg_name);
		_root_dir /= "palettes";
		_loadColorPalettes();
	}

	const ColorPalette& ColorLibrary::SetPalette(const std::string &palette_name){

		std::string pname = palette_name;
		std::transform(pname.begin(), pname.end(), pname.begin(), ::tolower);
		_active_palette = &_palettes.at(pname);
		return *_active_palette;
	}

	const ColorPalette& ColorLibrary::GetPalette(const std::string &palette_name){

		std::string pname = palette_name;
		std::transform(pname.begin(), pname.end(), pname.begin(), ::tolower);
		return _palettes.at(pname);
	}

	std::vector<std::string> ColorLibrary::GetPaletteNames(){
		std::vector<std::string> palette_names;

		for(const auto it : _palettes){
			palette_names.push_back(it.first);
		}

		return palette_names;
	}

	const Color ColorLibrary::PickColor(float id){

		BOOST_ASSERT_MSG( _active_palette != NULL, "<_active_palette> is not set yet.");
		return _active_palette->operator[](id);
	}

	const Color ColorLibrary::PickColor(const std::string &pname, float id){
		return GetPalette(pname).operator[](id);
	}

	void ColorLibrary::Print(){
		std::cout << std::endl;
		std::cout << "= Available palettes are : ============" << std::endl;
		for( auto it : _palettes ){
			std::cout << "[ ";
			std::cout << std::internal << std::setw(10) << it.first;
			std::cout << " ] - size : [ " << it.second.size() << " ]" << std::endl;
		}
		std::cout << "=======================================" << std::endl;
		std::cout << std::endl;
	}

	std::ostream& operator<<(std::ostream &stream, const ColorLibrary &picker){
		stream << std::endl;
		stream << "= Available palettes are : ============" << std::endl;
		for( auto it : picker._palettes ){
			stream << "[ ";
			stream << std::internal << std::setw(10) << it.first;
			stream << " ] - size : [ " << it.second.size() << " ]" << std::endl;
		}
		stream << "=======================================" << std::endl;
		stream << std::endl;	
	}

}; // namespace