#ifndef IPPINGER_H
#define IPPINGER_H
#include <cstdlib>
#include <string>
#include <vector>
#include <bitset>
#include <map>

using namespace std;

class Pinger{
private:
    int cidr_modifier=0;
    string ipInputStr;     // user input ip string
    vector<string> ipSegs;  // parsed ip strings
    bitset<32> lowestIp, highestIp; // two IP address bounds
    static int minCount, maxCount; // lowest and highest ip host number
    map<string,string> pingResults;

public:
    // constructor
    Pinger(string s);

    void ipParse();
    void setIpBound(vector<string> ipSegs, int cidrNum);
    bitset<32> bitsetIncr(bitset<32> ipBits);   // increment given bitset by one
    bitset<32> bitsetDecr(bitset<32> ipBits);   // decrement given bitset by one
    void pingFromLow(bitset<32> lowestIp);      // ping from lowest ip
    void pingFromHigh(bitset<32> highestIp);    // ping from highest ip
    void mapAdd(string key, string r);
    string mapGet(string key);
    map<string,string> getMap();

    // getters
    vector<string> getIpSegs();
    int getCidr();
    bitset<32> getLowestIp();
    bitset<32> getHighestIp();
    static int getMinCount();
    static int getMaxCount();

};

#endif // IPPINGER_H
