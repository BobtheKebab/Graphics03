#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  int c = points->lastcol;
  if (c == points->cols) {
    grow_matrix(points, c + 10);
  }
  points->m[0][c] = x;
  points->m[1][c] = y;
  points->m[2][c] = z;
  points->m[3][c] = 1;
  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int count = 0;
  while (count < points->lastcol) {
    draw_line(points->m[0][count], points->m[1][count],
	      points->m[0][count + 1], points->m[1][count + 1], s, c);
    count += 2;
  }
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  int x = x0, y = y0, A = y1 - y0, B = x1 - x0, d = 2 * A - B;

  if (x0 > x1) {
    draw_line(x1, y1, x0, y0, s, c);
  }
  
  //Oct 1
  if (A >= 0 && B >= A) {
    while (x <= x1) {
      plot(s, c, x, y);
      if (d > 0) {
	y++;
	d += 2 * B;
      }
      x++;
      d += 2 * A;
    }
  }

  //Oct 2
  if (A >= 0 && A >= B) {
    while (y <= y1) {
      plot(s, c, x, y);
      if (d < 0) {
	x++;
	d += 2 * A;
      }
      y++;
      d += 2 * B;
    }
  }

  //Oct 7
  if (A < 0 && A >= (-1 *B)) {
    while (x <= x1) {
      plot(s, c, x, y);
      if (d > 0) {
	y--;
	d += 2 * B;
      }
      x++;
      d -= 2 * A;
    }
  }

  //Oct 8
  if (A < 0 && (-1 * B) >= A) {
    while (y >= y1) {
      plot(s, c, x, y);
      if (d < 0) {
	x++;
	d -= 2 * A;
      }
      y--;
      d += 2 * B;
    }
  }
  
}

/*
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

  int x, y, d, A, B;
  //swap points if going right -> left
  int xt, yt;
  if (x0 > x1) {
    xt = x0;
    yt = y0;
    x0 = x1;
    y0 = y1;
    x1 = xt;
    y1 = yt;
  }

  x = x0;
  y = y0;
  A = 2 * (y1 - y0);
  B = -2 * (x1 - x0);

  //octant 1
  if ( abs(x1 - x0) >= abs(y1 - y0) ) {

    //octant 1
    if ( A > 0 ) {
      d = A + B/2; //not really division since B = 2B

      while ( x < x1 ) {
        plot( s, c, x, y );
        if ( d > 0 ) {
          y+= 1;
          d+= B;
        }
        x++;
        d+= A;
      } //end octant 1 while
      plot( s, c, x1, y1 );
    } //end octant 1
  }

} //end draw_line
*/
