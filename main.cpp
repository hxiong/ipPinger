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

int main(int argc, char * argv[])
{
    if(argc !=2){
        cout<<"Provide IP input in CIDR form"<<endl;
        return 1;
    }

    string IP_CIDR = argv[1];  // ip address in CIDR format
    //string IP_CIDR = "70.34.140.0/24";

    Pinger pinger = Pinger(IP_CIDR);  // create pinger object with input IP address
    pinger.ipParse();   // parse input IP

    pinger.setIpBound(pinger.getIpSegs(),pinger.getCidr());  // set the lowest and highest IP to ping

    // creating threads
    thread tlow(&Pinger::pingFromLow, &pinger, pinger.getLowestIp());
    thread thigh(&Pinger::pingFromHigh, &pinger, pinger.getHighestIp());

    tlow.join();
    thigh.join();

 //   cout<<"first in map: "<<pinger.getMap().begin()->second<<endl;
    return 0;
}


