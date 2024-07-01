#include "/home/kpit/ranjeetp1/YUV_422_Reader/include/yuv_reader.hpp"

void YUVREADER::readYUV()
{
    std::ifstream is(in_yuv_file, std::ifstream::binary);
    if (is)
    {
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        char *buffer = new char[length];
        char *rgbaData_ = new char[length * 2];
        std::cout << "Reading " << length << " characters... ";
        is.read(buffer, length);
        if (is)
            std::cout << "all characters read successfully.\n";
        else
            std::cout << "error: only " << is.gcount() << " could be read";
        is.close();

        // BMDPixelFormat enumerates the pixel formats supported for output and input.
        // bmdFormat8BitYUV: "UYVY' 4:2:2 Representation
        // Four 8-bit unsigned components (CCIR 601) are packed into one 32-bit little-endian word.
        //         Word
        // Decreasing Address Order
        // Byte 3      Byte 2     Byte 1                Byte 0
        // Y1           Cr 0            YO      Cb 0
        // 76543210 76543210 76543210 76543210
        // int framesize = (Width 16/8) Height rowbytes Height
        // In this format, two pixels fit into 32 bits or 4 bytes, so one pixel fits into 16 bits or 2 bytes.
        // For the row bytes calculation, the image width is multiplied by the number of bytes per pixel.
        //  For the frame size calculation, the row bytes are simply multiplied by the number of rows in the frame.
        unsigned char *uyvyData = (unsigned char *)(buffer);
        unsigned char *rgbaData = (unsigned char *)(rgbaData_);

        uyvyToRGBA8888(uyvyData, rgbaData, 176, 144);
        // writeCSV(length, buffer, csv_filename);
        delete[] buffer;
        delete[] rgbaData_;
    }
    else
        std::cout << "File is not available" << std::endl;
}

void YUVREADER::writeCSV(int len_, char *buf_, std::string csv_filename)
{
    std::ofstream csv_file;
    csv_file.open(csv_filename);
    for (size_t i = 0; i < len_; i++)
    {
        for (size_t row = 0; row < (len_ / 16); row++)
        {
            for (size_t col = 0; col < 16; col++)
            {
                if (col == 15)
                {
                    csv_file << std::hex << (uint16_t)buf_[i];
                }
                else
                {
                    csv_file << std::hex << (uint16_t)buf_[i] << ",";
                }
                i++;
            }
            csv_file << "\n";
        }
    }
    csv_file.close();
}

void YUVREADER::writeYUV()
{
    std::ofstream op_yuv;
    op_yuv.open(op_yuv_file, std::ofstream::out | std::ofstream::app);

    std::ifstream csv_file(csv_filename);
    std::string line;
    int count = 0;
    while (std::getline(csv_file, line))
    {
        std::string val;
        std::stringstream s(line);
        while (std::getline(s, val, ','))
        {
            int value;
            std::stringstream str;
            str << val;
            str >> std::hex >> value;
            op_yuv << static_cast<char>(value);
            count++;
        }
    }
    csv_file.close();
    op_yuv.close();
    std::cout << count << " all characters read successfully." << std::endl;
}

void YUVREADER::uyvyToRGBA8888(unsigned char *uyvyData, unsigned char *rgbaData, int width, int height)
{
    FILE *fp = fopen("rgba.png", "wb");
    int rgba_index = 0;
    for (int i = 0; i < width * height * 4 * 3; i += 4)
    {
        unsigned char u = uyvyData[i + 0];
        unsigned char y1 = uyvyData[i + 1];
        unsigned char v = uyvyData[i + 2];
        unsigned char y2 = uyvyData[i + 3];

        int c = y1 - 16;
        int d = u - 128;
        int e = v - 128;

        rgbaData[rgba_index++] = std::max(0, std::min(255, (298 * c + 409 * e + 128) >> 8));           // R
        rgbaData[rgba_index++] = std::max(0, std::min(255, (298 * c - 100 * d - 208 * e + 128) >> 8)); // G
        rgbaData[rgba_index++] = std::max(0, std::min(255, (298 * c + 516 * d + 128) >> 8));           // B
        rgbaData[rgba_index++] = 255;                                                                  // A
        c = y2 - 16;

        rgbaData[rgba_index++] = std::max(0, std::min(255, (298 * c + 409 * e + 128) >> 8));           // R
        rgbaData[rgba_index++] = std::max(0, std::min(255, (298 * c - 100 * d - 208 * e + 128) >> 8)); // G
        rgbaData[rgba_index++] = std::max(0, std::min(255, (298 * c + 516 * d + 128) >> 8));           // B
        rgbaData[rgba_index++] = 255;                                                                  // A
    }
    svpng(fp, 176, 144, rgbaData, 1);
    fclose(fp);
}

int main()
{
    YUVREADER obj;
    obj.readYUV();
    // obj.writeYUV();
    return 0;
}
