#include "koder.h"
#include <QStringList>


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

    if(list[ind1+1] != "}")
    {
        QStringList list2 = list[ind1+1].split(",");
        for(int i = 0; i < list2.size(); i++ )
        {
            zdekodowany = zdekodowany + list2[i] + " ";
        }
    }

    ind1 = list.lastIndexOf(":");

    if(list[ind1+2].contains('0') || list[ind1+2].contains('1')|| list[ind1+2].contains('2')|| list[ind1+2].contains('3')|| list[ind1+2].contains('4')|| list[ind1+2].contains('5')|| list[ind1+2].contains('6')|| list[ind1+2].contains('7')|| list[ind1+2].contains('8')|| list[ind1+2].contains('9'))
    {
        ok = true;
        if( ! ( list[ind1+2].contains('.') || list[ind1+2].contains('.') ) )
            ok2 = true;
    }

    if(list[ind1+2] == "1..*" || list[ind1+2] == "0..1" || list[ind1+2] == "0..*" || ok)
    {
        if(list[ind1+2] == "1..*")
            zdekodowany = zdekodowany + "std::deque<" + list[list.lastIndexOf(":")+1] + "> ";
        else if(list[ind1+2] == "0..*")
            zdekodowany = zdekodowany + "std::deque<" + list[list.lastIndexOf(":")+1] + "> ";
        else if(ok2)
        {
            zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + "[" + list[ind1+2] + "] ";
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
    list2 = str.split(" , ");

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

    return zdekodowany;
}
