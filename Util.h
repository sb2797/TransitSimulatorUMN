#ifndef SRC_UTIL_
#define SRC_UTIL_

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Util {
  public:
    std::vector<std::string> processOutput(std::ostringstream& out_stream);
};

#endif
