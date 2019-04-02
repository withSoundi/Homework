#include <bits/stdc++.h>
using namespace std;
const int maxn = 100;
int main() {
    //S SYN | ACK | FIN (Send)
    //R SYN | RST | ACK | FIN (Receive)
    //or 'S A+B' | 'R A+B'
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    string r[maxn];
    r[0] = "Closed";
    r[1] = "Listen";
    r[2] = "SYN_rcvd";
    r[3] = "SYN_sent";
    r[4] = "Established";
    r[5] = "Fin_wait_1";
    r[6] = "Fin_wait_2";
    r[7] = "Closing";
    r[8] = "Time_wait";
    r[9] = "Close_wait";
    r[10] = "Last_ack";
    string e, msg;
    cout << "Please input 'operate' + 'message' and press enter(or input 'close it')." << endl;
    cout << "Input '0 0' to end it." << endl;
    cout << "Now the TCP's conditon is " << r[0] << endl;
    int cur = 0;
    while(1) {
        cin >> e >> msg;
        cout << e << ' ' << msg << endl;
        if(e == "0") break;
        switch(cur) {
            case 0:
                if(e == "S" && msg == "SYN") cur = 3;
                break;
            case 1:
                if(e == "S" && msg == "SYN") cur = 3;
                if(e == "close") cur = 0;
                break;
            case 2:
                if(e == "R") {
                    if(msg == "ACK") cur = 4;
                    if(msg == "RST") cur = 1;
                }
                if(e == "S" && msg == "FIN") cur = 5;
                break;
            case 3:
                if(e == "S" && msg == "ACK") cur = 4;
                if(e == "R" && msg == "SYN") cur = 2;
                if(e == "close") cur = 0;
                break;
            case 4:
                if(e == "S") {
                    if(msg == "ACK") cur = 9;
                    if(msg == "FIN") cur = 5;
                }
                if(e == "R" && msg == "SYN") cur = 9;
                break;
            case 5:
                if(e == "R") {
                    if(msg == "FIN") cur = 7;
                    if(msg == "F+A") {
                        cout << "Now the TCP's conditon is " << r[8] << endl;
                        cur = 0;
                    }
                    if(msg == "ACK") cur = 6;
                }
                break;
            case 6:
                if(e == "R" && msg == "FIN") {
                    cur = 0;
                    cout << "Now the TCP's conditon is " << r[8] << endl;
                }
                break;
            case 7:
                if(e == "R" && msg == "ACK") {
                    cur = 0;
                    cout << "Now the TCP's conditon is " << r[8] << endl;
                }
                break;
            case 8:
                cur = 0;
                break;
            case 9:
                if(e == "S" && msg == "FIN") cur = 10;
                if(e == "close") cur = 10;
                break;
            case 10:
                if(e == "R" && msg == "SYN") cur = 0;
                break;
        }
        cout << "Now the TCP's conditon is " << r[cur] << endl;
    }
    return 0;
}