// Singapore NOI 2011 - Change
// Leonardo Paes

// My solution is the same as the official solution: 
// https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/NOI/official/2011.pptx

#include <bits/stdc++.h>

#define int long long

using namespace std;

int cnt[5], ans[5];

main(){

    for(int i=1; i<=4; i++){
        cin >> cnt[i];
    }

    int total;

    cin >> total;

    if(total>=50){
        int k = total/50;
        k = min(k, cnt[4]);
        total -= k*50;
        if(cnt[2]==0 and cnt[1]<2 and total%20==10){
            total+=50;
            k--;
        }
        ans[4]=k;
    }
    if(total>=20){
        int k = total/20;
        k = min(k, cnt[3]);
        total -= k*20;
        ans[3]=k;
    }
    if(total>=10){
        int k = total/10;
        k = min(k, cnt[2]);
        total -= k*10;
        ans[2]=k;
    }
    if(total>=5){
        int k = total/5;
        k = min(k, cnt[1]);
        total -= k*5;
        ans[1]=k;
    }

    if(total==0){
        int sum=0;
        for(int i=1; i<=4; i++){
            cout << ans[i] << " ";
            sum+=ans[i];
        }
        cout << sum << endl;
    }
    else{
        cout << -1 << endl;
    }

    return 0;
}
