/**
 * @file IObservable.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/FileWriter.h"

void FileWriter::Write(std::string file_name,
std::vector<std::string> csv_strings) {
std::ofstream myFile;
myFile.open (file_name);
for (int i = 0; i < csv_strings.size(); i++) {
    myFile << csv_strings[i];
  }
  myFile.close();
}
