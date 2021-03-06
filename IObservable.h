/**
 * @file IObservable.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_IOBSERVABLE_H_
#define SRC_IOBSERVABLE_H_
#include <src/IObserver.h>
#include <iostream>
#include <string>
using namespace std;
template <typename T>

/**
 *@brief Observable class used to Attach, Detach, and Notify Observers
 */
class IObservable {
 public:
  void RegisterObserver(IObserver<T>* Observer);
  void ClearObservers();
  void NotifyObservers(T info);

 private:
  std::vector<IObserver<T>*> observer_;
};
template <typename T>
void IObservable<T>::RegisterObserver(IObserver<T>* Observer) {
  observer_.push_back(Observer);
}

// Remove all Observers from this Observable
template <typename T> void IObservable<T>::ClearObservers() {
observer_.clear(); 
}

// Notify All Observers attached to this Observable
template <typename T> void IObservable<T>::NotifyObservers(T info) {
  for (typename vector<IObserver<T>*>::const_iterator iter = observer_.begin();
        iter != observer_.end(); ++iter) {
        if(*iter != 0) {
           (*iter)->Notify(info);
        }
    } 
}
#endif  // SRC_IOBSERVABLE_H_
