#ifndef XMLREADER_H
#define XMLREADER_H
#include <QString>
#include <QtCore>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QDebug>
#include <iostream>
#include <vector>
using namespace std;

class XmlReader{

public:
    XmlReader(vector<class Player*>);

};

#endif // XMLREADER_H
