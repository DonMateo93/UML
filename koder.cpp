#include "koder.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QString>

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

QString KoderCpp::dekodujOperacje(const Operacja& operacja, QString przedrostekDoCpp)
{
    QString zakodowany;
    QString zdekodowany = "";
    zakodowany << operacja;
    if(zakodowany != "")
    {
        QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
        QString str;
        bool ok = false;
        bool ok2 = false;

        for(int i = 0; i < list.size(); i++ )
        {
            str = str + "\n" + list[i];
        }



        int ind1 = list.lastIndexOf("{");

        if(ind1 != -1)
        {
            if(list[ind1+1] != "}")
            {
                QStringList list2 = list[ind1+1].split(",",QString::SkipEmptyParts);
                for(int i = 0; i < list2.size(); i++ )
                {
                    zdekodowany = zdekodowany + list2[i] + " ";
                }
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
        {
            zdekodowany =zdekodowany + przedrostekDoCpp + list[1] ;
        }
        else
        {
            zdekodowany = zdekodowany + przedrostekDoCpp + list[0];
        }
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
    }

    return zdekodowany;
}

QString KoderCpp::dekodujOperacje(const QString& operacja, QString przedrostekDoCpp)
{
    QString zakodowany = "";
    QString zdekodowany = "";
    if(operacja != "")
    {
        zakodowany = operacja;
        QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
        QString str;
        bool ok = false;
        bool ok2 = false;

        for(int i = 0; i < list.size(); i++ )
        {
            str = str + "\n" + list[i];
        }



        int ind1 = list.lastIndexOf("{");
        if(ind1 != -1)
        {
            if(list[ind1+1] != "}")
            {
                QStringList list2 = list[ind1+1].split(",",QString::SkipEmptyParts);
                for(int i = 0; i < list2.size(); i++ )
                {
                    zdekodowany = zdekodowany + list2[i] + " ";
                }
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
            zdekodowany =zdekodowany + przedrostekDoCpp + list[1];
        else
            zdekodowany =zdekodowany + przedrostekDoCpp + list[0];

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
    }

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

    FilePathAndName.chop(2);
    FilePathAndName += ".cpp";
    QFile PlikZrodlo(FilePathAndName);

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);
            QTextStream stream2(&PlikZrodlo);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(Przestrzen);
            stream << wszystko;

            QString przedrostek = Przestrzen->getNazwa() + "::";
            QString wszystkoCpp = przygotujBlokTekstuDoCpp(Przestrzen, przedrostek);
            stream2 << wszystkoCpp;



            Plik.close();
            PlikZrodlo.close();

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

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);
                QTextStream stream2(&PlikZrodlo);

                QString buffor = in.readAll();
                out << buffor;

                QString przedrostek = DoJakiej->getNazwa() + "::" + Przestrzen->getNazwa() + "::";
                QString wszystkoCpp = przygotujBlokTekstuDoCpp(Przestrzen, przedrostek);
                stream2 << wszystkoCpp;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();
                PlikZrodlo.close();

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

    FilePathAndName.chop(2);
    FilePathAndName += ".cpp";
    QFile PlikZrodlo(FilePathAndName);

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);
            QTextStream stream2(&PlikZrodlo);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(struktura);
            stream << wszystko;

            QString przedrostek = struktura->getNazwa() + "::";
            QString wszystkoCpp = przygotujBlokTekstuDoCpp(struktura, przedrostek);
            stream2 << wszystkoCpp;

            Plik.close();
            PlikZrodlo.close();

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

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);
                QTextStream stream2(&PlikZrodlo);

                QString buffor = in.readAll();
                out << buffor;

                QString przedrostek = DoJakiej->getNazwa() + "::" + struktura->getNazwa() + "::";
                QString wszystkoCpp = przygotujBlokTekstuDoCpp(struktura, przedrostek);
                stream2 << wszystkoCpp;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();
                PlikZrodlo.close();

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

    FilePathAndName.chop(2);
    FilePathAndName += ".cpp";
    QFile PlikZrodlo(FilePathAndName);

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);
            QTextStream stream2(&PlikZrodlo);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(klasa);
            stream << wszystko;

            QString przedrostek = klasa->getNazwa() + "::";
            QString wszystkoCpp = przygotujBlokTekstuDoCpp(klasa, przedrostek);
            stream2 << wszystkoCpp;

            Plik.close();
            PlikZrodlo.close();

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

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);
                QTextStream stream2(&PlikZrodlo);

                QString buffor = in.readAll();
                out << buffor;

                QString przedrostek = DoJakiej->getNazwa() + "::" + klasa->getNazwa() + "::";
                QString wszystkoCpp = przygotujBlokTekstuDoCpp(klasa, przedrostek);
                stream2 << wszystkoCpp;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();
                PlikZrodlo.close();

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


QString KoderCpp::dekodujBlokOperacji(const QString& BlokOperacji, QString przedrostekDoCpp)
{
    QString ZdekodowanyBlok = "";

    if(BlokOperacji != "")
    {
        QStringList ListaOperacji = BlokOperacji.split("\n");

        for(int i = 0; i< ListaOperacji.size(); i++)
        {
            ListaOperacji[i] = dekodujOperacje(ListaOperacji[i], przedrostekDoCpp);
        }

        ZdekodowanyBlok = ListaOperacji.join("\n");
        ZdekodowanyBlok += "\n";
    }

    return ZdekodowanyBlok;
}

QString KoderCpp::dekodujBlokAtrybutow(const QString& BlokAtrybutow, bool CzyZPustymiLiniami)
{
    QString ZdekodowanyBlok = "";
    if(BlokAtrybutow != "")
    {
        QStringList ListaAtrybutow = BlokAtrybutow.split("\n");

        for(int i = 0; i< ListaAtrybutow.size(); i++)
        {
            ListaAtrybutow[i] = dekodujAtrybut(ListaAtrybutow[i]);
        }


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
            zwracana += (ListaPom[i] + ";\n"); //USUNIĘTO \n{\n\n}
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
        QString pom2 = "";

        zwracana += "class " + klasa->getNazwa() + "\n{\n" ;
        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        pom = klasa->getOperacjeOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokOperacji(pom);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

        //----------------------------------------------------------------------------

        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wProtected);
        pom = dekodujBlokAtrybutow(pom,true);

        pom2 = klasa->getOperacjeOSpecyfikatorzeDostepu(wProtected);
        pom2 = dekodujBlokOperacji(pom2);

        if(pom != "" || pom2 != "")
            zwracana += "\nprotected:\n";

        zwracana += pom;

        ListaPom.clear();
        ListaPom = pom2.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

        //----------------------------------------------------------------------------
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
        //----------------------------------------------------------------------------

        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokAtrybutow(pom,true);

        pom2 = klasa->getOperacjeOSpecyfikatorzeDostepu(wPublic);
        pom2 = dekodujBlokOperacji(pom2);

        if(pom != "" || pom2 != "")
            zwracana += "\npublic:\n";

        zwracana += pom;

        ListaPom.clear();
        ListaPom = pom2.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

       //----------------------------------------------------------------------------
//        zwracana += "\npublic:\n";
//        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wPublic);
//        pom = dekodujBlokAtrybutow(pom,true);
//        zwracana += pom;

//        pom = klasa->getOperacjeOSpecyfikatorzeDostepu(wPublic);
//        pom = dekodujBlokOperacji(pom);
//        ListaPom.clear();
//        ListaPom = pom.split("\n", QString::SkipEmptyParts);

//        for(int i = 0; i < ListaPom.size(); i++)
//        {
//            zwracana += (ListaPom[i] + "\n{\n\n}\n");
//        }

       //----------------------------------------------------------------------------

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
        QString pom2 = "";

        zwracana += "struct " + struktura->getNazwa() + "\n{\n" ;
        pom = struktura->getAtrybutyOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        pom = struktura->getOperacjeOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokOperacji(pom);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

        //--------------------------------------------
        pom = struktura->getAtrybutyOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokAtrybutow(pom,true);

        pom2 = struktura->getOperacjeOSpecyfikatorzeDostepu(wPrivate);
        pom2 = dekodujBlokOperacji(pom2);

        if(pom != "" || pom2 != "")
            zwracana += "\nprivate:\n";

        zwracana += pom;


        ListaPom.clear();
        ListaPom = pom2.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

        //--------------------------------------------
//        zwracana += "\nPrivate:\n";
//        pom = struktura->getAtrybutyOSpecyfikatorzeDostepu(wPrivate);
//        pom = dekodujBlokAtrybutow(pom,true);
//        zwracana += pom;

//        pom = struktura->getOperacjeOSpecyfikatorzeDostepu(wPrivate);
//        pom = dekodujBlokOperacji(pom);
//        ListaPom.clear();
//        ListaPom = pom.split("\n", QString::SkipEmptyParts);

//        for(int i = 0; i < ListaPom.size(); i++)
//        {
//            zwracana += (ListaPom[i] + "\n{\n\n}\n");
//        }
        //--------------------------------------------

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

        zwracana += "\n};\n";


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
        pom = dekodujBlokAtrybutow(pom,true);
        QStringList lista = pom.split("\n",QString::SkipEmptyParts);
        pom = lista.join(",\n");

        zwracana += pom;

        zwracana += "\n};\n";


    }else
    {
        //ZGŁOŚ BŁĄD
    }
    return zwracana;
}

void KoderCpp::wprowadzDoPlikuWszystkieElementy(QString FilePathAndName)
{
    //FUNKCJA JEST NIE SKOŃCZONA, NALEŻY DODAĆ PRZESZUKIWANIE RELACJI W CELU ZNALEZIENIA
    //KOINCYDENCJI Z JAKIMIŚ PRZESTRZENIAMI NAZW

    //Przeszukiwanie przestrzeni nazw nie znajdujących się w innych przestrzeniach nazw
    PrzestrzenNazw* nadrzedna = NULL;
    for(int i = 0; i < ListaElementow.size(); i++)
    {
        PrzestrzenNazw* przestrzen = dynamic_cast<PrzestrzenNazw*>(ListaElementow[i]);
        if(przestrzen)
        {
            if(dajAdresNadrzednejPrzestrzeni(przestrzen) == NULL)
            {
                wprowadzElementDoPliku(FilePathAndName, przestrzen);
            }
        }
    }

    for(int k = 0; k < ListaElementow.size(); k ++)
    {
        PrzestrzenNazw* przestrzen = dynamic_cast<PrzestrzenNazw*>(ListaElementow[k]);

        if(przestrzen)
        {
            nadrzedna = dajAdresNadrzednejPrzestrzeni(przestrzen);

            if(nadrzedna != NULL)
            {
               wprowadzElementDoPliku(FilePathAndName,przestrzen,nadrzedna);
            }
        }
    }

    for(int j = 0; j < ListaElementow.size(); j++)
    {
        if(dynamic_cast<Klasa*>(ListaElementow[j]))
        {
            Klasa* klasa = dynamic_cast<Klasa*>(ListaElementow[j]);
            nadrzedna = dajAdresNadrzednejPrzestrzeni(klasa);
            wprowadzElementDoPliku(FilePathAndName,klasa,nadrzedna);

        }else if(dynamic_cast<Struktura*>(ListaElementow[j]))
        {
            Struktura* klasa = dynamic_cast<Struktura*>(ListaElementow[j]);
            nadrzedna = dajAdresNadrzednejPrzestrzeni(klasa);
            wprowadzElementDoPliku(FilePathAndName,klasa,nadrzedna);

        }else if(dynamic_cast<Wyliczenie*>(ListaElementow[j]))
        {
            Wyliczenie* klasa = dynamic_cast<Wyliczenie*>(ListaElementow[j]);
            nadrzedna = dajAdresNadrzednejPrzestrzeni(klasa);
            wprowadzElementDoPliku(FilePathAndName,klasa,nadrzedna);

        }else if(dynamic_cast<Unia*>(ListaElementow[j]))
        {
            Unia* klasa = dynamic_cast<Unia*>(ListaElementow[j]);
            nadrzedna = dajAdresNadrzednejPrzestrzeni(klasa);
            wprowadzElementDoPliku(FilePathAndName,klasa,nadrzedna);
        }
    }
}

void Koder::dodajElementDoListy(Element* element)
{
    bool ok = true;

    for(int i = 0; i < ListaElementow.size(); i++)
    {
        if(ListaElementow[i]->getNazwa() == element->getNazwa())
        {
            ok = false;
            break;
        }
    }

    if(ok)
    {
        ListaElementow.push_back(element);
    }else
    {
        //OBSŁUGA BŁĘDU
    }

}

void KoderCpp::dodajRelacje(Relacja *relacja)
{
// DODAĆ KONTROLĘ WPROWADZANIA
    ListaRelacji.push_back(relacja);
}


PrzestrzenNazw* KoderCpp::dajAdresNadrzednejPrzestrzeni(Element* element)
{
    PrzestrzenNazw* zwrot = NULL;

    if(element != NULL)
    {
        //BARDZO WAŻNE!!!! SPRAWDZIĆ CZY KONCEPCJA ADRESÓW DZIAŁA
        for(int i = 0; i < ListaRelacji.size(); i++)
        {
            if(dynamic_cast<Aggregation*>(ListaRelacji[i]) || dynamic_cast<Composition*>(ListaRelacji[i]))
            {
                if(ListaRelacji[i]->czyZgadzaSieAdresZElementemDrugim(element))
                {
                    if(ListaRelacji[i]->czyPierwszyToPrzestrzen())
                    {
                        zwrot = dynamic_cast<PrzestrzenNazw*>(ListaRelacji[i]->dajAdresPierwszy());
                        break;
                    }
                }
            }
        }
    }

    return zwrot;
}

QString KoderCpp::przygotujBlokTekstuDoCpp(PrzestrzenNazw* przestrzen, QString przedrostekDoCpp)
{
    QString zwracana = "";
    if(przestrzen != NULL)
    {
        QString pom = "";


        pom = przestrzen->getWszystkieOperacje();
        pom = dekodujBlokOperacji(pom, przedrostekDoCpp);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n\n");
        }

    }else
    {
        //ZGŁOŚ BŁĄD
    }

    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoCpp(Klasa* klasa, QString przedrostekDoCpp)
{
    QString zwracana = "";
    if(klasa != NULL)
    {
        QString pom = "";


        pom = klasa->getWszystkieOperacje();
        pom = dekodujBlokOperacji(pom, przedrostekDoCpp);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n\n");
        }

    }else
    {
        //ZGŁOŚ BŁĄD
    }

    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoCpp(Struktura* struktura, QString przedrostekDoCpp)
{
    QString zwracana = "";
    if(struktura != NULL)
    {
        QString pom = "";


        pom = struktura->getWszystkieOperacje();
        pom = dekodujBlokOperacji(pom, przedrostekDoCpp);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n\n");
        }

    }else
    {
        //ZGŁOŚ BŁĄD
    }

    return zwracana;
}

void KoderCpp::wprowadzDoPlikuWszyskieRelacje(QString FilePathAndName)
{

}












