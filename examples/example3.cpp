/***********************************************************************************************/
/**                                                                                           **/
/** EXAMPLE 3                                                                                 **/
/**                                                                                           **/
/** Set owserver flags : persistence connexion & temperature in Fahrenheit                    **/
/**                                                                                           **/
/***********************************************************************************************/

#include <iostream>
#include "owfscpp.h"

using namespace std;

int main()
{
    owfscpp owfsClient;
    string buffer;

    owfsClient.Initialisation("192.168.0.20", 4304);

    owfsClient.SetOwserverFlag(owfscpp::Persistence, true);

    owfsClient.SetTemperatureScale(owfscpp::Centigrade);
    buffer = owfsClient.Read("/10.0429A9010800/temperature9");
    cout << "The temperature of the device 10.0429A9010800 is " << buffer << " in centigrade." << endl;

    owfsClient.SetTemperatureScale(owfscpp::Fahrenheit);
    buffer = owfsClient.Read("/10.0429A9010800/temperature9");
    cout << "The temperature of the device 10.0429A9010800 is " << buffer << " in fahrenheit." << endl;

    cin >> buffer;
    return 0;
}
