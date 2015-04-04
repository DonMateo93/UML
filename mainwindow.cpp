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
    Atrybut atrybut1("name","int",wPrivate);
    Atrybut atrybut2("nazwaZ","typ",ND,N,"",false,true,10);
    Atrybut atrybut3("name3","vector",wPrivate);
    operacja.dodajParametr(atrybut1);
    operacja.dodajParametr(atrybut2);
    operacja.dodajParametr(atrybut3);



    Koder* kod = new KoderCpp;
    QString zdekodowany,zakodowany;

    Klasa* klasa = new Klasa("Klasa");
    PrzestrzenNazw* przestrzen = new PrzestrzenNazw("PrzestrzenNazw");
    przestrzen->dodajOperacje(operacja);
    Operacja operacja2("druga","integer",wPublic,przezWskaznik,true,true,true,N,100);
    przestrzen->dodajOperacje(operacja2);
    przestrzen->dodajAtrybut(atrybut1);
    przestrzen->dodajAtrybut(atrybut2);

    PrzestrzenNazw* przestrzen2 = new PrzestrzenNazw("PrzestrzenDruga");
    Atrybut atrybut4("Jasio","integral",wProtected,N,"10",false,false,8);
    Atrybut atrybut5("stasio","intfsdfegral",wPrivate,Jeden,"",false,true,19);

    Operacja operacja3("trzecia","dupa",wPrivate,przezReferencje,true,false,false,JedenLubX);
    operacja3.dodajParametr(atrybut2);

    Operacja operacja4("czwarta","int",wProtected);

    przestrzen2->dodajAtrybut(atrybut4);
    przestrzen2->dodajAtrybut(atrybut5);

    przestrzen2->dodajOperacje(operacja3);
    przestrzen2->dodajOperacje(operacja4);
    przestrzen2->dodajOperacje(operacja);

    QString nazwapliku = "pierwsze.h";

    klasa->dodajAtrybut(atrybut1);
    klasa->dodajAtrybut(atrybut2);
    klasa->dodajAtrybut(atrybut3);
    klasa->dodajAtrybut(atrybut4);
    klasa->dodajAtrybut(atrybut5);

    klasa->dodajOperacje(operacja);
    klasa->dodajOperacje(operacja2);
    klasa->dodajOperacje(operacja3);
    klasa->dodajOperacje(operacja4);

    zakodowany = kod->przygotujBlokTekstuDoWpisaniaElementu(klasa);
    kod->wprowadzElementDoPliku(nazwapliku,przestrzen,NULL);
    kod->wprowadzElementDoPliku(nazwapliku,przestrzen2);
    kod->wprowadzElementDoPliku(nazwapliku,klasa,przestrzen);
    kod->poprawKodWPliku(nazwapliku);
    delete klasa;
    delete przestrzen;
    delete przestrzen2;
    delete kod;


    ui->textEdit->setText(zakodowany);
}

MainWindow::~MainWindow()
{
    delete ui;
}
