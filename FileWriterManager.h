/**
 * @file IObservable.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_FILEWRITERMANAGER_H_
#define SRC_FILE_WRITER_MANAGER_

#include "src/FileWriter.h"


class File_Writer_Manager {
 public:
    FileWriter* getInstance();
 private:
      FileWriter* file_writer = new FileWriter();
};
#endif  // SRC_FILEWRITERMANAGER_H_
