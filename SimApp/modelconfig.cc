#include "modelconfig.h"

ModelConfig::ModelConfig()
{

}

ModelConfig::~ModelConfig()
{

}

int ModelConfig::config()
{
    pugi::xml_node IEDNode;

    inst_xml.init("C:/ModelConfig.xml");
    std::cout << "XML Load result: " << inst_xml.getRootNode().name() << std::endl;
    IEDNode = inst_xml.findNode(inst_xml.getRootNode(), "GENERAL", "");
    string tmp = inst_xml.GetValue(IEDNode, "IEDCount", "");
    iedCount = std::atoi(tmp.c_str());
    std::cout << "iedCount: " << iedCount << std::endl;

    return 0;
}




