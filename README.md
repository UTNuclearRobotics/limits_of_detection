# Limits of Detection Library
A library that calculates the limits of detection, dwell time, and alpha detector velocity.  This information is used for assessing the presence of alpha emitting material on a surface. ROS/ROS2 independent, only a C++ library.  

# Installation
To install the package, first clone or download the repository to your computer. From here on, we will assume that you are cloning using an ssh key as authentification.
```bash
git clone git@github.com:UTNuclearRobotics/limits_of_detection.git
```
Then navigate into the reo and create a /build folder. From this folder we can invoke cmake to compile the library.
```bash
cd limits_of_detection
mkdir build && cd build
cmake .. && make -j
```
Now that the library is compiled, you can test the example program 
```bash
./limits_of_detection
```

If you want to install the library so it can easiliy be used with other cmake or catkin/colcon projects, run the following command under the /build directory
```bash
sudo make install
```

