import math
import fractions
from decimal import *

getcontext().prec = 60

if __name__ == "__main__":
    w, h = 1000, 1000
    p = [[0 for x in range(w)] for y in range(h)]

    p[0][0] = Decimal(1)
    p[0][1] = 0
    for k in range(1, 999):
        p[0][k] = 0
    k = 1
    expectation_value = 0
    for n in range(1, 1000):
        for k in range(1, 1000):
            if k > n:
                p[n][k] = 0
            p[n][k] = ((p[n-1][k-1]) * Decimal(pow(0.5, k-1))) + (p[n-1][k])
            # print(fractions.Fraction(p[n][k]))
    #   expectation:
    for k in range(1, 999):
        expectation_value += Decimal(p[999][k]) * k
    print(Decimal((expectation_value)))

