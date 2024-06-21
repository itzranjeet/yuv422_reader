#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class YUVREADER
{
public:
    // PATHS
    std::string in_yuv_file = "/home/kpit/ranjeetp1/YUV_422_Reader/1.yuv";
    std::string csv_filename = "/home/kpit/ranjeetp1/YUV_422_Reader/1.csv";
    std::string op_yuv_file = "/home/kpit/ranjeetp1/YUV_422_Reader/2.yuv";

    void readYUV();
    void writeCSV(int, char *, std::string);
    void writeYUV();
};