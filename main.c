#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "display.c"
#include "draw.h"
#include "draw.c"
#include "matrix.h"
#include "matrix.c"

int main() {

  screen s;
  color c;
  struct matrix *edges = new_matrix(4, 4);

  c.red = 255;
  int xoff = 1, y = 5;
  while (y < 495) {
    add_edge(edges, 250 + xoff, y, 0, 250 - xoff, y, 0);
    add_edge(edges, 250 + xoff, y, 0, 250 + xoff, 0, 0);
    add_edge(edges, 250 - xoff, y, 0, 250 - xoff, 0, 0);
    xoff+= 5;
    y += 10;
  }
  
  draw_lines(edges, s, c);
  display(s);
  free_matrix( edges );
  
}
