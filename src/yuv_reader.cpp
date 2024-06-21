#include </home/kpit/ranjeetp1/YUV_422_Reader/include/yuv_reader.hpp>

void YUVREADER::readYUV()
{
    std::ifstream is(in_yuv_file, std::ifstream::binary);
    if (is)
    {
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);
        char *buffer = new char[length];
        std::cout << "Reading " << length << " characters... ";
        is.read(buffer, length);
        if (is)
            std::cout << "all characters read successfully.";
        else
            std::cout << "error: only " << is.gcount() << " could be read";
        is.close();

        // BMDPixelFormat enumerates the pixel formats supported for output and input.
        // bmdFormat8BitYUV: "UYVY' 4:2:2 Representation
        // Four 8-bit unsigned components (CCIR 601) are packed into one 32-bit little-endian word.
        //         Word
        // Decreasing Address Order
        // Byte 3      Byte 2     Byte 1		Byte 0
        // Y1		Cr 0		YO	Cb 0
        // 76543210 76543210 76543210 76543210
        // int framesize = (Width 16/8) Height rowbytes Height
        // In this format, two pixels fit into 32 bits or 4 bytes, so one pixel fits into 16 bits or 2 bytes.
        // For the row bytes calculation, the image width is multiplied by the number of bytes per pixel.
        //  For the frame size calculation, the row bytes are simply multiplied by the number of rows in the frame.
        writeCSV(length, buffer, csv_filename);
        delete[] buffer;
    }
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
            // char ch = static_cast<char>(value);
            op_yuv << static_cast<char>(value);
            count++;
        }
    }
    csv_file.close();
    op_yuv.close();
    std::cout << count << " all characters read successfully." << std::endl;
}

int main()
{
    YUVREADER obj;
    // obj.readYUV();
    obj.writeYUV();
    return 0;
}
