# Color Utilities

This ROS package provides various color palettes that can be used to generate nice & distinctive colors for plotting.


### Prerequisites

This ROS package depends on Eigen and OpenCV. The test application plots all the color palettes available on an OpenCV image (cv::Mat). Hence, OpenCV dependcy is not crucial. Both libraries come with ROS installation.

### Installing

Simply clone the repository into your workspace with 

```
git clone https://github.com/ozaslan/color_utils
```

## Running the tests

Run the test code to see if all the color palettes are set up properly with
```
rosrun color_utils test_color_library
```

This shoud dump a lot of text on the command prompt consisting of available palette names, their paths and number of colors defined (note that you can interpolate between colors).

This image show the available colors:

<p align="center">
  <img src="https://github.com/ozaslan/color_utils/blob/master/images/palettes.png">
</p>

## Acknowledgments

This library copies both the names and the colors of [Matlab 'colormap'][1]

[1]: https://www.mathworks.com/help/matlab/ref/colormap.html