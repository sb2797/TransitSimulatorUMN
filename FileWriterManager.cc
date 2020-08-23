/**
 * @file IObservable.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/FileWriterManager.h"

FileWriter* File_Writer_Manager::getInstance() {
  return file_writer;
}
