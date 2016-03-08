#include "Client.h"
#define NPACK 1
#define PORT 31415 //port currently used for testing, can be changed
#define SRV_IP "10.1.42.142" //static ip of pi is 10.0.42.142



Client::Client() {

}
void Client::initilizeSocket(){

   cout << "init socket" << endl;
   //create socket
   m_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   //count variable for init pings
   int sendCount=0;
   //flag for init
   m_initGood=false;

   //define and set socket timeout
   struct timeval timeout;
   timeout.tv_sec=1;
   timeout.tv_usec=0;
   cout<<"set socket timeout" << endl;
   setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO,&timeout,sizeof(timeout));

   //configure adress and port of the pi to be use by socket
   m_si_other.sin_family = AF_INET;
   m_si_other.sin_port = htons(PORT);
   m_si_other.sin_addr.s_addr = inet_addr(SRV_IP);

   //set all arrays to zero
   memset(m_convertedData,0,9);
   memset(m_targetData,0,9);
   memset(m_ballData,0,9);
   memset(m_distanceData,0,9);

   cout<<"start ping loop" << endl;
   char buf[BUFLEN];

   //loop until coms or 25 attempts
   while (!m_initGood && sendCount < 25){
      sendCount++;

      cout<<"send ping " << sendCount << endl;
      //reset buffer between attempts
      memset(buf,0,sizeof(buf));
      sprintf(buf,"ping number %d", sendCount);

      //send ping
      sendto(m_socket,buf,15, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));

      cout<<"waiting to receive" << endl;

      //if received any data back
      if(recvfrom(m_socket,m_receivedData,1024, MSG_TRUNC ,(sockaddr*)&m_si_other, &m_si_other_len)>0){
          //convert received data to int
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

        //reset all arrays
        memset(m_convertedData,0,9);
        memset(m_targetData,0,9);
        memset(m_ballData,0,9);
        memset(m_distanceData,0,9);
        //infinite loop because it is running in a thread
        struct timeval timeout;
        timeout.tv_sec=0;
        timeout.tv_usec=500;
        cout<<"set socket timeout" << endl;
        setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO,&timeout,sizeof(timeout));

        while (true){
           //cout << "waiting to receive packet in thread" << endl;

           //receive packet
           if(recvfrom(m_socket,m_receivedData,BUFLEN, 0 ,(sockaddr*)&m_si_other, &m_si_other_len) < 0) {
              //cout << "packet receive error" << endl;
           }

           else {
               //cout << "packet received in thread" <<endl;

               //convert data from byte to int
               byteToInt(m_receivedData,m_convertedData);
               //Target has flag 1 in first place of array ball has flag 2, lydar has flag 3

               //sort based on the first int as a flag
               if (m_convertedData[0]==1){
                  //set unread data to true telling aiming to get new data
                   m_unreadTargetData=true;
                   copyArray(m_convertedData,m_targetData);

               }
               else if (m_convertedData[0]==2){
                   copyArray(m_convertedData,m_ballData);

               }
               else if (m_convertedData[0]==3){
                   copyArray(m_convertedData,m_distanceData);
               }
               else {
                   //cout << "no valid flag found" <<endl;
                }
           }
     }
}

void Client::byteToInt(char *byteArray,int *intArray){
    int currentByte =0;
    //cout<<"start packet convert"<<endl;
    //loop through int array and count up 2 for bytes
    for (int currentInt = 0; currentInt < 9;currentInt++){
        intArray[currentInt]=(int)byteArray[currentByte] + ((int)(byteArray[currentByte+1]) << 8);
        currentByte+=2;
        //cout << "received data = " <<  intArray[currentInt] << endl;
    }
}

//send a packet of up to size 10 kb
void Client::sendPacket(char * data) {
    cout << "sending packet" << endl;
    sendto(m_socket,data,BUFLEN, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));
}
//getters for data types
int Client::getBallData(int element){
    return m_ballData[element];

}

int Client::getTargetData(int element){
     if (element == 8){
         m_unreadTargetData=false;
     }
    return m_targetData[element];

}

int Client::getDistanceData(){
    return *m_distanceData;

}
//copy from one array to another
void Client::copyArray(int *array1, int *array2){
      for (unsigned int i =0;i < 9;i++){
         array2[i]=array1[i];
      }
}

//getter for unread data or not
bool Client::checkPacketState(){
   return m_unreadTargetData;
}

Client::~Client() {

}
