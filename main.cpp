#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include <string>

using namespace std;

enum SuccessEnum {FAILURE, SUCCESS};

SuccessEnum loadXML()
{
	TiXmlDocument doc;
	if(!doc.LoadFile("test.xml"))
	{
		cerr << doc.ErrorDesc() << endl;
		return FAILURE;
	}
	
	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
		return FAILURE;
	}
	
	for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		string elemName = elem->Value();
		
        const char* attr;
		if(elemName == "Element1")
		{
			cout << "Got Element1" << endl;
			
			attr = elem->Attribute("attribute1");
			if(attr != NULL)
				cout << "Got attribute1: " << attr << endl;
		}
		else if(elemName == "Element2")
		{
			cout << "Got Element2" << endl;
			
			attr = elem->Attribute("attribute2");
			if(attr != NULL)
				cout << "Got attribute2: " << attr << endl;
			
			attr = elem->Attribute("attribute3");
			if(attr != NULL)
				cout << "Got attribute3: " << attr << endl;
			
			
			for(TiXmlElement* e = elem->FirstChildElement("Element3"); e != NULL; e = e->NextSiblingElement("Element3"))
			{
				cout << "Got Element3" << endl;
			
				attr = e->Attribute("attribute4");
				if(attr != NULL)
					cout << "Got attribute4: " << attr << endl;
			}
			
			for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling())
			{
			    TiXmlText* text = e->ToText();
			    if(text == NULL)
                    continue;
                
                cout << "Got text: " << text->Value() << endl;
			}
		}
	}
    
    doc.Clear();
	
	return SUCCESS;
}


/* SuccessEnum saveXML()
{
	TiXmlDocument doc;
	
	TiXmlElement* root = new TiXmlElement("root");
	doc.LinkEndChild(root);
	
	TiXmlElement* element1 = new TiXmlElement("Element1");
	root->LinkEndChild(element1);
	
	element1->SetAttribute("attribute1", "some value");
	
	
	TiXmlElement* element2 = new TiXmlElement("Element2");
	root->LinkEndChild(element2);
	
	element2->SetAttribute("attribute2", "2");
	element2->SetAttribute("attribute3", "3");
	
	
	TiXmlElement* element3 = new TiXmlElement("Element3");
	element2->LinkEndChild(element3);
	
	element3->SetAttribute("attribute4", "4");
	
	TiXmlText* text = new TiXmlText("Some text.");
	element2->LinkEndChild(text);
	
	
	bool success = doc.SaveFile("test_save.xml");
	
    doc.Clear();
    
    if(success)
        return SUCCESS;
    else
        return FAILURE;
} */



int main(int argc, char* argv[])
{
	if(loadXML() == FAILURE)
		return 1;
    
    cout << "Loaded successfully." << endl;
    
	
	
	return 0;
}
