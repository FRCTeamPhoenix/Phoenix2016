#include "Client.h"
#include <arpa/inet.h> // winsock2.h for windows
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#define NPACK 1
#define PORT 31415
#define SRV_IP "999.999.999.999" //change ip address



Client::Client() {

//   std::thread receiveThread(receivePacket);

}

void Client::receivePacket(){

    struct sockaddr_in si_me, si_other;
        int receiveSocket, slen=sizeof(si_other);
        //char buf[BUFLEN];

        receiveSocket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        memset((char *) &si_me, 0, sizeof(si_me));

        si_me.sin_family = AF_INET;

        si_me.sin_port = htons(PORT);

        si_me.sin_addr.s_addr = htonl(INADDR_ANY);

        bind(receiveSocket, (sockaddr*)&si_me, sizeof(si_me));

        while (true){

            // breaks out of loop in case of error
            if(recvfrom(receiveSocket,m_receivedData,BUFLEN,0, (sockaddr*)&si_other, (socklen_t*)&slen) == -1) {
               break;
            }
            //m_receivedData=buf;
        }
}

void Client::sendPacket() {

}

Client::~Client() {
}
