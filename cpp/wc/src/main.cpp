#include "wc.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  const std::string filename = argv[1];
  std::ifstream file(filename);

  if (!file) {
    std::cerr << "Error opening file '" << filename << "': "
      << std::strerror(errno) << std::endl;
    return 1;
  }

  size_t totalWords = 0;
  std::string line;

  try {
    while(std::getline(file, line)) {
      totalWords += WordCounter::countWords(line);
    }

    if (file.bad()) {
      throw std::runtime_error("Error reading file");
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  std::cout << "Word count: " << totalWords << std::endl;

  return 0;

}
