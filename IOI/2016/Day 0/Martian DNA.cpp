// IOI 2016 - Martina DNA
// Leonardo Paes
//
// Same solution as in this comment -> https://codeforces.com/blog/entry/46525?#comment-310021 . But instead of calculating
// the longest substring of 0s I calculated the longest substring of 1s.

#include "dna.h"
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

bool check1(int x){
    string s;
    s.resize(x);
    for(int i=0; i<x; i++) s[i] = '1';
    return make_test(s);
}

bool check2(int x, string aux){
    string s;
    s.resize(x);
    for(int i=0; i<x; i++) s[i] = aux[i];
    return make_test(s);
}

string analyse(int n, int t){
    if(!make_test("1")){
        string a;
        a.resize(n);
        for(int i=0; i<n; i++) a[i] = '0';
        return a;
    }

    int ini = 0, fim = n, meio, longest1 = 0;

    while(ini <= fim){
        meio = (ini + fim) >> 1;

        if(check1(meio)){
            longest1 = meio;
            ini = meio + 1;
        }
        else{
            fim = meio-1;
        }
    }

    string s;
    for(int i=0; i<longest1; i++) s += '1';

    int consec1 = longest1;

    while(consec1<=longest1){
        string aux = s;
        aux += '0';
        if(make_test(aux)){
            s += '0';
            consec1 = 0;
        }
        else{
            s += '1';
            consec1++;
        }
    }

    ini = (int)s.size() - consec1, fim = (int)s.size();

    int idend;

    while(ini <= fim){
        meio = (ini + fim ) >> 1;

        if(check2(meio, s)){
            idend = meio;
            ini = meio + 1;
        }
        else{
            fim = meio - 1;
        }
    }

    deque<char> ans;
    for(int i=0; i<idend; i++) ans.push_back(s[i]);

    while(ans.size() < n){
        ans.push_front('1');
        string aux;
        aux.resize((int)ans.size());
        for(int i=0; i<ans.size(); i++) aux[i] = ans[i];
        if(!make_test(aux)){
            ans.pop_front();
            ans.push_front('0');
        }
    }

    string true_ans;
    true_ans.resize(n);
    for(int i=0; i<ans.size(); i++) true_ans[i] = ans[i];

    return true_ans;
}
