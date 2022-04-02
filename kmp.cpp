#include <bits/stdc++.h>
#define endl '\n'
using namespace std;


vector<int> bruteforce(string txt, string pat){
    vector<int> occ;
    int n = txt.length();
    int m = pat.length();
    int i = 0, j = 0;
    while(i <= n-m){
        while( j < m and txt[i+j] == pat[j]){
            j++;
        }
        if(j == m){
            occ.push_back(i);
        }
        i++;
        j = 0;
    }
    return occ;
}
int main(){
    // vector<int> occ = bruteforce("abracadabrabrabrabrabrabrabrabrabrabra","abra");
    // for(int x: occ){
    //     cout << x << endl;
    // }
    string p = "porta";

}