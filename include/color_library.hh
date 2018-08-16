#ifndef __COLOR_LIBRARY_HH__
#define __COLOR_LIBRARY_HH__

#include "color_palette.hh"

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>
namespace fs = ::boost::filesystem;

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include <Eigen/Dense>

//#include <iomanip>
//#include <algorithm>

/*
  This class consists of functions that generates
  colors similar those in Matlab's colormaps.
  There are a number of color palettes stored in text format 
  located under </palettes> folder within the package root directory.

  The user can use overloaded operators to get colors indexed
  by floating point indices. This basically interpolates between
  adjacent colors defined in the palette text files.

  At the first color query, all the palettes and colors therein
  are loaded into the static containers.
*/

namespace color_utils {
  class ColorLibrary{
  private:
    // Palette name - palette pairs.
    static std::map<std::string, ColorPalette> _palettes;
    // Root directory where <.palette> files are located.
    static fs::path _root_dir;
    // The last queried palette store for direct color queries.
    static ColorPalette *_active_palette;
    // This function goes to <_root_dir>, parses all of the 
    // files with extension <.palettel> and loads all the colors
    // from all palettes into the static memory.
    static void _loadColorPalettes();
  public:
    // This function set the root directory where all the 
    // <.palette> files are sitting. Upon setting this, this
    // funtion attempts to load all the palettes in the root folder.
    // It throws an exception in case the path is not valid.
    static void SetRoot(const fs::path &root_dir);
    // This behaves the same as <SetRoot> except that instead of a root directory
    // name of a ROS package. Note that the given package should be in the same 
    // workspace as this package.
    static void SetRootFromPackageName(const std::string &pkg_name);
    // This sets the <_active_palette> to enable direct color querying
    // without any need to deliberately specifying the palette name
    // during consecutive uses of the same palette. This throws an exception
    // if the palette name is correct, otherwise returns a const reference
    // to the corresponding color palette.
    static const ColorPalette& SetPalette(const std::string &palette_name);
    // This has the same behavious as <SetPalette(...)> except for that this
    // does not modify <_active_palette> and just returns the palette with
    // name <palette_name>.
    static const ColorPalette& GetPalette(const std::string &palette_name);
    // This returns the names of the available palettes.
    static std::vector<std::string> GetPaletteNames();
    // This works only when the active palette is already set using either 
    // <set_palette(...)> or <operator[](const std::string&)> functions. Otherwise
    // it won't pass the assert macro. If active palette is alrady set, this has the same 
    // effect as querying a color from that color palette.
    static const Color PickColor(float id);
    // This has the same effect as <Pick(float id)> except for that this allows
    // for choosing the palette. This does not modify <_active_palette>. 
    static const Color PickColor(const std::string &pname, float id);
    // This function prints the names and the number of colors of
    // available color palettes.
    static void Print();
    friend std::ostream& operator<<(std::ostream &stream, const ColorLibrary &picker) ;
  }; // class

}; // namespace
#endif
