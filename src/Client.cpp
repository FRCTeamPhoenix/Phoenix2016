#include "Client.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;
#define NPACK 1
#define PORT 31417
#define SRV_IP "10.0.42.25" //change ip address



Client::Client() {

//   std::thread receiveThread(receivePacket);

}
void Client::initilizeSocket(){
    cout << "init socket" << endl;
   m_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   int sendCount=0;
   m_initGood=false;
   //defining and setting socket timeout
   struct timeval timeout;
   timeout.tv_sec=1;
   timeout.tv_usec=0;
   cout << "set socket timout" << endl;

   setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO,&timeout,sizeof(timeout));

   //Initializing everything to zero
   memset((char *) &m_si_me, 0, sizeof(m_si_me));


   m_si_me.sin_family = AF_INET;
   m_si_me.sin_port = htons(PORT);
   m_si_me.sin_addr.s_addr = htonl(INADDR_ANY);

   m_si_other.sin_family = AF_INET;
   m_si_other.sin_port = htons(PORT);
   m_si_other.sin_addr.s_addr = inet_addr(SRV_IP);

   memset(m_receivedData,0,BUFLEN);

   cout << "start ping loop" << endl;
   while (!m_initGood && sendCount< 10){

      sendCount++;
      cout << "sending ping " << sendCount << endl;
      sendto(m_socket,"start",5, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));
      cout << "waiting to receive" << endl;
      if ((recvfrom(m_socket,m_receivedData,BUFLEN, 0 ,(sockaddr*)&m_si_other, &m_si_other_len))>0){
          m_initGood = true;
          cout << "received packet" << endl;
      }
      cout << "Timout Reached" << endl;
    }

}
void Client::receivePacket(){
        socklen_t m_si_other_len=sizeof(m_si_other);
        while (true){
        // breaks out of loop in case of error
        if(recvfrom(m_socket,m_receivedData,BUFLEN, 0 ,(sockaddr*)&m_si_other, &m_si_other_len) == -1) {
           break;
        }
     }
}

void Client::sendPacket() {
    sendto(m_socket,m_sendData,BUFLEN, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));
}
char Client::getData(){
    return m_receivedData;
}
Client::~Client() {
}
