#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <memory>
#include <queue>
#include <semaphore.h>

class ProcessManagement {
    sem_t* itemsSemaphore; // space occupied
    sem_t* emptySlotsSemaphore; // space available


    public:
        ProcessManagement();
        ~ProcessManagement(); 
        bool submitToQueue(std::unique_ptr<Task> task);
        void executeTasks();
    private:
        struct SharedMemory {
            std::atomic<int> size; 
            char tasks[1000][256]; // queue that can accomodate 1000 tasks
            int front;
            int rear;

            void printSharedMemory() {
                std::cout<< size << std::endl;
                std::cout<<front<<std::endl;
                std::cout<<rear<<std::endl;
            }
        };

        SharedMemory* sharedMem;
        int shmFd;
        const char* SHM_NAME = "/my_queue";
        std::mutex queueLock;
};

#endif