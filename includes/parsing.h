#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>

#include "logs.h"
#include "vector.h"
#include "matrix.h"

struct ObjectFileDatas
{
  std::vector<Vector4> vertices;
  std::vector<unsigned int> indices;
};

#pragma pack(push, 1)
struct BMPFileHeader
{
  uint16_t fileType; // 'BM'
  uint32_t fileSize;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t dataOffset;
};

struct BMPInfoHeader
{
  uint32_t headerSize;
  int32_t width;
  int32_t height;
  uint16_t planes;
  uint16_t bitsPerPixel;
  uint32_t compression;
  uint32_t imageSize;
  int32_t xPixelPerMeter;
  int32_t yPixelPerMeter;
  uint32_t colorUsed;
  uint32_t importantColors;
};
#pragma pack(pop)

struct ParsedBMPDatas
{
  const int width;
  const int height;
  std::vector<unsigned char> pixels;
};

std::string readFileToString(std::string filePath);
ObjectFileDatas readObjectFile(std::string filePath);
ParsedBMPDatas parseBmpFile(std::string filePath, bool flipY = false);
std::vector<std::string> getObjFiles();
