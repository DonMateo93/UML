#ifndef KODER_H
#define KODER_H
#include <C:\Users\avans\Documents\UML\relacja.h>
#include <C:\Users\avans\Documents\UML\element.h>
#include <QVector>


class Koder
{
protected:
//    virtual void sprawdzPlik();
    QVector<Relacja*> WektorRelacji;
    QVector<Element*> WektorElementow;
    QString RodzajStosowanegoKontenera;

public:
//    virtual void wprowadzKlaseDoPliku();
//    virtual void wprowadzStructureDoPliku();
//    virtual void wprowadzWyliczenieDoPliku();
//    virtual void wprowadzUnieDoPliku();
//    virtual void wprowadzAgregacjeDoPliku();
//    virtual void wprowadzGeneralizacjeDoPliku();
//    virtual void wprowadzDependencyDoPliku();
//    virtual void wprowadzAsocjacjeDoPliku();
//    virtual void wprowadzKompozycjeDoPliku();
//    virtual void generujKodDoPliku(QString path = "");
    virtual void wprowadzElementDoPliku(QString FilePath, PrzestrzenNazw* przestrzen, PrzestrzenNazw* doJakiej = NULL) = 0;
    virtual QString dekodujAtrybut(const Atrybut& atrybut) = 0;
    virtual QString dekodujOperacje(const Operacja& operacja) = 0;
    virtual QString dekodujBlokOperacji(const QString& BlokOperacji) = 0;
    virtual QString dekodujBlokAtrybutow(const QString& BlokAtrybutow,bool CzyZPustymiLiniami = false) = 0;
    virtual void poprawKodWPliku(const QString& PathAndName) = 0;
//    virtual QString dajListeAtrybutow();

    Koder();
    ~Koder();
};

class KoderCpp: public Koder
{
//    void sprawdzPlik();

public:
//    void wprowadzKlaseDoPliku();
//    void wprowadzStructureDoPliku();
//    void wprowadzWyliczenieDoPliku();
//    void wprowadzUnieDoPliku();
//    void wprowadzAgregacjeDoPliku();
//    void wprowadzGeneralizacjeDoPliku();
//    void wprowadzDependencyDoPliku();
//    void wprowadzAsocjacjeDoPliku();
//    void wprowadzKompozycjeDoPliku();
    void wprowadzElementDoPliku(QString FilePathAndName, PrzestrzenNazw *Przestrzen, PrzestrzenNazw *DoJakiej = NULL);
    void wprowadzElementDoPliku(QString FilePathAndName, Klasa* klasa);
    void generujKodDoPliku(QString path);
    QString dekodujAtrybut(const QString& atrybut);
    QString dekodujAtrybut(const Atrybut& atrybut);
    QString dekodujOperacje(const Operacja& operacja);
    QString dekodujOperacje(const QString& operacja);
    QString dekodujBlokOperacji(const QString& BlokOperacji);
    QString dekodujBlokAtrybutow(const QString& BlokAtrybutow, bool CzyZPustymiLiniami = false);
    void poprawKodWPliku(const QString& PathAndName);

};

class KoderJava: public Koder
{
    //void sprawdzPlik();

public:
//    void wprowadzPrzestrzenieNazw();
//    void generujKodDoPliku(QString path = "");
};

#endif // KODER_H
