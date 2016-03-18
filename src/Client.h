#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include "WPILib.h"
#include <arpa/inet.h> // winsock2.h for windows
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <string.h>
using namespace std;
#define BUFLEN 10240

class Client {
public:
    bool m_unreadTargetData;
    char m_receivedData[BUFLEN];
    static bool receive;
    int m_socket;
    socklen_t m_si_other_len;
    bool m_initGood;
    sockaddr_in m_si_me, m_si_other;
    int m_convertedData[5];
    int m_targetData[5];
    char m_sendData[8];
    char m_tempByteArray[4];
    char m_intToByteConvertBuf[4];
    Client();

    char* getData();

    void initilizeSocket();

    bool checkPacketState();

    void receivePacket();

    void byteToIntOld(char *byteArray,int *intArray);

    char* intToByteOld(int * intArray);

    int getTargetData(int element);

    void sendPacket(char * data);

    int getBallData(int element);

    int getResponseData(int element);

    void copyArray(int *array1, int *array2);

    void copyArray(char *char1,char * char2);

    char * intToBytes(int num);

    int bytesToInt(char * bytes);

    virtual ~Client();


};

#endif
