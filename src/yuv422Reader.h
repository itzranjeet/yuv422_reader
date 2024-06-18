#ifndef YUV422READER_H
#define YUV422READER_H

#include <C:\\opencv\\build\\include\\opencv2\\imgproc\\imgproc.hpp>
// #include <opencv2/highgui/highgui.hpp>

// #include <string>

class YUV422READER {
    public:
    std::string filename;
    void readImage();
};
#endif // YUV422READER_H