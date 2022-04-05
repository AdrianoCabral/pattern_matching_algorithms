#include <bits/stdc++.h>
#define endl '\n'
using namespace std;


bool flag;

vector<int> fail;
vector<vector<int>> transition;
vector<vector<int>> occ;
map<char,int> table;

void print_matrix(vector<vector<int>> vvi){
    vector< vector<int> >::iterator row;
    vector<int>::iterator col;
    cout <<"[" <<endl;
    for (row = vvi.begin(); row != vvi.end(); row++) {
        cout <<" [";
        for (col = row->begin(); col != row->end(); col++) {
            cout << *(col);
            if(col < row->end()-1){cout <<", ";}
        }
        if(row < vvi.end()-1){cout << "]," << endl;}
        else{cout << "]" << endl;}
        
    }
    cout << "]" << endl;
    cout << endl;
}

void make_hash(string alphabet){
    int l = alphabet.length();
    for(int i = 0; i < l;i++){
        table[alphabet[i]] = i;
    }
}

void build_transitions(vector<string> pat_set, string alphabet){
    int l = alphabet.length();
    transition.push_back(vector<int>(l,-1));
    occ.push_back(vector<int>(0));
    make_hash(alphabet);
    int cur = 0;
    int nxt = 1;

    for(int k = 0; k < pat_set.size();k++){
        cur = 0;
        string pat = pat_set[k];
        int m = pat.length();
        int j = 0;
        int c = table[pat[j]];
        vector< vector<int> >::iterator row;
        vector<int>::iterator col;
        row = transition.begin() + cur;
        col = row->begin() + c;
        while (j < m and row < transition.end() and col < row->end() and *(col) != -1){
            cur = transition[cur][c];
            j++;
            c = table[pat[j]];
            row = transition.begin() + cur;
            col = row->begin() + c;
        }

        while(j < m){
            c = table[pat[j]];
            transition[cur][c] = nxt;
            transition.push_back(vector<int>(l,-1)); 
            occ.push_back(vector<int>(0));
            cur = nxt;
            j++;
            nxt++;
        }
        occ[cur].push_back(k);
    }
    for(int c = 0; c < l; c++){
        if(transition[0][c] == -1){
            transition[0][c] = 0;
        }
    }
}

void build_fail(vector<string> pat_set, string alphabet){
    
    int n = transition.size();
    int l = alphabet.length();
    vector<int> fail_aux(n,-1);
    fail.insert(fail.begin(), fail_aux.begin(),fail_aux.end());
    queue<int> bfs;
    fail[0] = 0;

    for(int c = 0; c < alphabet.length();c++){
        if(transition[0][c] > 0){
            bfs.push(transition[0][c]);
            fail[transition[0][c]] = 0;
        }
    }
    while(!bfs.empty()){
        int cur = bfs.front();
        bfs.pop();
        for(int c = 0; c < alphabet.length();c++){
            int suc = transition[cur][c];
            if(suc >= 0){
                bfs.push(suc);
                int brd = fail[cur];
                assert(brd >= 0);
                while(transition[brd][c] < 0){
                    brd = fail[brd]; 
                }
                fail[suc] = transition[brd][c];
                occ[suc].insert(occ[suc].end(), occ[fail[suc]].begin(),occ[fail[suc]].end());
            }
        }
    }
}

void build_fsm(vector<string> pat_set, string alphabet){  
    build_transitions(pat_set, alphabet);
    build_fail(pat_set, alphabet);
    flag = true;
}

vector<vector<int>> aho_corasick(string txt, vector<string> pat_set, string alphabet){
    
    if(!flag){
        build_fsm(pat_set, alphabet);
    }
    for(int i: fail){
        cout << i << " ";
    }
    cout << endl;
    
    vector<vector<int>> match_set(pat_set.size(),vector<int>(0));
    int n = txt.length();
    int cur = 0;
    int i = 0;
    int c = 0;
    while(i < n){
        c = table[txt[i]];
        while(transition[cur][c] < 0){
            cur = fail[cur];
        }
        cur = transition[cur][c];
        for(int k: occ[cur]){
            match_set[k].push_back((i - pat_set[k].length()) + 1);
        }
        i++;
    }
    return match_set;
}

int main(){
    vector<char >alphabet{'a','b','c','d','e','f','g','h','i','j', 'k','l','m','n','o', 'p','q','r','s','t','u','v','w','x','y','z'};
    string alphabet2 = "ehirsu";
    vector<string> pat_set{"he","she","his","hers"};
    vector<vector<int>> match_set = aho_corasick("ushers", pat_set, alphabet2);
    cout << "fofo" << endl;
    print_matrix(match_set);
    cout << match_set.size() << endl;
    // transitions.push_back(vector<int>(l,-1));

    // for(char c: pat){
    //     cout << table[c] << endl;
    // }
}