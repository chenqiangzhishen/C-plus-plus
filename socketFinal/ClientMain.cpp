#include "ClientSocket.h"
#include "/home/cq/jsoncpp/include/json/json.h"
#include "SocketException.h"
#include "ConnectionPool.h"
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "sm.SocketMessage.pb.h"


using namespace std;

const string kServer_Address = "127.0.0.1";
const int port = 33333;
const int poolLen = 5;
int exit_flag = 1;

void *thread_function(void *arg)
{
    stringstream ss;
    string s;
    Json::Value root;
    string send_str;
    srand((unsigned)time(NULL));
    while(exit_flag)
    {
        cout << "send Json to server." << endl;
        try
        {

            //ClientSocket client_socket ( "localhost", 30000 );
            CConnPool *client_pool = new CConnPool (kServer_Address, port, poolLen);
            ClientSocket *client_socket = client_pool->getOneConn();

            root["key_id"] = rand();
            send_str = root.toStyledString();
            cout << send_str <<endl;
            std::string reply;

            try
            {
                *client_socket << send_str;
                *client_socket >> reply;
            }
            catch ( SocketException& ) {}

            sm::SocketMessage sockMessage;
            sockMessage.ParseFromString(reply);
            int recv_key_id = sockMessage.received_key_id_plus_1();
            ss << recv_key_id;
            s = ss.str();
            cout << "We received this response from the server:\n" << "value :" + s << endl;;
            ss.clear();
            ss.str("");

        }
        catch ( SocketException& e )
        {
            cout << "Exception was caught:" << e.description() << "\n";
            exit(EXIT_FAILURE);
        }

        sleep(1);
    }
    cout << "every 1 second request thread exit." << endl;
    pthread_exit(0);
}

int main ( void )
{
    pthread_t thread;

    if(0 != pthread_create(&thread, NULL, thread_function, NULL))
    {
        cerr << "Thread creation failed" << endl;
        exit(EXIT_FAILURE);
    }

    char ch;
    while(cin>>ch)
    {
        if (ch == 'q')
            exit_flag = 0;
        cin.clear();
    }
    cout << "Terminate the thread now." << endl;


    cout << "Wait for thread to exit" << endl;

    pthread_join(thread, NULL);
    cout << "Bye!!" << endl;

    return 0;
}
