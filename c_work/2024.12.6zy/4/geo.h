#ifndef _GEO_H
#define _GEO_H
#define XMAX 100
struct point{
    double x;
    double y;
};
struct rect{
    struct point p1;
    struct point p2;
};
struct point makepoint(double x,double y);
struct point middlepoint(struct rect screen);
struct point addpoint(struct point p1,struct point p2);
int ptinrect(struct point p,struct rect r);
struct rect canonrect(struct rect r);
#endif