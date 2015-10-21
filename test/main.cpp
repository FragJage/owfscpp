#include <iostream>
#include <string>
#include <algorithm>
#include "owfscpp.h"

using namespace std;

#define COULEUR_VERTE 1
#define COULEUR_ROUGE 2
#define COULEUR_INVERSE 3
#define COULEUR_NORMALE 4

void EcrireEnCouleur(int couleur, string msg);
void Titre(string myTitre);
void Resultat(string myTest, bool myResult);
void TestsUnitaire(owfscpp owfsClient, bool persistence);

#ifdef WIN32
#include <Windows.h>
void EcrireEnCouleur(int couleur, string msg)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(couleur)
    {
        case COULEUR_VERTE  :
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case COULEUR_ROUGE  :
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        case COULEUR_INVERSE:
            SetConsoleTextAttribute(consoleHandle, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
            break;
        case COULEUR_NORMALE:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
            break;
        default:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    }
    cout << msg;
}
#endif // WIN

#ifdef __linux__
void EcrireEnCouleur(int couleur, string msg)
{
    switch(couleur)
    {
        case COULEUR_VERTE  :
            printf("\033[32m");
            break;
        case COULEUR_ROUGE  :
            printf("\033[31m");
            break;
        case COULEUR_INVERSE:
            printf("\033[30;47m");
            break;
        case COULEUR_NORMALE:
            printf("\033[0m");
            break;
        default:
            printf("\033[0m");
    }
    cout << msg;
}
#endif // LINUX

void Titre(string myTitre)
{
    string complete(60, '°');

    cout << endl;
    complete = complete.substr(0, 60-myTitre.length());
    EcrireEnCouleur(COULEUR_INVERSE, "°°° ");
    EcrireEnCouleur(COULEUR_INVERSE, myTitre);
    EcrireEnCouleur(COULEUR_INVERSE, " ");
    EcrireEnCouleur(COULEUR_INVERSE, complete);
    EcrireEnCouleur(COULEUR_NORMALE, "");
    cout << endl;
}

void Resultat(string myTest, bool myResult)
{
    cout << " - " << myTest << " : ";

    if(myResult)
        EcrireEnCouleur(COULEUR_VERTE, "OK :-)");
    else
        EcrireEnCouleur(COULEUR_ROUGE, "KO :-(");
    EcrireEnCouleur(COULEUR_NORMALE, "");
    cout << endl;
}

void TestsUnitaire(owfscpp owfsClient, bool persistence)
{
    list<string> lstDir;
    list<string> lstDirAll;
    list<string>::iterator iDir;
    list<string>::iterator iDirEnd;
    string TemperatureDevice;
    string PIODevice;
    string sValue;
    string sLstDir;
    string sLstDirSlash;
    float fValue;
    int iValue;
    unsigned flags;
    bool ok,ok2;


    if(persistence)
        Titre("Test avec connexion persistante");
    else
        Titre("Test avec connexion simple");

    if(persistence) owfsClient.SetOwserverFlag(owfsClient.Persistence, true);

    lstDir = owfsClient.Dir("/");
    Resultat("Test de la methode Dir",  lstDir.empty()==false);
    lstDirAll = owfsClient.DirAll("/");
    Resultat("Test de la methode DirAll",  lstDir.size()==lstDirAll.size());
    lstDirAll = owfsClient.DirAllSlash("/");
    Resultat("Test de la methode DirAllSlash",  lstDir.size()==lstDirAll.size());

    iDirEnd = lstDir.end();
    for(iDir = lstDir.begin(); iDir != iDirEnd; ++iDir)
    {
        sValue = (*iDir).substr(1,2);
        if((TemperatureDevice=="")&&((sValue=="10")||(sValue=="22")||(sValue=="28")))
            TemperatureDevice = *iDir;

        if((PIODevice=="")&&(sValue=="12"))
            PIODevice = *iDir;

        sLstDir += *iDir+",";
        sLstDirSlash += *iDir+"/,";
    }
    sLstDir.erase(sLstDir.size()-1);
    sLstDirSlash.erase(sLstDirSlash.size()-1);

    sValue = owfsClient.Read(TemperatureDevice+"/temperature9");
    fValue = atof(sValue.c_str());
    iValue = int(fValue*10+0.5);
    ok = true;
    if(iValue==0) ok = false;       //Modéremment risqué
    if(iValue<-550) ok = false;
    if(iValue>1250) ok = false;
    Resultat("Test de la methode Read", ok);

    ok = owfsClient.Present(TemperatureDevice);
    ok2 = owfsClient.Present(TemperatureDevice+"X");
    Resultat("Test de la methode Present", ok&(!ok2));

    sValue = owfsClient.Get("/");
    Resultat("Test 1 de la methode Get", sValue==sLstDir);
    sValue = owfsClient.Get(TemperatureDevice+"/temperature9");
    Resultat("Test 2 de la methode Get", int(atof(sValue.c_str())*10+0.5)==iValue);

    sValue = owfsClient.GetSlash("/");
    Resultat("Test 1 de la methode GetSlash", sValue==sLstDirSlash);
    sValue = owfsClient.GetSlash(TemperatureDevice+"/temperature9");
    Resultat("Test 2 de la methode GetSlash", int(atof(sValue.c_str())*10+0.5)==iValue);

    owfsClient.SetTemperatureScale(owfsClient.Fahrenheit);
    sValue = owfsClient.Get(TemperatureDevice+"/temperature9");
    Resultat("Test de la methode SetTemperatureScale", (atof(sValue.c_str())<fValue*1.81+32)&&(atof(sValue.c_str())>fValue*1.79+32));

    owfsClient.SetDeviceDisplay(owfsClient.FaPtIdPtCo);
    sValue = owfsClient.GetSlash("/");
    owfsClient.SetDeviceDisplay(owfsClient.FaIdCo);
    sLstDir = owfsClient.GetSlash("/");
    sValue.erase(remove(sValue.begin(), sValue.end(), '.'), sValue.end());
    Resultat("Test de la methode SetDeviceDisplay", sValue==sLstDir);

    owfsClient.SetPressureScale(owfsClient.Pa);
    flags = owfsClient.GetOwserverFlags();
    Resultat("Test de la methode SetPressureScale", (flags&0x00140000)==0x00140000);

    flags = owfsClient.GetOwserverFlags();
    Resultat("Test de la methode GetOwserverFlags", flags>0);

    if(PIODevice!="")
    {
        string sValueMemo;
        string sValueSet;

        sValueMemo = owfsClient.Get(PIODevice+"/PIO.B");
        if(sValueMemo=="0")
            sValueSet = "1";
        else
            sValueSet = "0";

        owfsClient.Write(PIODevice+"/PIO.B", sValueSet);
        sValue = owfsClient.Get(PIODevice+"/PIO.B");
        Resultat("Test de la methode Write", sValue==sValueSet);

        owfsClient.Write(PIODevice+"/PIO.B", sValueMemo);
    }

    ok=false;
    try
    {
        owfsClient.Read(TemperatureDevice+"/XXXXXX");
    }
    catch(const owfscpp::Exception& e)
    {
        if(e.GetOwfsError()==-1) ok=true;
    }
    Resultat("Test de owfscpp::Exception", ok);

    if(persistence) owfsClient.SetOwserverFlag(owfsClient.Persistence, false);
}

int main()
{
    owfscpp owfsClient;
    string buffer;

    owfsClient.Initialisation("192.168.0.20", 4304);

    TestsUnitaire(owfsClient, false);
    TestsUnitaire(owfsClient, true);

    cin >> buffer;

    return 0;
}
