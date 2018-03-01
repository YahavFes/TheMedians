#include <iostream>
#include <math.h>
#include <stdbool.h>

class Point{
public:
    int x;
    int y;
    Point(): x(0),y(0){}
};

int R=0,C=0,F=0,N=0,B=0,T=0;
Point* places;
bool* used;

int closest(Point p);
int distance(Point p1,Point p2);
void Parser();

int main() {
    Parser();
    places=new Point[F];
    used=new bool[F];
    return 0;
}

int closest(Point p){
    int min=0;
    for(int i=1;i<F;i++){
        if(distance(p,places[min])>distance(p,places[i])){
            min=i;
        }
    }
    return min;
}

int distance(Point p1,Point p2){
    return abs(p1.x-p2.x)+abs(p1.y-p2.y);
}

void Parser() {
    std::cin >> R;
    std::cin >> C;
    std::cin >> F;
    std::cin >> N;
    std::cin >> B;
    std::cin >> T;
}