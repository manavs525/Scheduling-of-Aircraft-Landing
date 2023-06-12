#include <bits/stdc++.h>
using namespace std;

void __print(int x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(bool x) {cerr << (x ? "true" : "false");}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T, typename V>
void __print(const array<T, 2> &x) {cerr << '{'; __print(x[0]); cerr << ','; __print(x[1]); cerr << '}';}
template<typename T, typename V>
void __print(const array<T, 3> &x) {cerr << '{'; __print(x[0]); cerr << ','; __print(x[1]); cerr << ','; __print(x[2]); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void print(T t, V... v) {_print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define w(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define w(x...)
#endif

#define DB long double

int main()
    freopen("airland1.txt","r",stdin);

    int Flights, Frozen_time;
    cin >> Flights >> Frozen_time;

    vector<vector<DB>> F(Flights, vector<DB> (Flights + 7));
    for(int i=0; i<Flights; i++){
        for(int j=0; j<Flights + 6; j+=1){
            cin >> F[i][j];
        }
        F[i][Flights + 6] = (i+1);
    }

    sort(F.begin(), F.end());  \\sorting flights in ascending order of appearance time

    for(int i=0; i<Flights; i++){
        w(i, F[i]);
    }

    // Apperance time, Earliest landing time, Target landing time, Latest landing time, cost before landing, cost after landing, 
    // Separation matrix with Flights number of values; // from 6
    // Actual landing time for all

    vector<DB> Actual_Time(Flights, 0.0);
    DB Cost = 0.0;

    cout << endl;
    for(int i=0; i<Flights; i++){
        if(i==0){
            Actual_Time[i] = F[i][2]; // actual landing time
            //w(F[i][Flights + 6], F[i][i+5], Actual_Time[i], Cost);
        }
        else{
            Actual_Time[i] = Actual_Time[i-1] + F[i][i+5];	

            if(Actual_Time[i] < F[i][2]){		\\Calculation for 5th step i.e., opportunity for optimisation
                if(F[i][i+5] > F[i-1][i+4]){
                    if((Actual_Time[i-1] - (F[i-2][2] + F[i-1][i+5])) > F[i][i+5]){
                        //Actual_Time[i-1] = Actual_Time[i-1] - F[i][i+5];
                        Actual_Time[i-1] = Actual_Time[i-1] - F[i][i+5];
                        Actual_Time[ i ] = F[i][2];
                    }
                    else if (Actual_Time[i-1] - (F[i-2][2] + F[i-1][i+5]) > 0){
                        Actual_Time[i-1] -= (F[i-2][2] + F[i-1][i+5]);
                        Actual_Time[ i ]  -= (Actual_Time[i-1] - (F[i-2][2] + F[i-1][i+5]));
                    }
                }
            }

            Cost += (Actual_Time[i] - F[i][2])*F[i][5];
            int Target_time = F[i][2];

            //w(F[i][Flights + 6], F[i-1][2], F[i][i+5], Actual_Time[i], Target_time, Cost);
        }

    }
    cout << endl;
    cout << "Total Cost = " << Cost << endl;
    cout<<Cost <<endl;

    for(int i=0; i<Flights; i++){
        cout<<F[i][Flights + 6]<<","<< Actual_Time[i]);
    }



}