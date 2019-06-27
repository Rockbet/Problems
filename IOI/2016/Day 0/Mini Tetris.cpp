// To solve this problem, I reduced the problem to: Having a 3x3 playing field, dont lose with pieces of type 2 and 3.
// This is possible if you choose position = 0 and rotation = 0 to all pieces of type 1, and to do it, you have to have
// at least one empty row. So, you always have to let at least 1 empty row.
// To solve all the others cases, I used 6 types of fields, and only them. I proved that, being in one of the six fields,
// we can reach one of them again by using any new piece into it.
// Here are the types of fields ( a dot is an empty space and a '#' is an used space: 
//    Type 1    Type 2    Type 3    Type 4    Type 5    Type 6
//   
//    . . .     . . .     . . .     . . .     . . .     . . .
//    . . .     . . .     . . .     . . .     . . .     . . .
//    . . .     . . .     . . .     . . .     . . .     # . .
//    . . .     # . .     # # .     . . #     . # #     # # .
//
// To understand the way we added the new piece into each one of the possible matrix, just go to the if's inside the
// void new_figure(int figure_type){}. :D

#include <bits/stdc++.h>
 
using namespace std;
 
int mat=1, position, rotation;
 
int get_position(){
    return position;
}
 
int get_rotation(){
    return rotation;
}
 
void init(int n){
}
 
void new_figure(int figure_type){
    if(figure_type==1){
        position=0;
        rotation=0;
        return;
    }
    if(figure_type==2){
        if(mat==1){
            mat=3;
            position=0;
            rotation=0;
            return;
        }
        if(mat==2){
            mat=1;
            position=1;
            rotation=0;
            return;
        }
        if(mat==3){
            mat=4;
            position=2;
            rotation=1;
            return;
        }
        if(mat==4){
            mat=1;
            position=0;
            rotation=0;
            return;
        }
        if(mat==5){
            mat=2;
            position=0;
            rotation=1;
            return;
        }
        if(mat==6){
            mat=3;
            position=1;
            rotation=0;
            return;
        }
    }
    if(figure_type==3){
        if(mat==1){
            mat=6;
            position=0;
            rotation=0;
            return;
        }
        if(mat==2){
            mat=4;
            position=1;
            rotation=1;
            return;
        }
        if(mat==3){
            mat=5;
            position=1;
            rotation=2;
            return;
        }
        if(mat==4){
            mat=2;
            position=0;
            rotation=0;
            return;
        }
        if(mat==5){
            mat=3;
            position=0;
            rotation=3;
            return;
        }
        if(mat==6){
            mat=1;
            position=1;
            rotation=2;
            return;
        }
    }
}
