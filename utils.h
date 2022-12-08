#include <fstream>

#include <vector>
#include <string>

std::vector<std::string> load_data(const std::string & fileName)
{
std::vector<std::string> lines;
  std::string line;
  std::ifstream file(fileName);

  if (file.is_open()) {
    while (getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  }

  return lines;
}