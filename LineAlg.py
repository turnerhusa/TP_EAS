from bresenham import bresenham

U = 0
D = 1
L = 2
R = 3
# inc_x = 0
# inc_y = 0

def drawLine(curr_x, curr_y, x, y):
  
  instructions = []

  # returns list of new coordinates in order they would be visited
  # a la [(-1, -4), (0, -3), (0, -2), (1, -1), (2, 0), (2, 1), (3, 2)]
  coords = bresenham(curr_x, curr_y, int(x), int(y))
  
  for i in coords[1:]: # start at second index
    
    # horizontal movement
    if coords[i][0] > coords[i-1][0]:
      instructions.append(R)
    elif coords[i][0] < coords[i-1][0]:
      instructions.append(L)
      
    # vertical movement
    if coords[i][1] > coords[i-1][1]:
      instructions.append(U)
    elif coords[i][1] < coords[i-1][1]:
      instructions.append(D)
    
    
  return instructions
 
#   dx = x - curr_x
#   dy = y - curr_y

#   if dx >= 0: # moving right, incrementing x
#     H = R
#     inc_x = 1
#   else: # moving left, decrementing x
#     H = L
#     inc_x = -1

#   if dy >= 0: # movig up, incrementing y
#     V = U
#     inc_y = 1
#   else: # moving down, decrementing y+
#     V = D
#     inc_y = -1


#   dx = abs(dx)
#   dy = abs(dy)
#   p = 2 * dy - dx

#   while x != curr_x or y != curr_y:

#     #print("while loop iteration - ")

#     # print(str(curr_x) + "," + str(curr_y))

#     if x == curr_x:
#       #print("x done, just moving y\n")
#       instructions.append(V)
#       curr_y += inc_y

#     elif y == curr_y:
#       #print("y done, just moving x\n")
#       instructions.append(H)
#       curr_x += inc_x

#     else:
#       if p < 0:
#         #print("door #1\n")
#         instructions.append(H)
#         curr_x += inc_x

#         p = p + 2 * dy

#       else:
#         #print("door #2\n")
#         instructions.append(H)
#         curr_x += inc_x

#         instructions.append(V)
#         curr_y += inc_y

#         p = p + 2 * (dy - dx)

#   return instructions
