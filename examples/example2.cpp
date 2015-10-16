/***********************************************************************************************/
/**                                                                                           **/
/** EXAMPLE 2                                                                                 **/
/**                                                                                           **/
/** Get the value of the first OWFS devices temperature                                       **/
/**                                                                                           **/
/***********************************************************************************************/

#include <iostream>
#include "owfscpp.h"

using namespace std;

int main()
{
    owfscpp owfsClient;
    list<string> lstDir;
    list<string>::iterator iDir;
    string TemperatureDevice;
    string buffer;

    owfsClient.Initialisation("192.168.0.20", 4304);

    //Find the first OWFS devices temperature
    lstDir = owfsClient.DirAll("/");
    for(iDir = lstDir.begin(); iDir != lstDir.end(); ++iDir)
    {
        buffer = (*iDir).substr(1,2);
        if((buffer=="10")||(buffer=="22")||(buffer=="28"))
        {
            TemperatureDevice = *iDir;
            break;
        }
    }

    //Read temperature
    buffer = owfsClient.Read(TemperatureDevice+"/temperature9");
    cout << "The temperature of the device " << TemperatureDevice << " is " << buffer << "." << endl;

    cin >> buffer;
    return 0;
}
