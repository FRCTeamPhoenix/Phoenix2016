#include "Client.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;
#define NPACK 1
#define PORT 31415
#define SRV_IP "10.0.42.21" //change ip address



Client::Client() {

//   std::thread receiveThread(receivePacket);

}
void Client::initilizeSocket(){
   m_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

   memset((char *) &m_si_me, 0, sizeof(m_si_me));

   m_si_me.sin_family = AF_INET;
   m_si_me.sin_port = htons(PORT);
   m_si_me.sin_addr.s_addr = htonl(INADDR_ANY);

   m_si_other.sin_family = AF_INET;
   m_si_other.sin_port = htons(PORT);
   m_si_other.sin_addr.s_addr = inet_addr(SRV_IP);

   memset(m_receivedData,0,BUFLEN);


   sendto(m_socket,"start",5, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));


    }
void Client::receivePacket(){
            socklen_t m_si_other_len=sizeof(m_si_other);
            while (true){

            // breaks out of loop in case of error
            if(recvfrom(m_socket,m_receivedData,BUFLEN, 0 ,(sockaddr*)&m_si_other, &m_si_other_len) == -1) {
               break;
            }
            cout << "received packet";
        }
}

void Client::sendPacket() {
    sendto(m_socket,m_sendData,BUFLEN, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));
}

Client::~Client() {
}
