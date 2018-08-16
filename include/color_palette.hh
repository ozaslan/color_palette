#ifndef __COLOR_PALETTE_HH__
#define __COLOR_PALETTE_HH__


#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>
namespace fs = ::boost::filesystem;

#include <vector>
#include <string>
#include <iostream>

#include <Eigen/Dense>

namespace color_utils {

  /*
    This class defines a single color palette populated
    using one of the palette definitions given in text 
    format under </palettes> folder.
  */

  typedef Eigen::Vector3f Color;

  class ColorPalette {
  private:
    static const uint32_t __init_size = 100;
    // Name of the palette.
    std::string _name;
    // Ordered array of colors.
    std::vector<Eigen::Vector3f> _colors;
  public:
    ColorPalette();
    ColorPalette(const std::string& path);
    // This function loads the palette file at <path>. If the given
    // path does not exists, it throws an exception.
    uint32_t loadFromFile(const fs::path &path);
    uint32_t loadFromFile(const std::string& path);
    // This function accepts a coordinate <idx> in [0, 1] range and
    // returns a color interpolated from the internally stored color
    // points. This throws an exception if the index is out of [0, 1].
    Color operator[](float idx) const;
    // This function prints the colors in RGB format on the command prompt.
    void print() const;
    friend std::ostream& operator<<(std::ostream &stream, const ColorPalette &palette) ;
    // This function returns the number of colors.
    inline uint32_t size() const{ return _colors.size(); }
    // Getter function for <name>
    const std::string & name() const {return _name;}
  }; // class
}; // namespace

#endif
