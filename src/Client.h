#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#define BUFLEN 1024

class Client {
public:
    static double m_targetPosition;
    char m_receivedData[BUFLEN];
    static bool receive;

    Client();

    void receivePacket();

    void sendPacket();

    virtual ~Client();

};

#endif
