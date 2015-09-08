#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <map>
#include "ipPinger.h"

using namespace std;

// Constructor
Pinger:: Pinger(string s){
    this->ipInputStr = s;
}

// getter definitions
vector<string> Pinger::getIpSegs(){ return this->ipSegs;}
int Pinger::getCidr(){ return this->cidr_modifier;}
bitset<32> Pinger::getLowestIp(){ return this->lowestIp;}
bitset<32> Pinger::getHighestIp() { return this->highestIp;}
map<string,string> Pinger::getMap() { return pingResults;}
int Pinger::getMinCount(){ return minCount;}
int Pinger::getMaxCount(){ return maxCount;}

// initializing static variables
int Pinger:: minCount = 0;
int Pinger:: maxCount = 255;


// parsing the user input
void Pinger::ipParse(){

    string delim = ".";
    size_t start = 0;
    size_t end = ipInputStr.find(delim);

    while(end != string::npos){
        ipSegs.push_back(ipInputStr.substr(start,end - start));
        start = end + delim.length();
        end = ipInputStr.find(delim,start);
    }
    string temp1 = ipInputStr.substr(start,string::npos);

    size_t found = temp1.find('/');

    ipSegs.push_back(temp1.substr(0,found));
    cidr_modifier=atoi(temp1.substr(found+1).c_str());
}

// set lowest and highest ip to ping from
void Pinger::setIpBound(vector<string> ipSegs, int cidrNum){
    string bitStr;
    int numBitsReset = 32-cidrNum;

    for(unsigned int i=0; i<ipSegs.size(); i++){
        bitStr += bitset<8>(atoi(ipSegs[i].c_str())).to_string();
    }
    this->lowestIp = bitset<32>(bitStr);
    this->highestIp = bitset<32>(bitStr);

// set lowest and highest bounds
    for(int i=0; i<numBitsReset; i++){
        this->lowestIp[i] = 0;
        this->highestIp[i] = 1;
    }

// set min and max counters for pinging
     minCount=0;
     string perm = highestIp.to_string().substr(cidrNum);
     char * endptr;
     maxCount = strtol(perm.c_str(),&endptr,2);
}


// increment and decrement bitset functions
bitset<32> Pinger::bitsetIncr(bitset<32> ipBits){
    for(int i=0; i<32; i++){
        if(ipBits[i] ==0){
            ipBits[i] = 1;
            break;
        }
        ipBits[i] = 0;
    }
    return ipBits;
}

bitset<32> Pinger::bitsetDecr(bitset<32> ipBits){
    for(int i=0; i<32; i++){
        if(ipBits[i] ==1){
            ipBits[i] =0;
            break;
        }
        ipBits[i] = 1;
    }
    return ipBits;
}

void Pinger::pingFromLow(bitset<32> lowestIp){
    string pingStr;
    string segStr;
    bitset<8> tbits;
    int flag=0;
  //  cout<<"lowestIp is: "<<endl<<lowestIp<<endl;

    while(minCount < maxCount){
        minCount++;
        pingStr = (string)"ping ";
        lowestIp = bitsetIncr(lowestIp);

        for(int i=0; i<32; i=i+8){
            segStr = lowestIp.to_string().substr(i,8);
            tbits = bitset<8>(segStr);
            unsigned long decimal = tbits.to_ulong();
            // long to string
            stringstream ss;
            ss<<decimal;
            // constructing ping string
            pingStr=pingStr+ss.str()+(string)".";
        }
        pingStr.pop_back();

        flag=system((pingStr+(string)" > nul").c_str());
        if(flag==0){
            cout<<pingStr.substr(5)<<endl;
            mapAdd(pingStr.substr(5),(string)"hit");
        }
        else if(flag==1){
            mapAdd(pingStr.substr(5),(string)"miss");
        }
    }
}

void Pinger::pingFromHigh(bitset<32> higestIp){
    string pingStr;
    string segStr;
    bitset<8> tbits;
    int flag=0;
   // cout<<"highestIp is: "<<endl<<highestIp<<endl;

    while(maxCount > minCount){
        maxCount--;
        pingStr = (string)"ping ";
        highestIp = bitsetDecr(highestIp);

        for(int i=0; i<32; i=i+8){
            segStr = highestIp.to_string().substr(i,8);
            tbits = bitset<8>(segStr);
            unsigned long decimal = tbits.to_ulong();
            // long to string
            stringstream ss;
            ss<<decimal;
            // constructing ping string
            pingStr=pingStr+ss.str()+(string)".";
        }
        pingStr.pop_back();

        flag=system((pingStr+(string)" > nul").c_str());
        if(flag == 0){
            cout<<pingStr.substr(5)<<endl;
            mapAdd(pingStr.substr(5),(string)"hit");
        }
        else if(flag ==1){
            mapAdd(pingStr.substr(5),(string)"miss");
        }
    }
}

void Pinger::mapAdd(string key, string r){
    this->pingResults[key] = r;
}

string Pinger::mapGet(string key){
    return this->pingResults[key];
}
