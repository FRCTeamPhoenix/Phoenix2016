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
    bool m_unreadBallData;
    bool m_unreadTargetData;
    bool m_unreadDistanceData;
    char m_receivedData[BUFLEN];
    static bool receive;
    int m_socket;
    socklen_t m_si_other_len;
    char buf2[20];
    bool m_initGood;
    char m_sendData[BUFLEN];
    sockaddr_in m_si_me, m_si_other;
    int m_convertedData[9];
    int m_targetData[9];
    int m_ballData[9];
    int m_distanceData[9];
    Client();

    char* getData();

    void initilizeSocket();

    bool checkPacketState();

    void receivePacket();

    void byteToInt(char *byteArray,int *intArray);

    int getTargetData(int element);

    void sendPacket(char * data);

    int getBallData(int element);

    int getDistanceData();

    void copyArray(int *array1, int *array2);

    virtual ~Client();

};

#endif
