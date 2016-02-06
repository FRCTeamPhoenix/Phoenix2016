#include "Client.h"
#define NPACK 1
#define PORT 31415 //port currently used for testing, can be changed
#define SRV_IP "10.0.42.142" //static ip of pi is 10.0.42.142


Client::Client() {

//   std::thread receiveThread(receivePacket);

}
void Client::initilizeSocket(){

   cout << "init socket" << endl;
   m_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   int sendCount=0;
   m_initGood=false;
   //defcouininkg and setting socket timeout
   struct timeval timeout;
   timeout.tv_sec=1;
   timeout.tv_usec=0;
   cout<<"set socket timeout" << endl;
   setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO,&timeout,sizeof(timeout));

   //Initializing everything to zero
   //memset((char *) &m_si_me, 0, sizeof(m_si_me));

   //Only used in case of bind probably not used right now.
   //m_si_me.sin_family = AF_INET;
   //m_si_me.sin_port = htons(PORT);
   //m_si_me.sin_addr.s_addr = htonl(INADDR_ANY);

   m_si_other.sin_family = AF_INET;
   m_si_other.sin_port = htons(PORT);
   m_si_other.sin_addr.s_addr = inet_addr(SRV_IP);

   memset(m_convertedData,0,9);
   memset(m_targetData,0,9);
   memset(m_ballData,0,9);
   memset(m_distanceData,0,9);

   cout<<"start ping loop" << endl;
   char buf[BUFLEN];

   while (!m_initGood && sendCount < 25){
      sendCount++;

      cout<<"send ping " << sendCount << endl;
      memset(buf,0,sizeof(buf));
      sprintf(buf,"ping number %d", sendCount);

      sendto(m_socket,buf,15, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));

      cout<<"waiting to receive" << endl;
      Wait(.5);

      if(recvfrom(m_socket,m_receivedData,1024, MSG_TRUNC ,(sockaddr*)&m_si_other, &m_si_other_len)>0){
          byteToInt(m_receivedData,m_convertedData);
          cout<<"init good" <<endl;
          m_initGood=true;

      }
      else {
          cout << "timout" << endl;
      }

   }
}
void Client::receivePacket(){
        socklen_t m_si_other_len=sizeof(m_si_other);

        memset(m_convertedData,0,9);
        memset(m_targetData,0,9);
        memset(m_ballData,0,9);
        memset(m_distanceData,0,9);
        while (true){
           cout << "waiting to receive packet in thread" << endl;
           if(recvfrom(m_socket,m_receivedData,BUFLEN, 0 ,(sockaddr*)&m_si_other, &m_si_other_len) < 0) {
              cout << "packet receive error" << endl;
           }

           else {
               cout << "packet received in thread" <<endl;
               byteToInt(m_receivedData,m_targetData);
               //Target has flag 1 in first place of array ball has flag 2, lydar has flag 3
               if (m_convertedData[0]==1){
                   copyArray(m_convertedData,m_targetData);
                   m_unreadTargetData=true;

               }
               else if (m_convertedData[0]==2){
                   copyArray(m_convertedData,m_ballData);
                   m_unreadBallData=true;

               }
               else if (m_convertedData[0]==3){
                   copyArray(m_convertedData,m_distanceData);
                   m_unreadDistanceData=true;
               }
               else {
                   cout << "no valid flag found" <<endl;
                }
           }
     }
}
void Client::byteToInt(char *byteArray,int *intArray){
    int currentByte =0;
    for (int currentInt = 0; currentInt<8;currentInt++){

        intArray[currentInt]=(int)byteArray[currentByte] + ((int)(byteArray[currentByte+1]) << 8);
        currentByte+=2;
        cout << "received data = " <<  intArray[currentInt] << endl;
    }
}

void Client::sendPacket() {
    cout << "sending packet" << endl;
    sendto(m_socket,m_sendData,BUFLEN, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));
}

int Client::getBallData(){
    m_unreadBallData=false;
    return *m_ballData;

}

int Client::getTargetData(){
    m_unreadTargetData=false;
    return *m_targetData;

}

int Client::getDistanceData(){
    m_unreadDistanceData=false;
    return *m_distanceData;

}

void Client::copyArray(int *array1, int *array2){
   if (sizeof(array1)>=sizeof(array2)){
      for (int i =0;i<sizeof(array2);i++){
         array2[i]=array1[i];
      }
   }
   else {
      for (int i =0;i<sizeof(array1);i++){
            array2[i]=array1[i];
      }
   }
}

Client::~Client() {

}

