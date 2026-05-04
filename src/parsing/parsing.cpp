#include "parsing.h"

std::string readFileToString(std::string filePath)
{
  std::ifstream file;
  std::string line;
  std::string resFile;

  file.open(filePath);

  if (!file.is_open())
  {
    logError("ERROR::FILE::READING::CAN'T_OPEN_FILE:", filePath);

    if (file.bad())
    {
      logError("/!\\ BADBIT ERROR /!\\");
    }

    if (file.fail())
    {
      logErrorInfo(strerror(errno));
    }

    throw -300;
  }

  while (std::getline(file, line))
  {
    resFile += line + "\n";
  }

  file.close();

  return resFile + "\0";
}

void readVerticeLine(std::string line, std::vector<Vector4> *vertices)
{
  std::string number;
  float vertice[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  int coordIndex = 0;
  for (long unsigned int i = 2; i <= line.size(); i++)
  {
    if ((line[i] == ' ' && line[i - 1] != ' ') || i == line.size())
    {
      if (coordIndex > 3)
      {
        logError("ERROR::FILE::READING::MISS_FORMATED_OBJ_FILE:", "too much float for a vertice");

        throw -300;
      }
      vertice[coordIndex] = std::stof(number);
      coordIndex++;
      number.clear();
    }
    else
    {
      number.push_back(line[i]);
    }
  }

  vertices->push_back(Vector4(vertice));
}

void readIndicesLine(std::string line, std::vector<unsigned int> *indices)
{
  std::string number;
  std::vector<unsigned int> faceIndices;

  for (long unsigned int i = 2; i <= line.size(); i++)
  {
    if (line[i] == '/')
    {
      logError("ERROR::PARSING::READ_INDICES_LINE:", "Parsing of obj file does not handle texture incoded files. Please provide only vertices and indices.");
      return ;
    }
    if ((line[i] == ' ' && line[i - 1] != ' ') || i == line.size())
    {
      faceIndices.push_back(std::stoi(number) - 1);
      number.clear();
    }
    else
    {
      number.push_back(line[i]);
    }
  }

  for (long unsigned int i = 1; i + 1 < faceIndices.size(); i++)
  {
    indices->push_back(faceIndices[0]);
    indices->push_back(faceIndices[i]);
    indices->push_back(faceIndices[i + 1]);
  }
}

ObjectFileDatas readObjectFile(std::string filePath)
{
  std::ifstream file;
  std::string line;
  std::vector<Vector4> vertices;
  std::vector<unsigned int> indices;

  file.open(filePath);

  if (!file.is_open())
  {
    logError("ERROR::FILE::READING::CANNOT_OPEN_FILE", filePath);

    if (file.bad())
    {
      logError("/!\\ BADBIT ERROR /!\\");
    }

    if (file.fail())
    {
      logErrorInfo(strerror(errno));
    }

    throw -300;
  }

  while (std::getline(file, line))
  {
    if (line[0] == 'v' && line[1] == ' ')
    {
      readVerticeLine(line, &vertices);
    }
    else if (line[0] == 'f' && line[1] == ' ')
    {
      readIndicesLine(line, &indices);
      if (indices.empty())
      {
        logError("ERROR::PARSING::READ_OBJECT_FILE:", "Could not parse indices in " + filePath);
        throw -300;
      }
    }
  }

  file.close();

  Vector4 centroid(0.0f, 0.0f, 0.0f, 0.0f);

  for (Vector4 v : vertices)
    centroid = centroid + v;

  centroid.X /= vertices.size();
  centroid.Y /= vertices.size();
  centroid.Z /= vertices.size();

  for (Vector4 &v : vertices)
  {
    v.X -= centroid.X;
    v.Y -= centroid.Y;
    v.Z -= centroid.Z;
  }

  return {vertices, indices};
}

ParsedBMPDatas parseBmpFile(std::string filePath, bool flipY)
{
  std::ifstream file(filePath, std::ios::binary);

  if (!file)
  {
    logError("ERROR::PARSING::BMP:", "could not open file");
    throw -300;
  }

  BMPFileHeader fileHeader;
  // reinterpret_cast treat fileHeader memory as a raw sequence of bytes
  // and file.read need it to be char *
  file.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
  // Check if header is a BMP header (0x4D42 = 'BM' little-endian)
  if (fileHeader.fileType != 0x4D42)
  {
    logError("ERROR::PARSING::BMP:", filePath + " is not a BMP file");
    throw -300;
  }

  BMPInfoHeader infoHeader;
  file.read(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));
  if (infoHeader.bitsPerPixel != 24 || infoHeader.compression != 0)
  {
    logError("ERROR::PARSING::BMP:", "format not supported\nSupported format is uncompressed 24-bit color BMP file");
    const char *compression = infoHeader.compression == 1 ? "compressed file" : "uncompressed file";
    logErrorInfo(filePath + " --> " + std::to_string(infoHeader.bitsPerPixel) + " bits per pixel " + compression);
    throw -300;
  }

  // infoHeader.width * 3 = real pixels size. But BMP wants mutiple of 4
  // + 3 making sure we round up and not down to keep all informations
  // & ~3 binary trick to clear last two bits as ~3 = 11111100
  int rowSize = (infoHeader.width * 3 + 3) & ~3;
  int width = infoHeader.width;
  int height = std::abs(infoHeader.height);
  // Allocating pixel Buffer for OpenGL specificity
  std::vector<unsigned char> pixels(width * height * 3);
  std::vector<unsigned char> row(rowSize);

  // placing cursor at the start of pixels by using dataOffset from the beging of file
  file.seekg(fileHeader.dataOffset, std::ios::beg);

  for (int y = 0; y < height; y++)
  {
    file.read(reinterpret_cast<char *>(row.data()), rowSize);
    for (int x = 0; x < width; x++)
    {
      int bmpIndex = x * 3;
      // Flip image vertically (BMP is bottom to up != OpenGL) and get rid of padding
      int glIndex = flipY ? ((height - 1 - y) * width + x) * 3 : (y * width + x) * 3;

      // Flip BGR to RGB for OpenGL
      pixels[glIndex + 0] = row[bmpIndex + 2]; // R
      pixels[glIndex + 1] = row[bmpIndex + 1]; // G
      pixels[glIndex + 2] = row[bmpIndex];     // B
    }
  }

  return {width, height, pixels};
}

std::vector<std::string> getObjFiles()
{
  std::vector<std::string> objFiles;

  for (const auto &entry : std::filesystem::directory_iterator("./resources/objects"))
  {
    if (entry.path().extension() == ".obj")
      objFiles.push_back(entry.path().string());
  }

  return objFiles;
}
