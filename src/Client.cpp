#include "Client.h"
#define NPACK 1
#define PORT 31415 //port currently used for testing, can be changed
#define SRV_IP "10.0.42.25" //change ip address



Client::Client() {

//   std::thread receiveThread(receivePacket);

}
void Client::initilizeSocket(){
   cout<<"init socket" << endl;
   m_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   int sendCount=0;
   m_initGood=false;
   //defcouining and setting socket timeout
   struct timeval timeout;
   timeout.tv_sec=1;
   timeout.tv_usec=0;
   cout<<"set socket timeout" << endl;

   setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO,&timeout,sizeof(timeout));

   //Initializing everything to zero
   memset((char *) &m_si_me, 0, sizeof(m_si_me));

   //Only used in case of bind probably not used right now.
   //m_si_me.sin_family = AF_INET;
   //m_si_me.sin_port = htons(PORT);
   //m_si_me.sin_addr.s_addr = htonl(INADDR_ANY);

   m_si_other.sin_family = AF_INET;
   m_si_other.sin_port = htons(PORT);
   m_si_other.sin_addr.s_addr = inet_addr(SRV_IP);

   memset(m_receivedData,0,BUFLEN);

   cout<<"start ping loop" << endl;

   while ((!m_initGood) && (sendCount< 10)){
      sendCount++;

      cout<<"send ping" << endl;
      char buf[1024];
      sprintf(buf,"ping number %d", sendCount);
      sendto(m_socket,buf,15, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));

      cout<<"waiting to receive" << endl;

      if (recvfrom(m_socket,m_receivedData,BUFLEN, 0 ,(sockaddr*)&m_si_other, &m_si_other_len)>0){
          cout << "set init good" << endl;
          m_initGood=true;
          m_convertedData = byteToInt(m_receivedData);
      }
      else {
      cout<< "timeout reached" << endl;
      }
    }

}
void Client::receivePacket(){
        socklen_t m_si_other_len=sizeof(m_si_other);

        while (true){
        // breaks out of loop in case of error
        cout << "waiting to receive packet" << endl;
        if(recvfrom(m_socket,m_receivedData,BUFLEN, 0 ,(sockaddr*)&m_si_other, &m_si_other_len) < 0) {
           break;
        }
        else {
            cout << "packet received = " << m_receivedData<<endl;
        }
     }
}
int Client::byteToInt(char *byteArray){
    int currentByte =0;
    int intArray[8];
    for (int currentInt =0;currentInt < 8;currentInt++){

        intArray[currentInt]=(int)byteArray[currentByte] +(int)(byteArray[currentByte+1] <<8);
        currentByte+=2;
        cout << "received data = " <<  intArray[currentInt] << endl;
    }
    return intArray;

}

void Client::sendPacket() {
    cout << "sending packet" << endl;
    sendto(m_socket,m_sendData,BUFLEN, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));
}
int Client::getData(){
    return m_convertedData;

}

Client::~Client() {
}
