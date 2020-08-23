/**
 * @file IObserver.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_IOBSERVER_H_
#define SRC_IOBSERVER_H_
#include <src/data_structs.h>

/**
 *@brief Abstract Observer class used to report on data from observables
 */
template <typename T>
class IObserver {
 public:
    virtual void Notify(T info) = 0;
};
#endif // SRC_IOBSERVER_H_
