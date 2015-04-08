#ifndef RELACJA_H
#define RELACJA_H
#include <QString>
#include <QStringList>
#include <QVector>
#include <C:\Users\avans\Documents\UML\element.h>


class Relacja
{
protected:
    Element* Pierwszy;  //pokazywany przez strzalke
    Element* Drugi;
    QString komentarz;
    Widocznosc widocznosc;
public:

    Relacja(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = ""):Pierwszy(pierwszy),Drugi(drugi),widocznosc(wid),komentarz(koment)
    {}
    ~Relacja();
    bool CzyJestElement();
    virtual void draw() = 0;
};

class Dependency: public Relacja
{

public:
    Dependency(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = ""):Relacja(pierwszy,drugi,wid,koment)
    {}
    void draw();
};

class Composition: public Relacja
{
    Krotnosc Ile;
public:
    Composition(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = "",Krotnosc ile = Jeden):Relacja(pierwszy,drugi,wid,koment),Ile(ile)
    {}
    void draw();
};

class Aggregation: public Relacja
{
    Krotnosc Ile;
public:
    Aggregation(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = "",Krotnosc ile = Jeden):Relacja(pierwszy,drugi,wid,koment),Ile(ile)
    {}
    void draw();
};

class Generalization: public Relacja
{
public:
    Generalization(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = ""):Relacja(pierwszy,drugi,wid,koment)
    {}
    void draw();
};

class Association: public Relacja
{
    Krotnosc Ile;
public:
    Association(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = "",Krotnosc ile = Jeden):Relacja(pierwszy,drugi,wid,koment),Ile(ile)
    {}
    void draw();
};

#endif // RELACJA_H
