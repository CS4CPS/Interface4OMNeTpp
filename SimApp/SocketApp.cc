#include <SocketApp.h>

SocketApp::SocketApp() {
    listenerSocket = INVALID_SOCKET;
    connSocket = INVALID_SOCKET;
}

SocketApp::~SocketApp() {
}

int32 SocketApp::sa_init(const char *ipv4, uint32 port)
{
    WSADATA data;

    if(WSAStartup(MAKEWORD(2,2),&data))
        throw cRuntimeError("WSAStartup() call failed.");

    listenerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenerSocket == INVALID_SOCKET)
        throw cRuntimeError("Cannot create socket");

    sockaddr_in sinInterface;
    sinInterface.sin_family = AF_INET;
    //sinInterface.sin_addr.s_addr = inet_addr("49.123.120.232");//INADDR_ANY;
    sinInterface.sin_addr.s_addr = inet_addr("10.0.2.15");//INADDR_ANY;
    //sinInterface.sin_addr.s_addr = inet_addr("192.168.43.87");//INADDR_ANY;
    sinInterface.sin_port = htons(6676);
    if (bind(listenerSocket, (sockaddr *)&sinInterface, sizeof(sockaddr_in)) == SOCKET_ERROR)
        throw cRuntimeError("Socket bind() failed");

    listen(listenerSocket, SOMAXCONN);

    // accept connection, and store FD in connSocket
    sockaddr_in sinRemote;
    int addrSize = sizeof(sinRemote);
    //connSocket = accept(listenerSocket, (sockaddr *)&sinRemote, (socklen_t *)&addrSize);
    connSocket = accept(listenerSocket, (sockaddr *)&sinRemote, &addrSize);
    if (connSocket == INVALID_SOCKET)
        throw cRuntimeError("Accept() failed");
    std::cout << "accept connection." << endl;
    return 0;
}

int32 SocketApp::sa_rece(uint32 addr, uint8 *buf, uint32 len)
{
    int res;

    while(1)
    {
        res = recv(connSocket,(char*)buf,512,0);
        if (res > 0)
        {
            break;
        }else if (res == SOCKET_ERROR) {
            std::cout << "socket error" << endl;
            closesocket(connSocket);
            connSocket = INVALID_SOCKET;
            res = -1;
            break;
        } else if (res == 0) {
            std::cout << "socket closed by the client" << endl;
            closesocket(connSocket);
            connSocket = INVALID_SOCKET;
            res = -1;
            break;
        }
    }

    return res;
}

int32 SocketApp::sa_send(uint32 addr, uint8 *buf, uint32 len)
{
    int res;

    res  = send(connSocket, (char*)buf, len, 0);
    if(res == SOCKET_ERROR)
    {
        std::cout << "socket error" << endl;
        closesocket(connSocket);
        connSocket = INVALID_SOCKET;
        res = -1;
    }
    return res;
}

