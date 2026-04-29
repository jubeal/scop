#include "logs.h"

// display message with red for error and no color for datas
void logError(std::string message, std::string datas)
{
  std::cerr << "\033[1;31m" << message << " \033[0m" << datas << std::endl;
}

void logError(std::string message)
{
  std::cerr << "\033[1;31m" << message << std::endl;
}

void logErrorInfo(std::string message)
{
  std::cerr << "Error details: " << message << std::endl;
}