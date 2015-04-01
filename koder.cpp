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

    zdekodowany = zdekodowany  + ");";

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

    zdekodowany = zdekodowany  + ");";

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

    if(DoJakiej == NULL)
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);

            stream << "namespace " + Przestrzen->getNazwa() + "\n{\n" ;


            pom = Przestrzen->getWszystkieAtrybuty();
            pom = dekodujBlokAtrybutow(pom,true);
            stream << pom;


            pom = Przestrzen->getWszystkieOperacje();
            pom = dekodujBlokOperacji(pom);
            QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

            for(int i = 0; i < ListaPom.size(); i++)
            {
                stream<<(ListaPom[i] + "\n{\n\n}\n");
            }

            stream << "\n}\n";

            Plik.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else
    {

    }
}

void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, Klasa* klasa)
{
    klasa->zmienNazwe("ZmienionoKlasa");
}


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
