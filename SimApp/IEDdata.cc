#include <omnetpp.h>

using namespace omnetpp;

class IEDdata
{
public:
    short des;
    short sor;
    int cmd[4];
    char data[256];
    int datalen;
    int ctrl;

    IEDdata(){}

    short getDes(){
        return des;
    }

    short getSor(){
        return sor;
    }

    int getData(char* buf){
        for(int i=0;i<datalen;i++)
            buf[i] = data[i];
        return datalen;
    }

    char getData(int i){
        return data[i];
    }

    int getDatalen(){
        return datalen;
    }
};
