/* 
 * File:   main1.cpp
 * Author: ducnt
 *
 * Created on July 9, 2018, 2:29 PM
 */

#include <iostream>
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

class WorkNotification : public Notification{
public :
    WorkNotification(int data) : _data(data) {
        std::cout << "construct WorkNotification " << data << std::endl;
    }

    int data() const {
        return _data;
    }
private:
    int _data;
};

class Worker : public Runnable { 
public :
    Worker(NotificationQueue & queue) : _queue(queue) {
        std::cout << "construct Worker " << std::endl;
    }

    void run() {
        AutoPtr<Notification> pNf(_queue.waitDequeueNotification()); //
        while (pNf) {
            WorkNotification* pWorkNf = dynamic_cast<WorkNotification*>(pNf.get());
            if (pWorkNf) {
                std::cout << "Worker is working..." << std::endl;
//                Poco::Thread::sleep(100);
                std::cout << "Worker has finished" << std::endl;
            }
            pNf = _queue.waitDequeueNotification();
        }
    }
private:
    NotificationQueue& _queue;
};

int main(int argc, char** argv) {
    NotificationQueue queue;
    Worker worker1(queue); // create worker threads
    Worker worker2(queue);
    Worker worker3(queue);
    ThreadPool::defaultPool().start(worker1); // start workers
    ThreadPool::defaultPool().start(worker2);
    ThreadPool::defaultPool().start(worker3);
    // create some work

    std::cout << "create some tasks for workers" << std::endl;
    for (int i = 0; i < 100; ++i) {
        queue.enqueueNotification(new WorkNotification(i));
    }
    std::cout << "create tasks finish" << std::endl;
    
    while (!queue.empty()){ // wait until all work is done
//        Poco::Thread::sleep(100);
    }
    
    queue.wakeUpAll(); // tell workers they're done
    
    ThreadPool::defaultPool().joinAll();
    
    return 0;
}