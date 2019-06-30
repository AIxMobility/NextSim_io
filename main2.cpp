#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include <string>

#include "headers/InputLink.hpp"
#include "headers/LinkArr.hpp"

using namespace std;

enum SuccessEnum
{
    FAILURE,
    SUCCESS
};

SuccessEnum loadXML()
{
    TiXmlDocument doc;
    if (!doc.LoadFile("simple_network.xml")) 
    {
        cerr << doc.ErrorDesc() << endl;
        return FAILURE;
    }

    TiXmlElement *root = doc.FirstChildElement();
    
    if (root == NULL)
    {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
        return FAILURE;
    }

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        string elemName = elem->Value();
        
        const char *attr;
        if (elemName == "roads")
        {
            cout << "Got roads" << endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                string elemName2 = e->Value();
                if (elemName2 == "nodes") 
                {
                    cout << "Got nodes" << endl;

                    for (TiXmlElement *e2 = e->FirstChildElement(); e2 != NULL; e2 = e2->NextSiblingElement())
                    {
                        //string elemName3 = e2->Value();

                        if (strncmp(e2->Attribute("type"), "intersection", 2) == 0)
                        {
                            //cout << "Got INTERSECTION node with id:" << " " << e2->Attribute("id") << endl;
                        }

                        else if (strncmp(e2->Attribute("type"), "normal", 2) == 0)
                        {
                            //cout << "Got NORMAL node with id:" << " " << e2->Attribute("id") << endl;
                        }

                        else if (strncmp(e2->Attribute("type"), "terminal", 2) == 0)
                        {
                            //cout << "Got TERMINAL node with id:" << " " << e2->Attribute("id") << endl;
                        }
                    }
                }

                else if (elemName2 == "links")
                {
                    cout << "Got links" << endl;

                    LinkArr links;

                    for (TiXmlElement *e2 = e->FirstChildElement(); e2 != NULL; e2 = e2->NextSiblingElement())
                    {
                        //cout << "LINk with id:" << " " << e2->Attribute("id") << endl;
                        //cout << atoi(e2->Attribute("id")) << endl;
                        InputLink demoLink( atoi(e2->Attribute("id")), atoi(e2->Attribute("num_lane")), atoi(e2->Attribute("num_sect")));
                        //cout << demoLink.getId() << endl;
                        //** this prints a single class object instance

                        links.putLink(demoLink);
                        //** this also prints a single class object instance

                        // Problem --> same class name generation in loop --> output variable is for the first class created **
                    }
                    
                    links.showArr();
                }

            }
        }

        else if (elemName == "agents")
        {
            cout << "Got agents" << endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                //cout << e->Attribute("type") << " veh with id: " << e->Attribute("id") << endl;

            }
        }

        else if (elemName == "param")
        {
            cout << "Got param" << endl;

            for (TiXmlElement *e = elem->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
            {
                string elemName2 = e->Value();
                if (elemName2 == "macro"){
                    cout << "Got MACRO params" << endl;
                }

                else if (elemName2 == "micro") {
                    cout << "Got MICRO params" << endl;
                }
            }
        }
    }

    doc.Clear();

    return SUCCESS;
}

int main(int argc, char *argv[])
{
    // Check formatting of the XML file
    if (loadXML() == FAILURE)
        return 1;

    cout << "Loaded successfully." << endl;

    return 0;
}
