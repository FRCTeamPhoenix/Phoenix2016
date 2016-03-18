#include "Client.h"
#define NPACK 1
#define PORT 31415 //port currently used for testing, can be changed
#define SRV_IP "10.1.42.142" //static ip of pi is 10.0.4p2.142



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
   memset(m_convertedData,0,5);
   memset(m_targetData,0,5);

   cout<<"start ping loop" << endl;
   char buf[BUFLEN];

   //loop until coms or 25 attempts
   while (!m_initGood && sendCount < 25){
      sendCount++;

      cout<<"send ping " << sendCount << endl;
      //reset buffer between attempts
      memset(buf,0,sizeof(buf));
      //sprintf(buf,"ping number %d", sendCount);

      //send ping
      sendto(m_socket,buf,15, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));

      cout<<"waiting to receive" << endl;

      //if received any data back
      if(recvfrom(m_socket,m_receivedData,1024, MSG_TRUNC ,(sockaddr*)&m_si_other, &m_si_other_len)>0){
          //convert received data to int

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
        memset(m_convertedData,0,5);
        memset(m_targetData,0,5);
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

              for (int i =0;i <5; i ++){
                 for (int j=0;j<4;j++){
                    m_tempByteArray[j]=m_receivedData[i*4+j];
                 }
                 m_convertedData[i]=bytesToInt(m_tempByteArray);
              }

               //sort based on the first int as a flag
               if (m_convertedData[0]==1){
                  //set unread data to true telling aiming to get new data
                   m_unreadTargetData=true;
                   copyArray(m_convertedData,m_targetData);

               }
               else {
                  cout << "invalid flag"<<endl;
               }


           }
     }
}

void Client::byteToIntOld(char *byteArray,int *intArray){
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
    //cout << "sending packet" << endl;
    sendto(m_socket,&data,18, 0 ,(sockaddr*)&m_si_other, sizeof(m_si_other));
}
//getters for data types

int Client::getTargetData(int element){
     if (element == 8){
         m_unreadTargetData=false;
     }
    return m_targetData[element];

}
//copy from one array to another
void Client::copyArray(int *array1, int *array2){
      for (unsigned int i =0;i < 5;i++){
         array2[i]=array1[i];
      }
}
void Client::copyArray(char* char1,char* char2){
   for (int i=0;i<18;i++){
      char2[i]=char1[i];
   }
}
char* Client::intToByteOld(int * array){
   int valuecount=0;
   memset(m_sendData,0,18);

   for ( int i =0;i<18;i++){
      if(i%2){
         m_sendData[i] = (char)(array[valuecount] & 0xff);
      }
      else {
         m_sendData[i] = (char)((array[valuecount] & 0xff00) >> 8);
         valuecount++;

      }
   }
   return m_sendData;

}

char * Client::intToBytes(int num){
   memset(m_intToByteConvertBuf,0,4);
     m_intToByteConvertBuf[0] = (char) ((num & 0xff000000) >> 24);
     m_intToByteConvertBuf[1] = (char) ((num & 0xff0000) >> 16);
     m_intToByteConvertBuf[2] = (char) ((num & 0xff00) >> 8);
     m_intToByteConvertBuf[3] = (char) (num & 0xff);
     return m_intToByteConvertBuf;

}
int Client::bytesToInt(char * bytes){
   unsigned int val=0;
    val += (unsigned int)((unsigned char)bytes[0] << 24);
    val += (unsigned int)((unsigned char)bytes[1] << 16);
    val += (unsigned int)((unsigned char)bytes[2] << 8);
    val += (unsigned int)((unsigned char)bytes[3]);
    return (int)val;
}
//getter for unread data or not
bool Client::checkPacketState(){
   return m_unreadTargetData;
}

Client::~Client() {

}
