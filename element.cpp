#include "element.h"

Element::~Element()
{

}

int Element::IleElementow = 0;

QString&
operator<<(QString& wyjscie, const ParametrOperacji parOp)
{
    wyjscie = "";

    wyjscie = parOp.Nazwa + " : ";

    if(parOp.CzyConst)
        wyjscie = wyjscie + "const ";

    wyjscie = wyjscie + parOp.Typ;

    if(parOp.CzyDomyslnaWartosc)
        wyjscie = wyjscie + "=" + parOp.DomyslnaWartosc;

    switch (parOp.Przekazanie)
    {
        case przezReferencje:
            wyjscie = wyjscie + "&";
            break;
        case przezWskaznik:
            wyjscie = wyjscie + "*";
            break;
    }

    return wyjscie;
}

void Element::zmienNazwe(QString NowaNazwa)
{
    NazwaElementu = NowaNazwa;
}

QString Element::getNazwa()
{
    return NazwaElementu;
}

QString&
operator<<(QString& napis, Operacja Op)
{
    napis = "";
    QString pomoc = "", pomoc2,tmp;

    switch(Op.Visibility)
    {
    case wPrivate:
        pomoc2 = "- ";
        break;
    case wPublic:
        pomoc2 = "+ ";
        break;
    case wProtected:
        pomoc2 = "# ";
        break;
    case wPackage:
        pomoc2 = "~ ";
        break;
    case ND:
        pomoc2 = "";
        break;
    }

    for(int i = 0; i < Op.ListaParamMetod.size(); i++)
    {
        tmp<<Op.ListaParamMetod[i];
        if(tmp[0] == '#' || tmp[0] == '~' || tmp[0] == '-' || tmp[0] == '+' || tmp[0] == '^' )
            tmp.remove(0,2);
        pomoc = pomoc + tmp;
        if(i<Op.ListaParamMetod.size() - 1)
        {
            pomoc = pomoc + " , ";
        }
    }

    napis = pomoc2 + Op.Nazwa + " ( " + pomoc + " ) : ";


    switch (Op.Ile)
    {
    case Jeden:
        pomoc2 = "";
        break;
    case JedenLubX:
        pomoc2 = " 1..*";
        break;
    case ZeroLub1:
        pomoc2 = " 0..1";
        break;
    case ZeroLubX:
        pomoc2 = " 0..*";
        break;
    case N:
        pomoc2 = " " + QString::number(Op.n);
        break;
    case WiecejNizN:
        pomoc2 = " " + QString::number(Op.n) + "..*";
        break;
    }

    napis = napis + Op.Typ;

    switch (Op.Przekaz)
    {
        case przezReferencje:
            napis = napis + "&";
            break;
        case przezWskaznik:
            napis = napis + "*";
            break;
    }

    napis = napis + pomoc2;

    if(Op.Komentarz != "")
        napis = napis + " { " + Op.Komentarz + " } ";

    return napis;
}

KontenerOperacji::~KontenerOperacji()
{
    for(int i = 0; i < WektorOperacji.size(); i++)
    {
        delete WektorOperacji[i];
    }

    WektorOperacji.clear();
}


QString&
operator<<(QString& napis, Atrybut atrybut)
{
    napis = "";
    QString pomoc2;
    switch (atrybut.Visibility)
    {
    case wPrivate:
        napis = "-";
        break;
    case wPublic:
        napis = "+";
        break;
    case wProtected:
        napis = "#";
        break;
    case wPackage:
        napis = "~";
        break;
    case ND:
        napis = "";
        break;
    }

    if(napis != "")
        napis = napis +" " + atrybut.Nazwa + " : " + atrybut.Typ;
    else
        napis = napis + atrybut.Nazwa + " : " + atrybut.Typ;


    switch (atrybut.Ile)
    {
    case Jeden:
        pomoc2 = "";
        break;
    case JedenLubX:
        pomoc2 = " 1..*";
        break;
    case ZeroLub1:
        pomoc2 = " 0..1";
        break;
    case ZeroLubX:
        pomoc2 = " 0..*";
        break;
    case N:
        pomoc2 = " " + QString::number(atrybut.n);
        break;
    case WiecejNizN:
        pomoc2 = " " + QString::number(atrybut.n) + "..*";
        break;
    }

    napis = napis + pomoc2;

    if(atrybut.DomyslnaWartosc != "")
        napis = napis + " = " + atrybut.DomyslnaWartosc;

    if(atrybut.Komentarz != "")
        napis = napis + " { " + atrybut.Komentarz + " }";

    return napis;
}

void Operacja::aktualizujKomentarz()
{
    Komentarz = "";
    if(CzyConst || CzyStatyczna)
    {
        if(CzyWirtualna)
            Komentarz = Komentarz + "virtual";

        if(CzyStatyczna)
        {
            if(Komentarz != "")
                Komentarz = Komentarz + ",static";
            else
                Komentarz = Komentarz + "static";
        }

        if(CzyConst)
        {
            if(Komentarz != "")
                Komentarz = Komentarz + ",const";
            else
                Komentarz = Komentarz + "const";
        }
    }
}

void Atrybut::aktualizujKomentarz()
{
    Komentarz = "";
    if(CzyConst || CzyStatyczna)
    {
        if(CzyStatyczna)
            Komentarz = Komentarz + "static";

        if(CzyConst)
        {
            if(Komentarz != "")
                Komentarz = Komentarz + ",const";
            else
                Komentarz = Komentarz + "const";
        }
    }

}


int Operacja::dodajParametr(Atrybut Parametr)
{
    ListaParamMetod.push_back(Parametr);
    return int(1);
}

QString Element::getWszystkieAtrybuty()
{
    QString WszystkieAtrybuty = "";
    for(int i = 0; i < WektorAtrybutow.size(); i++)
    {
        WszystkieAtrybuty << WektorAtrybutow[i];

        if(i < WektorAtrybutow.size() - 1)
            WszystkieAtrybuty += "\n";
    }

    return WszystkieAtrybuty;

}

void ElementZOperacjami::dodajOperacje(const Operacja& operacja)
{   //TU I W PODOBNYCH DODAĆ SPRAWDZANIE CZY SIĘ NIE POWTARZA
    WektorOperacji.push_back(operacja);
}

QString ElementZOperacjami::getWszystkieOperacje()
{
    QString WszystkieOperacje = "";
    QString pom;
    for(int i = 0; i < WektorOperacji.size(); i++)
    {
        pom << WektorOperacji[i];
        WszystkieOperacje += pom;

        if(i < WektorOperacji.size() - 1)
            WszystkieOperacje += "\n";
    }

    return WszystkieOperacje;
}
