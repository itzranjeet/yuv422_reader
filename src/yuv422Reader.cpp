#include "yuv422Reader.h"

void YUV422READER::readImage()
{
    filename = "input\\Test_1.yuv";
    
     Mat source, bird_eye_view, destination2, destination3, gray_image, gray_image_;
        std::string filename = folder + Files[i];
        //load image
        source = imread(filename, CV_LOAD_IMAGE_COLOR);
        // check if image is corrupted
        if (!source.data)
        {
            std::cout << "Could not open or find the image" << std::endl;
        }
}

int main()
{
    YUV422READER yr;
    yr.readImage();
}