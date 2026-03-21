
# DO NOT CHANGE THE NAMES OF THE FILE, CLASS or METHOD
class Homework6:
    def isPowerOfSeven(self, n):
        if n < 1:
            return False

        while n % 7 == 0:
            n = n // 7

        return n == 1

# For testing your code uncomment below lines.
# l = Homework6()
# print(l.isPowerOfSeven(343)) # True (7^3)
# print(l.isPowerOfSeven(50)) # False
# Comment or delete the above test code before submitting.

