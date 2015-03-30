#ifndef RELACJA_H
#define RELACJA_H
#include <QString>
#include <QStringList>
#include <QVector>
#include <C:\Users\avans\Documents\UML\element.h>


class Relacja
{
protected:
    Element* Pierwszy;
    Element* Drugi;
    Krotnosc Multi;
public:

    Relacja(Element* pierwszy, Element* drugi, Krotnosc krotnosc = Jeden):Pierwszy(pierwszy),Drugi(drugi),Multi(krotnosc)
    {}
    ~Relacja();
    bool CzyJestElement();
    virtual void draw() = 0;
};

class Dependency: public Relacja
{
public:
    void draw();
};

class Composition: public Relacja
{
public:
    void draw();
};

class Aggregation: public Relacja
{
public:
    void draw();
};

class Generalization: public Relacja
{
public:
    void draw();
};

class Association: public Relacja
{
public:
    void draw();
};

#endif // RELACJA_H
