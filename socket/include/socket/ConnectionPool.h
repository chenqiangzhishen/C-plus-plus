#ifndef __CONNECTION_POOL_H__
#define __CONNECTION_POOL_H__
#include "semaphore.h"
#include "ClientSocket.h"
#include <vector>
#include <map>

using namespace std;

class CConnPool
{
public:
    CConnPool(string server_addr, int port, int pool_len);
    ~CConnPool();
    ClientSocket* getOneConn(); //�����ӳ�ȡһ������
    void  freeOneConn(ClientSocket* pConn);// ���������ˣ������Ż����ӳء��Ա��������á�

private:
    string m_serverAddr;
    int m_port;
    int m_poolLen;
    pthread_mutex_t m_work_mutex;
    vector<ClientSocket*>  m_vectorConn;
    map<ClientSocket*, int> m_mapVI; //  �����ӵĵ�ַ�������ҵ����������ڴ�ŵ�m_vectorconn�С�

};

#endif

