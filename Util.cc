/**
 * @file visualization_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "Util.h"


std::vector<std::string> Util::processOutput(std::ostringstream& out_stream) {
  std::vector<std::string> string_vector;
  std::string output = " ";
  std::string seperate = ",";
  std::string temp_string = " ";
  output = out_stream.str();

  int start = 0;
  int length = 0;
  for (int i = 0; i < output.length(); i++) {
    if (output.at(i) == ' ') {
      length = i - start;
      temp_string = output.substr(start, length);
      temp_string.append(seperate);
      string_vector.push_back(temp_string);
      start = i + 1;
    }
  }
  return string_vector;
}
