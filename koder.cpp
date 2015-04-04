#include "koder.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QString>


Koder::Koder()
{

}

Koder::~Koder()
{

}

QString KoderCpp::dekodujAtrybut(const Atrybut& atrybut)
{
    // atrybut = + Nazwa : Typ licznosc = 0 {virtual, const etc.}
    QString zakodowany;
    zakodowany << atrybut;
    QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
    QString zdekodowany = "";
    QString str;
    bool ok = false;
    bool ok2 = false;

    if(zakodowany != "")
    {
        //DO WYWALENIA
        for(int i = 0; i < list.size(); i++ )
        {
            str = str + "\n" + list[i];
        }



        int ind1 = list.indexOf("{");

        if(list[ind1+1] != "}" && ind1 != -1)
        {
            QStringList list2 = list[ind1+1].split(",");
            for(int i = 0; i < list2.size(); i++ )
            {
                zdekodowany = zdekodowany + list2[i] + " ";
            }
        }

        ind1 = list.indexOf(":");

        if(ind1 + 2 < list.size())
        {

            if(list[ind1+2].contains('0') || list[ind1+2].contains('1')|| list[ind1+2].contains('2')|| list[ind1+2].contains('3')|| list[ind1+2].contains('4')|| list[ind1+2].contains('5')|| list[ind1+2].contains('6')|| list[ind1+2].contains('7')|| list[ind1+2].contains('8')|| list[ind1+2].contains('9'))
            {
                ok = true;
                if( ! ( list[ind1+2].contains('.') || list[ind1+2].contains('.') ) )
                    ok2 = true;
            }

            if(list[ind1+2] == "1..*" || list[ind1+2] == "0..1" || list[ind1+2] == "0..*" || ok)
            {
                if(list[ind1+2] == "1..*")
                    zdekodowany = zdekodowany + "std::deque<" + list[list.indexOf(":")+1] + "> ";
                else if(list[ind1+2] == "0..*")
                    zdekodowany = zdekodowany + "std::deque<" + list[list.indexOf(":")+1] + "> ";
                else if(ok2)
                {
                    zdekodowany = zdekodowany + list[list.indexOf(":")+1] + "[" + list[ind1+2] + "] ";
                }
            }else
            {
                zdekodowany = zdekodowany + list[list.indexOf(":")+1];
            }
        }else
        {
            zdekodowany = zdekodowany + list[list.indexOf(":")+1];
        }

        if(zdekodowany[zdekodowany.size()-2] == ' ')
            zdekodowany = zdekodowany + list[list.indexOf(":")-1];
        else
            zdekodowany = zdekodowany + " " + list[list.indexOf(":")-1];

        if(list.contains("="))
        {
            zdekodowany = zdekodowany + " = " + list[list.indexOf("=") + 1] + " ";
        }

        zdekodowany = zdekodowany + ";";
    }else
    {
        //ZASTANOWIĆ SIĘ CZY NIE DODAĆ OBSŁUGI BŁĘDÓW
        zdekodowany = "";
    }

    return zdekodowany;
}

void KoderCpp::generujKodDoPliku(QString path = "")
{

}

QString KoderCpp::dekodujOperacje(const Operacja& operacja)
{
    QString zakodowany;
    zakodowany << operacja;
    QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
    QString zdekodowany = "";
    QString str;
    bool ok = false;
    bool ok2 = false;

    for(int i = 0; i < list.size(); i++ )
    {
        str = str + "\n" + list[i];
    }



    int ind1 = list.lastIndexOf("{");

    if(list[ind1+1] != "}" && ind1 != -1)
    {
        QStringList list2 = list[ind1+1].split(",",QString::SkipEmptyParts);
        for(int i = 0; i < list2.size(); i++ )
        {
            zdekodowany = zdekodowany + list2[i] + " ";
        }
    }

    ind1 = list.lastIndexOf(":");

    //SPRAWDZANIE MULTIPLICITY
    if(ind1+2<list.size())
    {
        if(list[ind1+2].contains('0') || list[ind1+2].contains('1')|| list[ind1+2].contains('2')|| list[ind1+2].contains('3')|| list[ind1+2].contains('4')|| list[ind1+2].contains('5')|| list[ind1+2].contains('6')|| list[ind1+2].contains('7')|| list[ind1+2].contains('8')|| list[ind1+2].contains('9'))
        {
            ok = true;
            if( ! ( list[ind1+2].contains('.') || list[ind1+2].contains('.') ) )
                ok2 = true;
        }

        if(list[ind1+2] == "1..*" || list[ind1+2] == "0..1" || list[ind1+2] == "0..*" || ok)
        {
            QString pomoCh = list[list.lastIndexOf(":")+1][list[list.lastIndexOf(":")+1].size() - 1]; //Ostatni znak w stringu przechowującym typ(może to być * lub &)
            if(pomoCh == "*" || pomoCh == "&")
            {
                list[list.lastIndexOf(":")+1].chop(1);
            }
            else
                pomoCh = "";
            if(list[ind1+2] == "1..*")
                zdekodowany = zdekodowany + "std::deque<" + list[list.lastIndexOf(":")+1] + ">" + pomoCh + " ";
            else if(list[ind1+2] == "0..*")
                zdekodowany = zdekodowany + "std::deque<" + list[list.lastIndexOf(":")+1] + ">" + pomoCh + " ";
            else if(ok2)
            {
                zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + "[" + list[ind1+2] + "] ";
            }
        }else
        {
            zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + " ";
        }
    }else
    {
        zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + " ";
    }

    if(list[0] == "#" || list[0] == "~" || list[0] == "+" || list[0] == "-" )
        zdekodowany = zdekodowany + list[1];
    else
        zdekodowany = zdekodowany + list[0];

    ind1 = list.indexOf("(");
    int ind2 = list.indexOf(")");

    QStringList list2;
    list2.clear();

    for(int j = 0; j < (ind2 - ind1) - 1; j++)
    {
        list2.push_back(list[ind1 + j + 1]);
    }

    zdekodowany = zdekodowany + "(";

    str = "";
    str = list2.join(" ");
    list2.clear();
    list2 = str.split(" , ",QString::SkipEmptyParts);

    str = "";
    QString pom = "";

    for(int k = 0; k < list2.size(); k++)
    {
        pom = list2[k];
        str = dekodujAtrybut(pom);
        str.chop(1);
        zdekodowany = zdekodowany + str;
        if(k<list2.size() - 1)
            zdekodowany = zdekodowany + ", ";
    }

    zdekodowany = zdekodowany  + ")";

    return zdekodowany;
}

QString KoderCpp::dekodujOperacje(const QString& operacja)
{
    QString zakodowany;
    zakodowany = operacja;
    QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
    QString zdekodowany = "";
    QString str;
    bool ok = false;
    bool ok2 = false;

    for(int i = 0; i < list.size(); i++ )
    {
        str = str + "\n" + list[i];
    }



    int ind1 = list.lastIndexOf("{");

    if(list[ind1+1] != "}" && ind1 != -1)
    {
        QStringList list2 = list[ind1+1].split(",",QString::SkipEmptyParts);
        for(int i = 0; i < list2.size(); i++ )
        {
            zdekodowany = zdekodowany + list2[i] + " ";
        }
    }

    ind1 = list.lastIndexOf(":");

    //SPRAWDZANIE MULTIPLICITY
    if(ind1+2<list.size())
    {
        if(list[ind1+2].contains('0') || list[ind1+2].contains('1')|| list[ind1+2].contains('2')|| list[ind1+2].contains('3')|| list[ind1+2].contains('4')|| list[ind1+2].contains('5')|| list[ind1+2].contains('6')|| list[ind1+2].contains('7')|| list[ind1+2].contains('8')|| list[ind1+2].contains('9'))
        {
            ok = true;
            if( ! ( list[ind1+2].contains('.') || list[ind1+2].contains('.') ) )
                ok2 = true;
        }

        if(list[ind1+2] == "1..*" || list[ind1+2] == "0..1" || list[ind1+2] == "0..*" || ok)
        {
            QString pomoCh = list[list.lastIndexOf(":")+1][list[list.lastIndexOf(":")+1].size() - 1]; //Ostatni znak w stringu przechowującym typ(może to być * lub &)
            if(pomoCh == "*" || pomoCh == "&")
            {
                list[list.lastIndexOf(":")+1].chop(1);
            }
            else
                pomoCh = "";
            if(list[ind1+2] == "1..*")
                zdekodowany = zdekodowany + "std::deque<" + list[list.lastIndexOf(":")+1] + ">" + pomoCh + " ";
            else if(list[ind1+2] == "0..*")
                zdekodowany = zdekodowany + "std::deque<" + list[list.lastIndexOf(":")+1] + ">" + pomoCh + " ";
            else if(ok2)
            {
                zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + "[" + list[ind1+2] + "] ";
            }
        }else
        {
            zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + " ";
        }
    }else
    {
        zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + " ";
    }

    if(list[0] == "#" || list[0] == "~" || list[0] == "+" || list[0] == "-" )
        zdekodowany = zdekodowany + list[1];
    else
        zdekodowany = zdekodowany + list[0];

    ind1 = list.indexOf("(");
    int ind2 = list.indexOf(")");

    QStringList list2;
    list2.clear();

    for(int j = 0; j < (ind2 - ind1) - 1; j++)
    {
        list2.push_back(list[ind1 + j + 1]);
    }

    zdekodowany = zdekodowany + "(";

    str = "";
    str = list2.join(" ");
    list2.clear();
    list2 = str.split(" , ",QString::SkipEmptyParts);

    str = "";
    QString pom = "";

    for(int k = 0; k < list2.size(); k++)
    {
        pom = list2[k];
        str = dekodujAtrybut(pom);
        str.chop(1);
        zdekodowany = zdekodowany + str;
        if(k<list2.size() - 1)
            zdekodowany = zdekodowany + ", ";
    }

    zdekodowany = zdekodowany  + ")";

    return zdekodowany;
}


QString KoderCpp::dekodujAtrybut(const QString& atrybut)
{
    // atrybut = + Nazwa : Typ licznosc = 0 {virtual, const etc.}
    QString zakodowany;
    zakodowany = atrybut;
    QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
    QString zdekodowany = "";
    QString str;
    bool ok = false;
    bool ok2 = false;

    if(zakodowany != "")
    {
        //DO WYWALENIA
        for(int i = 0; i < list.size(); i++ )
        {
            str = str + "\n" + list[i];
        }



        int ind1 = list.indexOf("{");

        if(list[ind1+1] != "}" && ind1 != -1)
        {
            QStringList list2 = list[ind1+1].split(",");
            for(int i = 0; i < list2.size(); i++ )
            {
                zdekodowany = zdekodowany + list2[i] + " ";
            }
        }

        ind1 = list.indexOf(":");

        if(ind1 + 2 < list.size())
        {

            if(list[ind1+2].contains('0') || list[ind1+2].contains('1')|| list[ind1+2].contains('2')|| list[ind1+2].contains('3')|| list[ind1+2].contains('4')|| list[ind1+2].contains('5')|| list[ind1+2].contains('6')|| list[ind1+2].contains('7')|| list[ind1+2].contains('8')|| list[ind1+2].contains('9'))
            {
                ok = true;
                if( ! ( list[ind1+2].contains('.') || list[ind1+2].contains('.') ) )
                    ok2 = true;
            }

            if(list[ind1+2] == "1..*" || list[ind1+2] == "0..1" || list[ind1+2] == "0..*" || ok)
            {
                if(list[ind1+2] == "1..*")
                    zdekodowany = zdekodowany + "std::deque<" + list[list.indexOf(":")+1] + "> ";
                else if(list[ind1+2] == "0..*")
                    zdekodowany = zdekodowany + "std::deque<" + list[list.indexOf(":")+1] + "> ";
                else if(ok2)
                {
                    zdekodowany = zdekodowany + list[list.indexOf(":")+1] + "[" + list[ind1+2] + "] ";
                }
            }else
            {
                zdekodowany = zdekodowany + list[list.indexOf(":")+1];
            }
        }else
        {
            zdekodowany = zdekodowany + list[list.indexOf(":")+1];
        }

        if(zdekodowany[zdekodowany.size()-2] == ' ')
            zdekodowany = zdekodowany + list[list.indexOf(":")-1];
        else
            zdekodowany = zdekodowany + " " + list[list.indexOf(":")-1];

        if(list.contains("="))
        {
            zdekodowany = zdekodowany + " = " + list[list.indexOf("=") + 1] + " ";
        }

        zdekodowany = zdekodowany + ";";
    }else
    {
        //ZASTANOWIĆ SIĘ CZY NIE DODAĆ OBSŁUGI BŁĘDÓW
        zdekodowany = "";
    }

    return zdekodowany;
}

void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, PrzestrzenNazw* Przestrzen, PrzestrzenNazw* DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(Przestrzen);
            stream << wszystko;

//            stream << "namespace " + Przestrzen->getNazwa() + "\n{\n" ;


//            pom = Przestrzen->getWszystkieAtrybuty();
//            pom = dekodujBlokAtrybutow(pom,true);
//            stream << pom;


//            pom = Przestrzen->getWszystkieOperacje();
//            pom = dekodujBlokOperacji(pom);
//            QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

//            for(int i = 0; i < ListaPom.size(); i++)
//            {
//                stream<<(ListaPom[i] + "\n{\n\n}\n");
//            }

//            stream << "\n}\n";

            Plik.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(Przestrzen);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);

                QString buffor = in.readAll();
                out << buffor;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }
}

void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, Struktura* struktura, PrzestrzenNazw* DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(struktura);
            stream << wszystko;

            Plik.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(struktura);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);

                QString buffor = in.readAll();
                out << buffor;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }
}

void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, Wyliczenie* wyliczenie, PrzestrzenNazw* DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(wyliczenie);
            stream << wszystko;

            Plik.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(wyliczenie);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);

                QString buffor = in.readAll();
                out << buffor;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }
}

void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, Unia* unia, PrzestrzenNazw* DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(unia);
            stream << wszystko;

            Plik.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(unia);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);

                QString buffor = in.readAll();
                out << buffor;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }
}


void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, Klasa* klasa, PrzestrzenNazw *DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(klasa);
            stream << wszystko;

            Plik.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(klasa);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);

                QString buffor = in.readAll();
                out << buffor;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }}


QString KoderCpp::dekodujBlokOperacji(const QString& BlokOperacji)
{
    QStringList ListaOperacji = BlokOperacji.split("\n");

    for(int i = 0; i< ListaOperacji.size(); i++)
    {
        ListaOperacji[i] = dekodujOperacje(ListaOperacji[i]);
    }

    QString ZdekodowanyBlok;
    ZdekodowanyBlok = ListaOperacji.join("\n");
    ZdekodowanyBlok += "\n";

    return ZdekodowanyBlok;

}
QString KoderCpp::dekodujBlokAtrybutow(const QString& BlokAtrybutow, bool CzyZPustymiLiniami)
{
    QStringList ListaAtrybutow = BlokAtrybutow.split("\n");

    for(int i = 0; i< ListaAtrybutow.size(); i++)
    {
        ListaAtrybutow[i] = dekodujAtrybut(ListaAtrybutow[i]);
    }

    QString ZdekodowanyBlok;
    if(CzyZPustymiLiniami)
    {
        ZdekodowanyBlok = ListaAtrybutow.join("\n\n");
        ZdekodowanyBlok += "\n\n";
    }
    else
    {
        ZdekodowanyBlok = ListaAtrybutow.join("\n");
        ZdekodowanyBlok += "\n";

    }

    return ZdekodowanyBlok;
}

void KoderCpp::poprawKodWPliku(const QString &PathAndName)
{
    //UNIEMOŻLIWIĆ WPISANIE PLIK POMOCNICZY W FILE DIALOG
    QFile Plik(PathAndName);
    QFile PlikPom("PlikPomocniczy.txt");
    int ileNawiasow = 0;
    bool ok = true;
    bool pomocB = false;


    if(Plik.open(QIODevice::ReadOnly|QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
    {
        if(Plik.size() != 0)
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString linia;
            QString pomoc = "";

            linia = in.readLine();
            while(!linia.isNull())
            {
                linia.remove('\t');
                if(linia.contains("{"))
                {
                    pomoc = "";

                    for(int i = 0; i < ileNawiasow; i++)
                    {
                        pomoc += "\t";
                    }

                    linia = pomoc + linia + "\n\n";
                    ileNawiasow++;
                    pomocB = false;
                }else if(linia.contains("}"))
                {
                    ileNawiasow--;

                    pomoc = "";

                    for(int i = 0; i < ileNawiasow; i++)
                    {
                        pomoc += "\t";
                    }
                    linia = pomoc + linia + "\n\n";
                    pomocB = false;
                }else if(linia == "")
                {

                }
                else if(linia.contains("private") || linia.contains("public") || linia.contains("protected"))
                {
                    if(pomocB)
                        linia = "\n" + linia;

                    pomoc = "";
                    for(int i = 0; i < ileNawiasow -1; i ++)
                        pomoc += "\t";

                    linia += "\n";
                    linia = pomoc + linia;
                    pomocB = false;
                }
                else
                {
                    pomoc = "";

                    for(int i = 0; i < ileNawiasow; i++)
                    {
                        pomoc += "\t";
                    }

                    if(pomocB)
                        linia = "\n" + pomoc + linia + "\n";
                    else
                        linia = pomoc + linia + "\n";

                    pomocB = true;
                }

                out << linia;
                linia = in.readLine();
            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Truncate)| PlikPom.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                QTextStream in2(&PlikPom);
                QTextStream out2(&Plik);

                if(PlikPom.size() != 0)
                {
                    linia = in2.readLine();
                    while(!linia.isNull())
                    {
                        out2 << linia+ "\n";
                        linia = in2.readLine();
                    }

                    Plik.close();
                    PlikPom.close();
                    PlikPom.remove();

                }else
                    ok = false;

            }else
                ok = false;
        }else
            ok = false;
    }else
        ok = false;

    if(!ok)
    {
        //OBSŁUGA BŁĘDÓW
    }
}

// Zawiera wszystkie dane odnosnie elemetnu w jednym stringu gotowym do wpisania do pliku
QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(PrzestrzenNazw* Przestrzen)
{
    QString zwracana = "";
    if(Przestrzen != NULL)
    {
        QString pom = "";
        zwracana += "namespace " + Przestrzen->getNazwa() + "\n{\n" ;


        pom = Przestrzen->getWszystkieAtrybuty();
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;


        pom = Przestrzen->getWszystkieOperacje();
        pom = dekodujBlokOperacji(pom);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n");
        }

        zwracana += "\n}\n";


    }else
    {
        //ZGŁOŚ BŁĄD
    }
    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(Klasa* klasa)
{
    QString zwracana = "";

    if(klasa != NULL)
    {
        QString pom = "";

        zwracana += "class " + klasa->getNazwa() + "\n{\n" ;
        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        pom = klasa->getOperacjeOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokOperacji(pom);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n");
        }

        zwracana += "\nprotected:\n";
        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wProtected);
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        pom = klasa->getOperacjeOSpecyfikatorzeDostepu(wProtected);
        pom = dekodujBlokOperacji(pom);
        ListaPom.clear();
        ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n");
        }

        zwracana += "\npublic:\n";
        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        pom = klasa->getOperacjeOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokOperacji(pom);
        ListaPom.clear();
        ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n");
        }

        zwracana += "\n};\n";


    }else
    {
        //ZGłOŚ BŁĄD
    }

    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(Struktura* struktura)
{
    QString zwracana = "";

    if(struktura != NULL)
    {
        QString pom = "";

        zwracana += "struct " + struktura->getNazwa() + "\n{\n" ;
        pom = struktura->getAtrybutyOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        pom = struktura->getOperacjeOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokOperacji(pom);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n");
        }

//        zwracana += "\nprotected:\n";
//        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wProtected);
//        pom = dekodujBlokAtrybutow(pom,true);
//        zwracana += pom;

//        pom = klasa->getOperacjeOSpecyfikatorzeDostepu(wProtected);
//        pom = dekodujBlokOperacji(pom);
//        ListaPom.clear();
//        ListaPom = pom.split("\n", QString::SkipEmptyParts);

//        for(int i = 0; i < ListaPom.size(); i++)
//        {
//            zwracana += (ListaPom[i] + "\n{\n\n}\n");
//        }

        zwracana += "\nPrivate:\n";
        pom = struktura->getAtrybutyOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        pom = struktura->getOperacjeOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokOperacji(pom);
        ListaPom.clear();
        ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n");
        }

        zwracana += "\n};\n";


    }else
    {
        //ZGłOŚ BŁĄD
    }

    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(Unia* unia)
{
    QString zwracana = "";
    if(unia != NULL)
    {
        QString pom = "";
        zwracana += "union " + unia->getNazwa() + "\n{\n" ;


        pom = unia->getWszystkieAtrybuty();
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        zwracana += "\n}\n";


    }else
    {
        //ZGŁOŚ BŁĄD
    }
    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(Wyliczenie* wyliczenie)
{
    QString zwracana = "";
    if(wyliczenie != NULL)
    {
        QString pom = "";
        zwracana += "enum " + wyliczenie->getNazwa() + "\n{\n" ;


        pom = wyliczenie->getWszystkieAtrybuty();
        QStringList lista = pom.split("\n",QString::SkipEmptyParts);
        pom = lista.join(",\n");

        zwracana += pom;

        zwracana += "\n}\n";


    }else
    {
        //ZGŁOŚ BŁĄD
    }
    return zwracana;
}



