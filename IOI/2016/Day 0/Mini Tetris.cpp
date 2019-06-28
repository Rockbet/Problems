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

#include <tetris.h>

int mat=0, position, rotation;

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
        position=0, rotation=0;
    }
    if(figure_type==2){
        int pos[6]={0,1,2,0,0,1}, rot[6]={0,0,1,0,1,0}, matt[6]={2,0,3,0,1,2};
        position=pos[mat], rotation=rot[mat], mat=matt[mat];
    }
    if(figure_type==3){
        int pos[6]={0,1,1,0,0,1}, rot[6]={0,1,2,0,3,2}, matt[6]={5,3,4,1,2,0};
        position=pos[mat], rotation=rot[mat], mat=matt[mat];
    }
}
