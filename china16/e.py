def func(x):
    return 1.0 * x[0] / x[1]

T = int(input())
for tc in range(1, T + 1):
    n = int(input())
    a = []
    for i in range(n):
        x, y = input().split(':')
        x = int(float(x) * 1000)
        y = int(float(y) * 1000)
        a += [(x, x + y)]
    a.sort(key=func)
    numer = 0
    denom = 1
    res = 0
    for i in range(n):
        numer = numer * a[i][1] + denom * a[i][0]
        denom = denom * a[i][1]
        if (numer < denom):
            res = i + 1
        else:
            break
    print("Case #" + str(tc) + ": " + str(res))


