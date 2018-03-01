#include <iostream>
#include <math.h>
#include <stdbool.h>
#include <cstdlib>




class Point{
public:
    int x;
    int y;
    Point(): x(0),y(0){}
    Point(int a,int b):x(a),y(b){}
    bool operator==(Point& p){
        return x==p.x&&y==p.y;
    }
    bool operator!=(Point& p){
        return !(*this==p);
    }
};

class Ride {
public:
    int startT;
    int endT;
    Point startP;
    Point endP;
};

int R=0,C=0,F=0,N=0,B=0,T=0;
Point* places;
bool* used;
Ride* rides;
Point* moveTo;
Ride* chosen;

void mergeSort(Ride* init, int l, int r);
int compare(Ride r1,Ride r2,Point p);
int closest(Point p);
int distance(Point p1,Point p2);
void Parser();
void moveX(int i);
void moveY(int i);
void initial();

int main() {
    Parser();
    places=new Point[F];
    used=new bool[F];
    mergeSort(rides,0,N);
    moveTo=new Point[F];
    chosen=new Ride[N];
    initial();
    for(int i=0;i<T;i++){
        for(int j=0;j<F;j++){
            if(used[j]==true){
                if(moveTo[j]!=places[j]){
                    if(moveTo[j].x==places[j].x){
                        moveY(j);
                    }
                    else{
                        moveX(j);
                    }
                }
                if(places[j]==moveTo[j]){
                    if(chosen[j].endP==places[j]){
                        used[j]=false;
                    }
                    else{
                        if(i+1>=chosen[j].startT){
                            moveTo[j]=chosen[j].endP;
                        }
                    }
                }
            }
            else{

            }
        }
    }
    return 0;
}

void moveY(int i){
    if(places[i].y<moveTo[i].y){
        places[i].y++;
    }
    else{
        places[i].y--;
    }
}

void moveX(int i){
    if(places[i].x<moveTo[i].x){
        places[i].x++;
    }
    else{
        places[i].x--;
    }
}

int closest(Point p){
    int min=-1;
    for(int i=0;i<F;i++){
        if(!used[i]) {
            if (min==-1||distance(p, places[min]) > distance(p, places[i])) {
                min = i;
            }
        }
    }
    return min;
}

int distance(Point p1,Point p2){
    return abs(p1.x-p2.x)+abs(p1.y-p2.y);
}


void merge(Ride* init, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    Ride L[n1], R[n2];
    Point point(0,0);

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = init[l + i];
    for (j = 0; j < n2; j++)
        R[j] = init[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (compare(L[i] , R[j] , point) == 0)
        {
            init[k] = L[i];
            i++;
        }
        else
        {
            init[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        init[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        init[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(Ride* init, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(init, l, m);
        mergeSort(init, m+1, r);

        merge(init, l, m, r);
    }
}

bool outOfRange(Ride r){
    return distance(r.startP,r.endP)>r.endT-r.startT;
}

int compare(Ride r1,Ride r2,Point p){
    if(distance(r1.startP,p) + r1.startT < distance(r2.startP,p) + r2.startT) {
        return 1;
    }
    else {
        return 0;
    }
}

void Parser() {
    std::cin >> R;
    std::cin >> C;
    std::cin >> F;
    std::cin >> N;
    std::cin >> B;
    std::cin >> T;
    rides=new Ride[N];
    int x,y;
    int place=0;
    for(int i=0;i<N;i++,place++){
        std::cin >> rides[place].startP.x;
        std::cin >> rides[place].startP.y;
        std::cin >> rides[place].endP.x;
        std::cin >> rides[place].endP.y;
        std::cin >> rides[place].startT;
        std::cin >> rides[place].endT;
        if(outOfRange(rides[place])){
            place--;
        }
    }
    N=place;
}

void initial() {
    Point point(0,0);
    int j=0;
    for(int i=0;i<F;i++) {
        if(distance(point,rides[i].startP) <= rides[i].startT) {
            used[j]=1;
            chosen[j]=rides[i];
            j++;
        }
        else {
            i--;
        }
    }
}