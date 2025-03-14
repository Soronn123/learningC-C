#include <windows.h>
#include <fstream>


int main()
{
    const char* image_name = "imageconvernet123124312412.png";
    try{
        std::fstream image;
        image.open( image_name , std::ios::binary | std::ios::out );

        const char buf[121] = "\x89PNG\r\n\x1a\n\x00\x00\x00\rIHDR\x00\x00\x00\x01\x00\x00\x00\x01\x08\x06\x00\x00\x00\x1f\x15\xc4\x89\x00\x00\x00\x01sRGB\x00\xae\xce\x1c\xe9\x00\x00\x00\x04gAMA\x00\x00\xb1\x8f\x0b\xfc\x61\x05\x00\x00\x00\tpHYs\x00\x00\x0e\xc3\x00\x00\x0e\xc3\x01\xc7o\xa8\x64\x00\x00\x00\rIDAT\x18Wc```\xf8\x0f\x00\x01\x04\x01\x00p e\x0b\x00\x00\x00\x00IEND\xae\x42\x60\x82";
        image.write( buf, sizeof buf );
        image.close();
        SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (char *)image_name, 0);
        std::remove(image_name);
    }
    catch(...){ }
    return 0;
}