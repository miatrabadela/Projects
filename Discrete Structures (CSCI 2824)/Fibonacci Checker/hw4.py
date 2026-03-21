#DO NOT CHANGE THE NAMES OF THE FILE, CLASS or METHOD

import math

class Fibonacci:
    def isFibonacciNumber(self, number):
        if number < 0: 
            return False
        def isPerfectSquare(x):
            s = int (math.isqrt(x))
            return s * s == x
        
        return isPerfectSquare(5* number * number+4) or isPerfectSquare(5* number * number -4)

# For testing your code uncomment below lines.
# f = Fibonacci()
# print(f.isFibonacciNumber(2))
# print(f.isFibonacciNumber(4))
# Comment or delete the above test code before submitting.
