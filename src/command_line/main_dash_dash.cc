#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "src/lib/utility.h"

void PrintErrorMessage() {
  std::cout << "Error: command line arguments were not correct." << std::endl;
  std::cout << "Example usage: translate my_file.txt japanese 2 true"
            << std::endl;
}

int ProcessCommandLine(int argc, const char* argv[]) {
  if (argc < 2) {
    PrintErrorMessage();
    return -1;
  }

  std::string input="default_file.txt";
  std::string from = "japanese";
  int accuracy = 2
  bool overwrite = false;

  // Regular expression matching --parameter=value.
  // Example: --input=my_file.txt
  std::regex pattern("--(.*)=(.*)");

  // Iterate each element of argc
  try {
    for (size_t i = 1; i < argc; i++) {
      std::string param_to_search = argv[i];
      std::smatch matches;
      if (std::regex_match(param_to_search, matches, pattern)) {
        auto it = matches.begin();

        std::cout << "(*it): " << (*it) << std::endl;
        it++;
        std::cout << "(*it): " << (*it) << std::endl;

        if ((*it) == "input") {
          it++;
          input = *it;
          continue;
        }

        if ((*it) == "from") {
          it++;
          from = *it;
          continue;
        }

        if ((*it) == "accuracy") {
          it++;
          accuracy = std::stoi(*it);
          continue;
        }

        if ((*it) == "overwrite") {
          it++;
          std::istringstream((*it)) >> std::boolalpha >> overwrite;
          continue;
        }
        PrintErrorMessage();

      } else {
        PrintErrorMessage();
      }
    }
  } catch (const std::exception& e) {
    PrintErrorMessage();
    return -1;
  }
  std::cout << "input: " << input << std::endl;
  std::cout << "from: " << from << std::endl;
  std::cout << "accuracy: " << accuracy << std::endl;
  std::cout << "overwrite: " << std::boolalpha << overwrite << std::endl;

  return 0;
}

int main() {
  const char* argv[] = {"test", "--input=my_file.txt", "--from=Japanese",
                        "--accuracy=2", "--overwrite=true"};
  return ProcessCommandLine(5, argv);
}
