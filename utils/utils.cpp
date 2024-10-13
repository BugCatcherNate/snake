#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <vector>
#include <memory>
#include "stb_image.h"
#include "utils.h"

// Implementation of ImageData constructor and destructor
ImageData::ImageData(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* tempData = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (tempData)
    {
        std::cout << "Loaded Image" << std::endl;
        data.assign(tempData, tempData + (width * height * nrChannels));
        stbi_image_free(tempData);
    }
    else
    {
        std::cerr << "Image Load Failed" << std::endl;
    }
}

ImageData::~ImageData()
{
    // No need to free data as std::vector manages its own memory
}

// Implementation of loadFile function
std::string loadFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}