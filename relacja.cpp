#include "relacja.h"

Relacja::~Relacja()
{

}

bool Relacja::czyZgadzaSieAdresZElementemDrugim(Element* element)
{
    if(element == Drugi)
    {
        return true;
    }else
    {
        return false;
    }
}

bool Relacja::czyZgadzaSieAdresZElementemPierwszym(Element* element)
{
    if(element == Pierwszy)
    {
        return true;
    }else
    {
        return false;
    }
}

bool Relacja::czyPierwszyToPrzestrzen()
{
    if(dynamic_cast<PrzestrzenNazw*>(Pierwszy))
    {
        return true;
    }else
    {
        return false;
    }
}

