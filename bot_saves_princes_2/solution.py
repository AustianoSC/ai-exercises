#

def nextMove(n,r,c,grid):
    p_row = p_col = 0
    for row, line in enumerate(grid):
        p_col = line.find('p')
        if p_col != -1:
            p_row = row
            break

    if r > p_row:
        return 'UP'
    elif r < p_row:
        return 'DOWN'
    elif c < p_col:
        return 'RIGHT'
    else:
        return 'LEFT'    

n = int(input())
r,c = [int(i) for i in input().strip().split()]
grid = []
for i in range(0, n):
    grid.append(input())

print(nextMove(n,r,c,grid))