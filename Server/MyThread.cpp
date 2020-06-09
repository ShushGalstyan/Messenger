#include "MyThread.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
MyThread::MyThread() { 
}

MyThread::~MyThread() {
    if (threadArgs != NULL) {
        delete threadArgs;
        threadArgs = NULL;
    }
    pthread_exit(NULL);
}

MyThread::MyThread(const MyThread& original) {
    
}

const MyThread& MyThread::operator=(const MyThread& other) {
    
}

void* MyThread::entryFunction(void* threadPtr) {
    MyThread* thread = static_cast<MyThread*>(threadPtr);
    thread->run();
    return NULL;
}

void MyThread::start() {
    int res = pthread_create(&thread, NULL, &MyThread::entryFunction, (void*) this);
    if (res != 0) {
        std::string errorMsg = "could not create thread";
   	perror(errorMsg.c_str());
   	exit(1);

    }
}

void MyThread::join() {
    int res = pthread_join(thread, NULL);
    if (res != 0) {
        std::string errorMsg = "could not join the thread";
   	perror(errorMsg.c_str());
   	exit(1);
    }
}
