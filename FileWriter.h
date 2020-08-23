/**
 * @file IObservable.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_FILEWRITERMANAGER_
#define SRC_FILE_WRITER_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class FileWriter {
  :
    void Write(std::string file_name, std::vector<std::string> csv_strings);
};

#endif SRC_FILEWRITERMANAGER_
