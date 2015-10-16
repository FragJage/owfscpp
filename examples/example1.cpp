/***********************************************************************************************/
/**                                                                                           **/
/** EXAMPLE 1                                                                                 **/
/**                                                                                           **/
/** Get the list of OWFS devices                                                              **/
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
    string buffer;

    owfsClient.Initialisation("192.168.0.20", 4304);

    lstDir = owfsClient.DirAll("/");
    for(iDir = lstDir.begin(); iDir != lstDir.end(); ++iDir)
    {
        cout << *iDir << endl;
    }

    cin >> buffer;
    return 0;
}
