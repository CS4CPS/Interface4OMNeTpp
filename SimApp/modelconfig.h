#ifndef MODELCONFIG_H
#define MODELCONFIG_H

#include <vector>
#include <string>
#include <iostream>

#include "drv_xml.h"

typedef struct{
    int iedBase;
    int iedCnt;
    int iedCount;
    int swTotalCount;
    int swControlBase;
    int swControlCnt;
    int parcount;

    int Tmslen, Tctlen, Tlen;
}ModelInfo;

#define MODELCONFIG_MEASURE     1
#define MODELCONFIG_PARA        2
#define MODELCONFIG_CTRL        3

class ModelConfig
{
public:
    ModelConfig();
    ~ModelConfig();

    int config();

    drv_xml inst_xml;
    int iedCount;
};

#endif // MODELCONFIG_H
