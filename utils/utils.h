#pragma once
#include "../math/math.h"
#include <vector>
#include <string>

class ImageData {
public:
    std::vector<unsigned char> data;
    int height;
    int width;
    int nrChannels;

    ImageData(const std::string& path);
    ~ImageData();
};

std::string loadFile(const std::string& filename);
float randomFloat(float min, float max);
float clipToNearestIncrement(float value, float increment);
bool areFloatsEqual(float a, float b, float tolerance);
ImageData* load_image(const std::string& path);