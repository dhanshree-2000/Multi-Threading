 #include <iostream>
 #include <mutex>
 #include <queue>
 #include <thread>
 #include <chrono>
 #include <sstream>
 #include "Logger.h"
 #include "Message.h"
 
 using namespace std;
 
 int main()
 {
 
     Message M[5];
     for(int msg_num = 0; msg_num < 5; msg_num++){
        string msg="";
        cout<<"Enter message:-";
        cin>>msg;
         M[msg_num].setMessage(msg);
     }
 
     Logger* log = Logger::getInstance();
     try {
           thread t1(&Logger::AddToQueue, log, M[0]);
           thread t2(&Logger::AddToQueue, log, M[1]);
           thread t3(&Logger::AddToQueue, log, M[2]);
           thread t4(&Logger::AddToQueue, log, M[3]);
           thread t5(&Logger::AddToQueue, log, M[4]);
 
           this_thread::sleep_for(chrono::milliseconds(100));
 
           thread t6(&Logger::RemoveFromQueue, log);
 
           t1.join();
           t2.join();
           t3.join();
           t4.join();
           t5.join();
           t6.join();
     }
     catch(const std::exception& e)
     {
        cout<<"caught exception"<<endl;
     }            
     return 0;
 }