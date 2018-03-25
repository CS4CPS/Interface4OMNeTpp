#include "drv_xml.h"

drv_xml::drv_xml()
{    
}

drv_xml::~drv_xml()
{
}

void drv_xml::init(string fileName)
{
    pugi::xml_parse_result result = doc.load_file(fileName.c_str());
    std::cout << "XML Load result: " << result.description() << std::endl;

    ModelConfig = doc.child("ModelConfig");
}

pugi::xml_node drv_xml::getRootNode()
{
    return ModelConfig;
}

pugi::xml_node drv_xml::findNode(pugi::xml_node root, string Name, string cnt)
{
    pugi::xml_node Noderes;

    for(Noderes = root.child(Name.c_str());Noderes;Noderes = Noderes.next_sibling(Name.c_str()))
    {
        std::cout << "Noderes: " << Noderes.value() << std::endl;
        if(cnt.compare("")!=0)
        {
            string nametmp = Noderes.attribute("id").value();
            if(nametmp.compare(cnt) == 0)
            {
                break;
            }
        }else
        {
            break;
        }
    }

    return Noderes;
}

int drv_xml::GetCount(pugi::xml_node root, string Name)
{
    pugi::xml_node Noderes;
    int cnt = 0;

    for(Noderes = root.child(Name.c_str());Noderes;Noderes = Noderes.next_sibling(Name.c_str()))
    {
        cnt = cnt + 1;
    }

    return cnt;
}

string drv_xml::GetValue(pugi::xml_node root, string Name, string cnt)
{
    string res;

    pugi::xml_node Noderes = findNode(root, Name, cnt);
    res = Noderes.child_value();

    return res;
}
