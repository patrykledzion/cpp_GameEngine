#include "Image.h"

void nWindow::Image::OpenFile()
{
    if (this->filename.empty())return;

    std::ifstream file(this->filename.c_str(), std::fstream::binary);
    if (!file)
    {
        std::cerr << "Nie mo¿na otworzyæ pliku " << this->filename << std::endl;
    }

    //file.read(reinterpret_cast<char*>(&this->header), sizeof(BMPHeader)); 
    file.read(reinterpret_cast<char*>(&this->header.signature), 2); 
    file.read(reinterpret_cast<char*>(&this->header.fileSize), 4);
    file.read(reinterpret_cast<char*>(&this->header.reserved), 4);
    file.read(reinterpret_cast<char*>(&this->header.dataOffset), 4);
    file.read(reinterpret_cast<char*>(&this->header.headerSize), 4);
    file.read(reinterpret_cast<char*>(&this->header.width), 4);
    file.read(reinterpret_cast<char*>(&this->header.height), 4);
    file.read(reinterpret_cast<char*>(&this->header.planes), 2);
    file.read(reinterpret_cast<char*>(&this->header.bitsPerPixel), 2);
    file.read(reinterpret_cast<char*>(&this->header.compression), 4);
    file.read(reinterpret_cast<char*>(&this->header.imageSize), 4);
    file.read(reinterpret_cast<char*>(&this->header.xPixelsPerMeter), 4);
    file.read(reinterpret_cast<char*>(&this->header.yPixelsPerMeter), 4);
    file.read(reinterpret_cast<char*>(&this->header.colorsUsed), 4);
    file.read(reinterpret_cast<char*>(&this->header.importantColors), 4);
    if (this->header.signature[0] != 'B' || this->header.signature[1] != 'M')
    {
        file.close();
        return;
    }

    this->header.bitsPerPixel = this->header.bitsPerPixel >= 8 ? this->header.bitsPerPixel : this->header.bitsPerPixel * 8;


    bool hasAlpha = header.bitsPerPixel == 32; 

    int bytesPerPx = header.bitsPerPixel / 8;
    int rowSize = ((header.width * bytesPerPx + 3) / 4) * 4;
    int dataSize = rowSize * abs((int)header.height);

    char* _buffer = new char[dataSize];
    if (_buffer == nullptr)
    {
        file.close();
        return;
    }

    this->buffer = new char[dataSize];
    if (this->buffer == nullptr)
    {
        delete[] _buffer;
        return;
    }

    file.seekg(this->header.dataOffset);
    file.read((this->buffer), dataSize);
    file.close();

    int x = 2137;

    delete[] _buffer;
}

 

nWindow::Image::Image(std::string filename) : filename(std::move(filename))
{
    this->buffer = nullptr; 
    this->OpenFile();

    int x = 2137;

}

const char* nWindow::Image::GetImage()
{
    return reinterpret_cast<char*>( this->buffer);
}
