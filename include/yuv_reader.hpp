#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
// #include "./../../../../../usr/include/opencv4/opencv2/opencv.hpp"

class YUVREADER
{
public:
    // PATHS
    std::string in_yuv_file = "/home/smartap/yuv422_reader-main/input/1.yuv";
    std::string csv_filename = "/home/smartap/yuv422_reader-main/input/1.csv";
    std::string op_yuv_file = "/home/smartap/yuv422_reader-main/input/2.yuv";

    void readYUV();
    void writeCSV(int, char *, std::string);
    void writeYUV();
    void uyvyToRGBA8888(unsigned char *, unsigned char *, int, int);
};
