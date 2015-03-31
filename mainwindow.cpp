#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <C:\Users\avans\Documents\UML\element.h>
#include <C:\Users\avans\Documents\UML\koder.h>

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


    KoderCpp* koder = new KoderCpp;
    Koder* kod = koder;
    QString zdekodowany,zakodowany;

    Klasa* klasa = new Klasa("Klasa");
    PrzestrzenNazw* przestrzen = new PrzestrzenNazw("PrzestrzenNazw");
    przestrzen->dodajOperacje(operacja);
    Operacja operacja2("druga","integer",wPublic,przezWskaznik,true,true,true,N,100);
    przestrzen->dodajOperacje(operacja2);
//    Element* element = klasa;
//    koder->wprowadzElementDoPliku("nic",element);
//    zdekodowany = element->getNazwa();

//    element = przestrzen;
//    koder->wprowadzElementDoPliku("nic",element);
//    zakodowany = element->getNazwa();

    zakodowany = przestrzen->getWszystkieOperacje();

    delete klasa;
    delete przestrzen;
    delete koder;

    ui->textEdit->setText(zakodowany);
}

MainWindow::~MainWindow()
{
    delete ui;
}
