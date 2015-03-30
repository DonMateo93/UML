#ifndef ELEMENT_H
#define ELEMENT_H
#include <QString>
#include <QPoint>
#include <QList>
#include <QVector>

//DODAĆ ITERATORY

class Atrybut;

class Operacja;

enum PrzekazanieParametru
{
    przezWartosc    = 0,
    przezReferencje = 1,
    przezWskaznik   = 2
};

enum Widocznosc
{
    wPrivate    = '-',
    wPublic     = '+',
    wProtected  = '#',
    wPackage    = '~',
    ND          = '^'
};

enum Krotnosc
{
    Jeden       = 1,
    JedenLubX   = 2,
    ZeroLub1    = 3,
    ZeroLubX    = 4,
    N           = 5,
    WiecejNizN  = 6
};

class Element
{
protected:
    QString NazwaElementu;
    static int IleElementow;
    int IleWskaznikowNaObiekt;
    QPoint Polozenie;
    QVector<Atrybut> WektorAtrybutow;

public:
    Element(QString nazwa = ""):NazwaElementu(nazwa)
    {}
    ~Element();
    void dodajAtrybut(Atrybut atrybut);
    void czyJestAtrybut(Atrybut atrybut);
    void zmienWlasciwosciAtrybutuONazwie(QString nazwa, QString typ, Widocznosc wid, Krotnosc ile, bool czyStatyczna, bool czyConst,int n);
    void wymazAtrybut(QString atrybut);
    QString atrybutGetText();
    virtual QString dajInfoDlaKodera() = 0;
};

class ElementZOperacjami: public Element
{
protected:
    QVector<Operacja> WektorOperacji;
public:
    ElementZOperacjami(QString nazwa = "");
    void dodajOperacje(Operacja operacja);
    void czyJestOperacja(QString operacja);
    void zmienWlasciwosciOperacjiONazwie(QString nazwa, QString typ, Widocznosc wid, Krotnosc ile, bool czyStatyczna, bool czyConst,int n, QString komentarz, PrzekazanieParametru przekaz);
    void wymazOperacje(QString operacja);

};

class SkladowaElementu
{
protected:
    int n;
    Krotnosc Ile;
    QString Typ;
    QString Komentarz;
    QString Nazwa;
    Widocznosc Visibility;
    bool CzyStatyczna;
    bool CzyConst;
    virtual void aktualizujKomentarz() = 0;

public:
    SkladowaElementu(QString nazwa = "", QString typ = "", Widocznosc wid = wPrivate, bool czyStatyczna = false, bool czyConst = false,Krotnosc ile = Jeden,int ileN = 0):Nazwa(nazwa),Typ(typ), Visibility(wid),CzyStatyczna(czyStatyczna), CzyConst(czyConst),Ile(ile),n(ileN)
    {}


//    friend QString&
//        operator<<(QString& napis, Operacja operacja);

//    friend QString&
//        operator<<(QString& napis, Atrybut atrybut);

};

class ParametrOperacji
{
    bool CzyDomyslnaWartosc;
    bool CzyConst;
    QString Typ;
    QString Nazwa;
    QString DomyslnaWartosc;
    PrzekazanieParametru Przekazanie;

public:
    ParametrOperacji(QString nazwa,QString typ = "",bool czyConst = false,PrzekazanieParametru przekazanie = przezWartosc, bool czyDomyslnaWart = false, QString domyslnaWart = ""):Nazwa(nazwa),CzyConst(czyConst),Typ(typ),Przekazanie(przekazanie),CzyDomyslnaWartosc(czyDomyslnaWart),DomyslnaWartosc(domyslnaWart)
    {}
    friend QString&
       operator<<(QString& wyjscie, const ParametrOperacji metoda);
    QString getName();
    void setName(QString nazwa);
    QString getType();
    void setType(QString nazwa);
    PrzekazanieParametru getPass();
    void setPass(PrzekazanieParametru przekaz);

};

class Operacja: public SkladowaElementu
{
    QList<Atrybut> ListaParamMetod;
    PrzekazanieParametru Przekaz;
    bool CzyWirtualna;

public:
    int dodajParametr(Atrybut Parametr);
    bool czyJestParametr(Atrybut Parametr);
    Operacja(QString nazwa = "",QString typ = "",Widocznosc wid = wPrivate,PrzekazanieParametru przekaz = przezWartosc, bool czyStatyczna = false, bool czyConst = false, bool czyWirtualna = false,Krotnosc ile = Jeden,int ileN = 0):SkladowaElementu(nazwa,typ,wid,czyStatyczna,czyConst,ile,ileN),Przekaz(przekaz), CzyWirtualna(czyWirtualna)
    {
        aktualizujKomentarz();
    }
    Operacja(QList<Atrybut> ListaParam, QString typ = "", Widocznosc wid = wPrivate, QString nazwa = "",PrzekazanieParametru przekaz = przezWartosc, bool czyStatyczna = false, bool czyConst = false, bool czyWirtualna = false,Krotnosc ile = Jeden):SkladowaElementu(nazwa,typ,wid,czyStatyczna,czyConst,ile),ListaParamMetod(ListaParam), Przekaz(przekaz), CzyWirtualna(czyWirtualna)
    {
        aktualizujKomentarz();
    }
    int ParamSize();

    friend QString&
        operator<<(QString& napis, Operacja operacja);

    void aktualizujKomentarz();
};

class KontenerOperacji
{
    QVector<Operacja*> WektorOperacji;

public:
    KontenerOperacji(){}
    KontenerOperacji(QVector<Operacja*> gotowaLista);
    ~KontenerOperacji();
    bool CzyJestOperacjaODanejNazwie(QString operacja);
    void add(Operacja* operacja);

};

class Atrybut: public SkladowaElementu
{
    QString DomyslnaWartosc;

public:
    Atrybut(QString nazwa = "",QString typ = "",Widocznosc wid = wPrivate,Krotnosc ile = Jeden,QString domyslnaWart = "", bool czyStatyczna = false, bool czyConst = false,int ileN = 0):SkladowaElementu(nazwa,typ,wid,czyStatyczna,czyConst,ile,ileN), DomyslnaWartosc(domyslnaWart)
    {
        aktualizujKomentarz();
    }
    friend QString&
        operator<<(QString& napis, Atrybut atrybut);
    void aktualizujKomentarz();
};

class Klasa: public ElementZOperacjami
{
    bool CzyAbstrakcyjna;
public:
    Klasa(QString nazwa = "", bool czyAbstrakcyjna = false):ElementZOperacjami(nazwa),CzyAbstrakcyjna(czyAbstrakcyjna)
    {
        IleElementow++;
    }
    ~Klasa()
    {
        IleElementow--;
    }
    QString dajInfoDlaKodera();
};

class Struktura: public ElementZOperacjami
{
public:
    QString dajInfoDlaKodera();
    Struktura(QString nazwa = ""):ElementZOperacjami(nazwa)
    {
        IleElementow++;
    }
    ~Struktura()
    {
        IleElementow--;
    }

};

class PrzestrzenNazw: public ElementZOperacjami
{
public:
    QString dajInfoDlaKodera();
    PrzestrzenNazw(QString nazwa = ""):ElementZOperacjami(nazwa)
    {
        IleElementow++;
    }
    ~PrzestrzenNazw()
    {
        IleElementow--;
    }
};

class Unia: public Element
{
public:
    QString dajInfoDlaKodera();
    Unia(QString nazwa = ""):Element(nazwa)
    {
        IleElementow++;
    }
    ~Unia()
    {
        IleElementow--;
    }
};

class Wyliczenie: public Element
{
public:
    QString dajInfoDlaKodera();
    Wyliczenie(QString nazwa = ""):Element(nazwa)
    {
        IleElementow++;
    }
    ~Wyliczenie()
    {
        IleElementow--;
    }
};

#endif // ELEMENT_H
