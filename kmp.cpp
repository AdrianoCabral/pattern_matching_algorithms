#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
vector<int> nxt;

vector<int> init_nxt_bf(string pat){
    nxt.resize(pat.length()+1);
    fill(nxt.begin(),nxt.end(),-1);
    for(int j = 1; j < pat.length()+1;j++){
        for(int k = 0; k < j;k++){
            if(pat.substr(0,k) == pat.substr(j-k,k)){
                nxt[j] = k;
            }
        }
    }
    return nxt;
}

vector<int> init_nxt(string pat){
    nxt.resize(pat.length()+1);
    fill(nxt.begin(),nxt.end(),0);
    nxt[0] = -1;
    int m = pat.length();
    int i = 1, j = 0;
    while (i + j < m){
        while (i + j < m && pat[i+j] == pat[j]){
            j++;
            nxt[i+j] = j;
        }
        i += (j- nxt[j]);
        j = max(0, nxt[j]);
    }

    return nxt;

}

vector<int> init_strict_nxt(string pat){
    nxt.resize(pat.length()+1);
    fill(nxt.begin(),nxt.end(),-1);
    if (m == 1 or (m > 1 && pat[0] != pat[1]){
        nxt[1] = 0
    }
    int m = pat.length();
    int i = 1, j = 0;
    while (i + j < m){
        while (i + j < m && pat[i+j] == pat[j]){
            j++;
            if (i + j == m or pat[i+j] != pat[j]){
                nxt[i+j] = j;
            }
            else{
                nzt[i+j] = nxt[j]
            }
        }
        i += (j- nxt[j]);
        j = max(0, nxt[j]);
    }

    return nxt;

}

vector<int> kmp(string txt, string pat){
    vector<int> occ;
    int n = txt.length();
    int m = pat.length();
    int i = 0, j = 0;
    if(nxt.size() == 0){
        nxt = init_nxt(pat);
    }
    
    while(i <= n-m){
        while( j < m and txt[i+j] == pat[j]){
            j++;
        }
        if(j == m){
            occ.push_back(i);
        }
        i = i + (j-nxt[j]);
        j = max(0,nxt[j]);
    }
    return occ;
}


int main(){
    vector<int> occ = kmp("abracadabrafdsafdsabracadabrabrabraxjklasabracadabra","abra");
    for(int x: occ){
       cout << x << endl;
    }
    for(int x: nxt){
        cout << x << " ";
    }
}