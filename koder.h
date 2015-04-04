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
    virtual void poprawKodWPliku(const QString& PathAndName) = 0;
    virtual void wprowadzElementDoPliku(QString FilePath, PrzestrzenNazw* przestrzen, PrzestrzenNazw* doJakiej = NULL) = 0;
    virtual void wprowadzElementDoPliku(QString FilePathAndName, Klasa* klasa, PrzestrzenNazw* DoJakiej = NULL) = 0;
    virtual void wprowadzElementDoPliku(QString FilePathAndName, Struktura* struktura, PrzestrzenNazw* DoJakiej = NULL) = 0;
    virtual void wprowadzElementDoPliku(QString FilePathAndName, Wyliczenie* wyliczenie, PrzestrzenNazw* DoJakiej = NULL) = 0;
    virtual void wprowadzElementDoPliku(QString FilePathAndName, Unia* unia, PrzestrzenNazw* DoJakiej = NULL) = 0;
    virtual QString dekodujAtrybut(const Atrybut& atrybut) = 0;
    virtual QString dekodujOperacje(const Operacja& operacja) = 0;
    virtual QString dekodujBlokOperacji(const QString& BlokOperacji) = 0;
    virtual QString dekodujBlokAtrybutow(const QString& BlokAtrybutow,bool CzyZPustymiLiniami = false) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(PrzestrzenNazw* przestrzen) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(Klasa* klasa) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(Struktura* struktura) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(Unia* unia) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(Wyliczenie* wyliczenie) = 0;

    Koder();
    ~Koder();
};

class KoderCpp: public Koder
{
//    void sprawdzPlik();

public:
    void poprawKodWPliku(const QString& PathAndName);
    void wprowadzElementDoPliku(QString FilePathAndName, PrzestrzenNazw *Przestrzen, PrzestrzenNazw *DoJakiej = NULL);
    void wprowadzElementDoPliku(QString FilePathAndName, Klasa* klasa, PrzestrzenNazw* DoJakiej = NULL);
    void wprowadzElementDoPliku(QString FilePathAndName, Struktura* struktura, PrzestrzenNazw* DoJakiej = NULL);
    void wprowadzElementDoPliku(QString FilePathAndName, Wyliczenie* wyliczenie, PrzestrzenNazw* DoJakiej = NULL);
    void wprowadzElementDoPliku(QString FilePathAndName, Unia* unia, PrzestrzenNazw* DoJakiej = NULL);
    void generujKodDoPliku(QString path);
    QString dekodujAtrybut(const QString& atrybut);
    QString dekodujAtrybut(const Atrybut& atrybut);
    QString dekodujOperacje(const Operacja& operacja);
    QString dekodujOperacje(const QString& operacja);
    QString dekodujBlokOperacji(const QString& BlokOperacji);
    QString dekodujBlokAtrybutow(const QString& BlokAtrybutow, bool CzyZPustymiLiniami = false);
    QString przygotujBlokTekstuDoWpisaniaElementu(PrzestrzenNazw* przestrzen);
    QString przygotujBlokTekstuDoWpisaniaElementu(Klasa* klasa);
    QString przygotujBlokTekstuDoWpisaniaElementu(Struktura* struktura);
    QString przygotujBlokTekstuDoWpisaniaElementu(Unia* unia);
    QString przygotujBlokTekstuDoWpisaniaElementu(Wyliczenie* wyliczenie);
};

class KoderJava: public Koder
{

public:
};

#endif // KODER_H
