#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <pthread.h>

#include <iostream>
#include <memory>
#include <string>

struct ThreadArgs {
    int acceptSocket;
    char messageBuff[512];
};



class MyThread {
public:
    MyThread();
    virtual ~MyThread();
    MyThread(const MyThread& original);
    const MyThread& operator=(const MyThread& other);
    
    void start();
    void join();
    
private:
    pthread_t thread;
    static void* entryFunction(void* threadPtr);
    
protected:
    std::string errorMsg;
    /** arguments for the thread */
    ThreadArgs* threadArgs;

    virtual void* run() = 0;
};

#endif /* MYTHREAD_H */

