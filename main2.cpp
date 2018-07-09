/* 
 * File:   main1.cpp
 * Author: ducnt
 *
 * Created on July 9, 2018, 2:29 PM
 */

#include <iostream>
#include <string>
#include <sstream>
#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "Poco/AutoPtr.h"

using Poco::Notification;
using Poco::NotificationQueue;
using Poco::ThreadPool;
using Poco::Runnable;
using Poco::AutoPtr;

class WorkNotification : public Notification {
public :
    WorkNotification(int idata) : _iData(idata) {
        _sData = "work " + _iData;
        std::cout << "construct WorkNotification " << _iData << std::endl;
    }

    int data() const {
        return _iData;
    }
    std::string getsData() const{
        return _sData;
    }
private:
    int _iData;
    std::string _sData;
};

class Worker : public Runnable { 
public :
    Worker(NotificationQueue & queue, std::string workerName) : _queue(queue), _name(workerName) {
        std::cout << "construct Worker " << std::endl;
    }

    void run() {
        AutoPtr<Notification> pNf(_queue.waitDequeueNotification()); //
        while (pNf) {
            WorkNotification* pWorkNf = dynamic_cast<WorkNotification*>(pNf.get());
            if (pWorkNf) {
                std::cout << this->_name << " Worker is working... " << pWorkNf->data() << std::endl;
//                Poco::Thread::sleep(100);
                std::cout << "----" << this->_name << " " << pWorkNf->data() << " " << pWorkNf->getsData() << std::endl;
                std::cout << this->_name << " Worker has finished " << std::endl;
            } else {
                return;
            }
            pNf = _queue.waitDequeueNotification();
        }
    }
private:
    NotificationQueue& _queue;
    std::string _name;
};

int main(int argc, char** argv) {
    NotificationQueue queue;
    
    // create worker threads
    Worker worker1(queue,"Worker1"); 
    Worker worker2(queue,"Worker2");
    Worker worker3(queue,"Worker3");
    
    // start workers
    ThreadPool::defaultPool().start(worker1); 
    ThreadPool::defaultPool().start(worker2);
    ThreadPool::defaultPool().start(worker3);
    
    // create some work
    std::cout << "Create some tasks for workers" << std::endl;
    for (int i = 0; i < 100; ++i) {
        queue.enqueueNotification(new WorkNotification(i));
    }
    std::cout << "Create tasks finish" << std::endl;
    
    // wait until all work is done
    while (!queue.empty()){ 
        Poco::Thread::sleep(100);
    }
    
    // tell workers they're done
    queue.wakeUpAll(); 
    
    ThreadPool::defaultPool().joinAll();
    
    std::cout << "DONE" << std::endl;
    return 0;
}