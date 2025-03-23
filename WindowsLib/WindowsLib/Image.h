#pragma once
#include <iostream>
#include <fstream>
#include <cmath>

namespace nWindow {

	typedef struct {
        char signature[2]; // "BM"
        uint32_t fileSize;
        uint32_t reserved;
        uint32_t dataOffset;
        uint32_t headerSize;
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bitsPerPixel;
        uint32_t compression;
        uint32_t imageSize;
        uint32_t xPixelsPerMeter;
        uint32_t yPixelsPerMeter;
        uint32_t colorsUsed;
        uint32_t importantColors;
	} BMPHeader;

	class Image
	{
	private:
        std::string filename;
        BMPHeader header;

		void OpenFile(); 

	public:

        char* buffer;
		Image(std::string filename);
		const char* GetImage();
        std::pair<int, int> GetSize() { return std::make_pair(this->header.width, this->header.height); }

	};
}
