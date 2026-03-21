# DO NOT CHANGE THE NAMES OF THE FILE, CLASS or METHOD
class ValueMultiple:
    def check_even_three(self, number_given):
        if number_given % 2 == 0:
            if number_given % 3 == 0:
                return "Even multiple of 3"
            else:
                return "Even non-multiple of 3"
        else:
            if number_given % 3 == 0:
                return "Odd multiple of 3"
            else:
                return "Odd non-multiple of 3"
# For testing your code uncomment below lines.
# f = ValueMultiple()
# print(f.check_even_three(6)
# print(f.check_even_three(16)
# print(f.check_even_three(9)
# print(f.check_even_three(11)
#Comment or delete the above code before submitting