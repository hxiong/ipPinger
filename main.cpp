#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
// #include <algorithm>
#include <string>
#include <cstdlib>
#include <bitset>

using namespace std;

// function declaration
vector<string> ipParse(string);


int main()
{
//    string usrInput;
//
//    cout << "enter the IP to ping: " << endl;
//    cin >> usrInput;
//    cout << usrInput;

    // string pingIp = (string)"ping" + "www.google.com";
    //int flag = system("ping www.google.com");
    string IP_CIDR = "192.168.0.0/23";

//    int flag = system("ping 80.34.0.0");
//    cout << "flag value is: "<<flag << endl;

    vector<string> ipSegs = ipParse(IP_CIDR);
    cout<<ipSegs.back()<<endl;

    string st="192";
    int i = atoi(st.c_str());
    cout <<"integer is: "<< i<<endl;

    // int to bit string
    string bitStr = bitset<32>(i).to_string();
    cout<<"bit string is: "<<bitStr<<endl;

    // bit string to decimal
    unsigned long decimal = bitset<32>(bitStr).to_ulong();
    cout<<"decimal is: "<<decimal<<endl;

    // int to bit set
    cout<<"bit set : "<<bitset<8>(192)<<endl;

    cout<<"bit set from string: "<<bitset<8>(atoi(st.c_str()))<<endl;



    return 0;
}

vector<string> ipParse(string rawIp){
    vector<string> ipSegs;
    cout <<"parsing IP in CIDR form: "<< rawIp <<endl;

    string delim = ".";
    size_t start = 0;
    size_t end = rawIp.find(delim);

    while(end != string::npos){
       // cout<<rawIp.substr(start,end - start)<<endl;
        ipSegs.push_back(rawIp.substr(start,end - start));
        start = end + delim.length();
        end = rawIp.find(delim,start);
    }
    ipSegs.push_back(rawIp.substr(start,string::npos));

    return ipSegs;

  //  cout<<ipSegs.at(ipSegs.size()-1)<<endl;
}
