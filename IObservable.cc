/**
 * @file IObservable.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#include <iostream>
#include <string>
#include "src/IObservable.h"


//Attach an Observer to this Observable

/*template <typename T> void IObservable<T>::RegisterObserver(IObserver<T>* Observer){
  observer_.push_back(Observer);
}

//Remove all Observers from this Observable
template <typename T> void IObservable<T>::ClearObservers(){
  observer_.clear(); 
}

//Notify All Observers attached to this Observable
template <typename T> void IObservable<T>::NotifyObservers(T info){
  for(typename vector<IObserver<T>*>::const_iterator iter = observer_.begin();
                                            iter != observer_.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->Notify(info);
        }
    } 
*/
