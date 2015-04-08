#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <C:\Users\avans\Documents\UML\element.h>
#include <C:\Users\avans\Documents\UML\koder.h>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Operacja operacja("nazwa","integer",wPublic,przezWskaznik,true,true,true,N,100);
    Operacja operacja2("druga","double",wPrivate,przezWskaznik,true,false,true,N,100);
    Operacja operacja3("trzecia","float",wProtected,przezReferencje,true,false,false,Jeden);
    Operacja operacja4("czwarta","int",wPublic,przezWartosc,false,false,false,JedenLubX);
    Operacja operacja5("piata","char",wPrivate,przezReferencje,true,false,false,JedenLubX);
    Operacja operacja6("szesc","bool",wProtected,przezReferencje,false,false,false,Jeden);
    Operacja operacja7("siedem","std::vector",wPublic,przezWartosc,true,false,true,JedenLubX);
    Operacja operacja8("osiem","std::deque",wProtected,przezReferencje,false,true,true,Jeden);
    Operacja operacja9("dziewiec","QList",wPrivate,przezWartosc,true,false,false,JedenLubX);
    Operacja operacja10("dziesiec","string",wPublic);

    Atrybut atrybut1("name","int",wPrivate);
    Atrybut atrybut2("nazwaZ","typ",ND,N,"",false,true,10);
    Atrybut atrybut3("name3","vector",wPublic);
    Atrybut atrybut4("Jasio","bool",wProtected,N,"10",false,false,8);
    Atrybut atrybut5("stasio","std::deque",wPrivate,Jeden,"",false,true,19);
    Atrybut atrybut6("gerlach","double",wPublic,Jeden,"",false,true,19);
    Atrybut atrybut7("stawy","float",wProtected,Jeden,"",false,true,19);
    Atrybut atrybut8("palec","atrybur",wPrivate,Jeden,"",false,true,19);
    Atrybut atrybut9("tarło","kajkoikoo",wPublic,Jeden,"",false,true,19);
    Atrybut atrybut10("kawior","intfsdfegral",wProtected,Jeden,"",false,true,19);

    operacja.dodajParametr(atrybut1);
    operacja.dodajParametr(atrybut2);
    operacja.dodajParametr(atrybut3);

    operacja2.dodajParametr(atrybut4);
    operacja2.dodajParametr(atrybut5);
    operacja2.dodajParametr(atrybut6);

    operacja4.dodajParametr(atrybut7);
    operacja4.dodajParametr(atrybut8);
    operacja4.dodajParametr(atrybut9);

    operacja5.dodajParametr(atrybut10);

    operacja6.dodajParametr(atrybut1);
    operacja6.dodajParametr(atrybut5);

    operacja8.dodajParametr(atrybut2);
    operacja8.dodajParametr(atrybut6);

    operacja10.dodajParametr(atrybut3);
    operacja10.dodajParametr(atrybut7);

    Klasa* klasa = new Klasa("Klasa");
    PrzestrzenNazw* przestrzen = new PrzestrzenNazw("PrzestrzenNazw");
    PrzestrzenNazw* przestrzen2 = new PrzestrzenNazw("PrzestrzenDruga");
    Wyliczenie* wyliczenie = new Wyliczenie("pewneWyliczenie");
    Unia* unia = new Unia("pewnaUnia");
    Struktura* struktura1 = new Struktura("pewnaStruktura");
    Struktura* struktura2 = new Struktura("chmurka");
    Struktura* struktura3 = new Struktura("ania");
    Klasa* klasa1 = new Klasa("kasia");
    Klasa* klasa2 = new Klasa("gosia");
    Klasa* klasa3 = new Klasa("ada");
    Wyliczenie* wyliczenie2 = new Wyliczenie("licz");

    przestrzen->dodajOperacje(operacja);
    przestrzen->dodajOperacje(operacja2);
    przestrzen->dodajAtrybut(atrybut1);
    przestrzen->dodajAtrybut(atrybut2);

    przestrzen2->dodajAtrybut(atrybut4);
    przestrzen2->dodajAtrybut(atrybut5);
    przestrzen2->dodajOperacje(operacja3);
    przestrzen2->dodajOperacje(operacja4);
    przestrzen2->dodajOperacje(operacja);

    klasa->dodajAtrybut(atrybut1);
    klasa->dodajAtrybut(atrybut2);
    klasa->dodajAtrybut(atrybut3);
    klasa->dodajAtrybut(atrybut4);
    klasa->dodajAtrybut(atrybut5);

    klasa->dodajOperacje(operacja);
    klasa->dodajOperacje(operacja2);
    klasa->dodajOperacje(operacja3);
    klasa->dodajOperacje(operacja4);

    klasa1->dodajAtrybut(atrybut2);
    klasa1->dodajAtrybut(atrybut5);

    klasa1->dodajOperacje(operacja3);
    klasa1->dodajOperacje(operacja8);

    klasa2->dodajAtrybut(atrybut3);
    klasa2->dodajAtrybut(atrybut6);

    klasa2->dodajOperacje(operacja4);
    klasa2->dodajOperacje(operacja9);

    struktura1->dodajAtrybut(atrybut4);
    struktura1->dodajOperacje(operacja5);

    struktura2->dodajAtrybut(atrybut5);
    struktura2->dodajAtrybut(atrybut10);
    struktura2->dodajOperacje(operacja6);

    wyliczenie->dodajAtrybut(atrybut3);
    wyliczenie->dodajAtrybut(atrybut6);
    wyliczenie->dodajAtrybut(atrybut10);

    unia->dodajAtrybut(atrybut4);
    unia->dodajAtrybut(atrybut7);
    unia->dodajAtrybut(atrybut1);

    Koder* kod = new KoderCpp;
    QString zdekodowany,zakodowany;

    QString nazwapliku = "pierwsze.h";
    kod->dodajElementDoListy(klasa);
    kod->dodajElementDoListy(klasa1);
    kod->dodajElementDoListy(klasa2);
    kod->dodajElementDoListy(klasa3);
    kod->dodajElementDoListy(przestrzen);
    kod->dodajElementDoListy(przestrzen2);
    kod->dodajElementDoListy(wyliczenie);
    kod->dodajElementDoListy(wyliczenie2);
    kod->dodajElementDoListy(unia);
    kod->dodajElementDoListy(struktura1);
    kod->dodajElementDoListy(struktura2);
    kod->dodajElementDoListy(struktura3);

    kod->wprowadzDoPlikuWszystkieElementy(nazwapliku);
    kod->poprawKodWPliku(nazwapliku);

    delete klasa;
    delete klasa1;
    delete klasa2;
    delete klasa3;
    delete wyliczenie;
    delete wyliczenie2;
    delete unia;
    delete przestrzen2;
    delete przestrzen;
    delete struktura1;
    delete struktura2;
    delete struktura3;

    delete kod;


    ui->textEdit->setText(zakodowany);
}

MainWindow::~MainWindow()
{
    delete ui;
}
