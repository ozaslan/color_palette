#ifndef __COLOR_PALETTE_HH__
#define __COLOR_PALETTE_HH__

#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ros/package.h>
#include <ros/ros.h>

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

#include <Eigen/Dense>

using namespace std;
namespace fs = ::boost::filesystem;


class ColorPalette{
  private:
    double _min_idx, _max_idx;

    string _curr_palette_name;
    vector<Eigen::Vector3d> *_curr_palette;
    map<string, vector<Eigen::Vector3d> > _palettes;

    vector<fs::path> filenames;

    int _load_palettes(){
      _curr_palette_name = "<invalid>";
      _curr_palette      = NULL;
      _palettes.clear();

      fs::path root = fs::path(ros::package::getPath("color_palette"));
      root /= fs::path("palettes");
      string ext  = ".palette";

      ROS_INFO_STREAM("Reading color palettes from : " << root);

      if(!fs::exists(root) || !fs::is_directory(root)) return -1;

      fs::recursive_directory_iterator it(root);
      fs::recursive_directory_iterator endit;

      while(it != endit)
      {
        if(fs::is_regular_file(*it) && it->path().extension() == ext) 
          filenames.push_back(it->path());
        ++it;
      }

      for(auto f : filenames){
        ROS_INFO_STREAM("Loading paletter @ " << f.string() << " \\w stem : " << f.stem().string());
        ifstream ifs(f.string(), std::ifstream::in);
        while(ifs.good()){
          Eigen::Vector3d color;
          ifs >> color(0) >> color(1) >> color(2);
          _palettes[f.stem().string()].push_back(color);
        }
        ifs.close();
      }
    }

  public:
    ColorPalette(){
      _min_idx = 0;
      _max_idx = 1;
      _curr_palette_name = "<invalid>";
      _curr_palette      = NULL;
      _load_palettes();
    }

    inline int    set_min_idx(double min_idx){_min_idx = min_idx; return true;}
    inline double get_min_idx(){return _min_idx;}
    inline int    set_max_idx(double max_idx){_max_idx = max_idx; return true;}
    inline double get_max_idx(){return _max_idx;}

    inline int  set_palette(const string &palette){
      _curr_palette_name = palette;
      std::transform(_curr_palette_name.begin(), _curr_palette_name.end(), 
                      _curr_palette_name.begin(), ::tolower);
      auto palette_it = _palettes.find(_curr_palette_name);
      if(palette_it == _palettes.end()){
        _curr_palette_name = "<invalid>";
        _curr_palette = NULL;
        return -1;
      } else {
        _curr_palette = &(palette_it->second);
        return (int)_curr_palette->size();
      }
    }

    inline const string& get_palette(){return _curr_palette_name;}

    Eigen::Vector3d pick_color(double idx){
      Eigen::Vector3d color(0, 0, 0);
      if(_curr_palette == NULL)
        return color;

      // Size of the palette
      std::size_t size = _curr_palette->size();
      if(size == 0)
        return color;

      // Remapper index
      double index = (idx - _min_idx) / (_max_idx - _min_idx) * size;

      // Check if index is inside the extrema
      if(index <= 0)
        color = _curr_palette->front();
      else if(index >= size - 1)
        color = _curr_palette->back();
      else {
        double fractpart, intpart;
        fractpart = modf(index, &intpart);
        color = (*_curr_palette)[intpart] + ((*_curr_palette)[intpart + 1] - (*_curr_palette)[intpart]) * fractpart;
      }
      return color;
    }

    inline int get_palettes(vector<string> &palettes){
      palettes.clear();
      for(auto& it : _palettes) {
          palettes.push_back(it.first);
      }
    }

    inline int print(){
      print(_curr_palette_name);
    }

    inline int print(string palette){
      std::transform(palette.begin(), palette.end(), palette.begin(), ::tolower);
      auto it = _palettes.find(palette);
      if(it == _palettes.end()){
        cout << "Palette : <" << palette << "> not found" << endl;
        return -1;
      }

      cout << "Palette name : <" << palette << ">" << endl;
      for(std::size_t i = 0 ; i < it->second.size() ; i++){
        Eigen::Vector3d &c = it->second[i];
        cout << "[" << i << "] - {" << c(0) << ", " << c(1) << ", " << c(2) << "}" << endl; 
      }
    }
};


#endif
