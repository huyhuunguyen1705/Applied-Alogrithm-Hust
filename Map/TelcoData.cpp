/*
Description
Write a C program to perform some queries on a telco data (comming from stdin) with the following format:
The first block of data consists of lines (terminated by a line containing #), each line (number of lines can be up to 100000) is under the form: 
        call <from_number> <to_number> <date> <from_time> <end_time> 
which is a call from the phone number <from_number> to a phone number <to_number> on <date>, and starting at time-point <from_time>, terminating at time-point <end_time>
<from_number> and <to_number> are string of 10 characters (a phone number is correct if it contains only digits 0,1,...,9, otherwise, the phone number is incorrect)
<date> is under the form YYYY-MM-DD (for example 2022-10-21)
<from_time> and <to_time> are under the form hh:mm:ss (for example, 10:07:23)
 
The second block consists of queries (terminated by a line containing #), each query in a line (number of lines can be up to 100000) and belongs to one of the following types:
?check_phone_number: print to stdout (in a new line) value 1 if no phone number is incorrect
?number_calls_from <phone_number>: print to stdout (in a new line) the number of times a call is made from <phone_number>
?number_total_calls: print to stdout (in a new line) the total number of calls of the data
?count_time_calls_from <phone_number>: print to stdout (in a new line) the total time duration (in seconds) the calls are made from <phone_number>

Example
Input
call 0912345678 0132465789 2022-07-12 10:30:23 10:32:00
call 0912345678 0945324545 2022-07-13 11:30:10 11:35:11
call 0132465789 0945324545 2022-07-13 11:30:23 11:32:23
call 0945324545 0912345678 2022-07-13 07:30:23 07:48:30
#
?check_phone_number
?number_calls_from 0912345678
?number_total_calls
?count_time_calls_from 0912345678
?count_time_calls_from 0132465789
#

Output
1
2
4
398
120
*/
//C++ 
#include <bits/stdc++.h>

using namespace std;

map<string,int> numCalls, timeCall;

bool checkPhone(string pNumber){
    if(pNumber.length() !=10) return false;
    for(int i=0; i<pNumber.length(); i++){
        if(!(pNumber[i]>='0' && pNumber[i]<='9')) return false;
    }
    return true;
}

int countTime(string sTime, string eTime){
    int startTime = 3600*((sTime[0]-'0')*10 + sTime[1]-'0') + 60*((sTime[3]-'0')*10+sTime[4]-'0') + ((sTime[6]-'0')*10 +sTime[7]-'0');
    int endTime = 3600*((eTime[0]-'0')*10 + eTime[1]-'0') + 60*((eTime[3]-'0')*10+eTime[4]-'0') + ((eTime[6]-'0')*10 +eTime[7]-'0');
    return endTime - startTime;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    
    string cmd;
    int totalCalls = 0;
    int incorrectPhones =0;
    
    while(true){
        cin>>cmd;
        if(cmd == "#") break;
        ++totalCalls;
        string sPhone, ePhone, date, sTime, eTime;
        cin>>sPhone>>ePhone>>date>>sTime>>eTime;
        if(!checkPhone(sPhone) || !checkPhone(ePhone)) ++incorrectPhones;
        numCalls[sPhone]++;
        timeCall[sPhone] +=countTime(sTime, eTime);
    }
    
    while(true){
        cin>>cmd;
        if(cmd == "#") break;
        if(cmd=="?check_phone_number"){
            if(incorrectPhones==0) cout<< 1 <<'\n';
            else cout<< 0 << '\n'; 
        }
        else if(cmd == "?number_calls_from"){
            string pNumber;
            cin>>pNumber;
            cout<<numCalls[pNumber]<<'\n';
        }
        else if(cmd=="?number_total_calls"){
            cout<<totalCalls<<'\n';
        }
        else if(cmd=="?count_time_calls_from"){
            string pNumber;
            cin>>pNumber;
            cout<<timeCall[pNumber] <<'\n';
        }
    }
    return 0;
}
