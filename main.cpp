#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <bitset>
#include <thread>
#include <map>
#include "ipPinger.h"

using namespace std;

int main()
{
    string usrInput;

    cout << "enter the IP in CIDR form: " << endl;
    cin >> usrInput;
   // cout << usrInput;

   // string IP_CIDR = "192.168.0.0/23";
    string IP_CIDR = "70.34.140.0/24";

    Pinger pinger = Pinger(IP_CIDR);
    pinger.ipParse();

    pinger.setIpBound(pinger.getIpSegs(),pinger.getCidr());

    cout<<"minCount is: "<<pinger.getMinCount()<<endl;
    cout<<"maxCount is: "<<pinger.getMaxCount()<<endl;

    // creating threads
    thread tlow(&Pinger::pingFromLow, &pinger, pinger.getLowestIp());
    thread thigh(&Pinger::pingFromHigh, &pinger, pinger.getHighestIp());

    tlow.join();
    thigh.join();

    cout<<"minCount after: "<<pinger.getMinCount()<<endl;
    cout<<"maxCount after: "<<pinger.getMaxCount()<<endl;
    cout<<"first in map: "<<pinger.getMap().begin()->second<<endl;

    return 0;
}


