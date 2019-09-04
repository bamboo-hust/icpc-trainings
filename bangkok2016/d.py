import math

def bezout(a, b):
    xa = 1
    xb = 0
    while b > 0:
        q = a / b
        r = a - q * b
        xr = xa - q * xb
        a = b
        xa = xb
        b = r
        xb = xr
    return xa

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

def solve(a, b, c):
    d = gcd(a, b)
    x = bezout(a, b);
    y = (d - a * x) / b
    c /= d
    return x * c, y * c

inp = input()
inp = inp.split('\n')
T = int(inp[0])

for i in range(1, T + 1):
    line = input().split(' ') #inp[i].split(' ')

    ax = int(line[0])
    ay = int(line[1])
    bx = int(line[2])
    by = int(line[3])
    k = int(line[4])

    x0 = bx - ax
    y0 = by - ay
    x, y = solve(y0, -x0, gcd(abs(x0), abs(y0)) + ax * y0 - ay * x0)
    
    for j in range(k):
        print(str(int(x)) + ' ' + str(int(y)))
        x -= x0
        y -= y0