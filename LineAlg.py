# // void drawLineFromCurrCoords(int x, int y) {

# //   // get distance of new coords from current 
# //   int dx = x - curr_coords[X];
# //   int dy = y - curr_coords[Y];

# //   // figure out which direction we are moving in from current position
# //   void (*UDdirec)();
# //   void (*LRdirec)();

# //   if (dx >= 0)  { LRdirec = &R; } 
# //   else     		{ LRdirec = &L; }

# //   if (dy >= 0)  { UDdirec = &U; }
# //   else     		{ UDdirec = &D; }

# //   while (!(curr_coords[X] == x && curr_coords[Y] == y)) {

# //     dx = abs(x - curr_coords[X]);
# //     dy = abs(y - curr_coords[Y]);
# //     int p = 2 * dy - dx;

# //     if      (dx == 0) { UDdirec(); } // if nowhere else to go sideways
# //     else if (dy == 0) { LRdirec(); } // if nowhere else to go vertically
# //     else { // Bresenham Line-Drawing Algorithm

# //       if (p < 0) {
# //         LRdirec();
# //         p = p + 2 * dy;
# //       } else {
# //         LRdirec();
# //         UDdirec();
# //         p = p + 2 * (dy - dx);
# //       }
# //     }
# //   }
# // }

U = 0
D = 1
L = 2
R = 3

instructions = []
inc_x = 0
inc_y = 0


def drawLine(curr_x, curr_y, x, y):
  dx = x - curr_x
  dy = y - curr_y

  if dx >= 0:
    H = R
    inc_x = 1
  else:
    H = L
    inc_x = -1

  if dy >= 0:
    V = U
    inc_y = 1
  else:
    V = D
    inc_y = -1


  dx = abs(dx)
  dy = abs(dy)
  p = 2 * dy - dx

  while x != curr_x or y != curr_y:

    if p < 0:
      instructions.append(H)
      x += inc_x
      p = p + 2 * dy
    else:
      instructions.append(H)
      x += inc_x
      instructions.append(V)
      x += inc_y
      p = p + 2 * (dy - dx)
