#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#define PI 3.141592653

double calcX(int radius, double item, double numSides,double off){
  double in = item/numSides * 2.0f*PI;
  return radius * cos(in+off);
}
double calcY(int radius, double item, double numSides,double off){
  double in = item/numSides * 2.0f*PI;
  return radius * sin(in +off);
}
void drawNgon(int x0, int y0,int radius, int numSides,int offset,screen s, color c){
  double off = offset * PI/180;
  int x = x0+ calcX(radius, -2, numSides,off);
  int y = y0+ calcY(radius, -2, numSides,off);
  int tx = x0+ calcX(radius, -1, numSides,off);
  int ty = y0+ calcY(radius, -1, numSides,off);
  int t2x = x0+ calcX(radius, 0, numSides,off);
  int t2y = y0+ calcY(radius, 0, numSides,off);
  int item = 0;
  while(item < numSides){
    x = x0+ calcX(radius, -2+item, numSides,off);
    y = y0+ calcY(radius, -2+item, numSides,off);
    tx = x0+ calcX(radius, -1+item, numSides,off);
    ty = y0+ calcY(radius, -1+item, numSides,off);
    t2x = x0+ calcX(radius, item, numSides,off);
    t2y = y0+ calcY(radius, item, numSides,off);
      drawBezier(x,y,tx,ty,t2x,t2y,10,s,c);
      item++;
  }
}
void drawBezier(int x0,int y0,int x1,int y1,int x2,int y2, int resolution,screen s, color c){
  int c0 = x0;
  int d0 = y0;
  int c1 = x1;
  int d1 = y1;
  int iter = 0;
  int j0 = x0;
  int k0 = y0;
  int tj0 = j0;
  int tk0 = k0;
  while(iter <= resolution){
    c0 = lerp(x0,x1,iter,resolution);
    d0 = lerp(y0,y1,iter,resolution);

    c1 = lerp(x1,x2,iter,resolution);
    d1 = lerp(y1,y2,iter,resolution);

    j0 = lerp(c0,c1,iter,resolution);
    k0 = lerp(d0,d1,iter,resolution);
    draw_line(c0,d0,c1,d1,s,c);
    if(iter > 0){
      draw_line(tj0,tk0,j0,k0,s,c);
    }
    tj0 = j0;
    tk0 = k0;
    iter++;
  }

}
int lerp(int t0, int t1, int pcent,int resolution){
  return (t0*pcent + (resolution - pcent)*t1)/resolution;
}















//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  if(x1 < x0){
    draw_line(x1,y1,x0,y0,s,c);
    return;
  }
  int fy = 1;
  if(y1 < y0){
    fy = -1;
  }
  int x = x0;
  int y = fy*y0;
  int ex = x1;
  int ey = fy*y1;
  int A = ey-y;
  int B = x-ex;
  int flip = (A+B) > 0;
  if(flip){
    int tmp = ex;
    ex = ey;
    ey = tmp;
    tmp = x;
    x = y;
    y = tmp;
    A = ey-y;
    B = x-ex;
  }
  int d = 2*A + B;
  A <<= 1;
  B <<= 1;
  while (x <= ex){
    if(flip){
      plot(s,c,y,x*fy);
    }else{
      plot(s,c,x,y*fy);
    }
    if(d > 0){
      ++y;
      d+=B;
    }
    ++x;
    d+=A;
  }
}
