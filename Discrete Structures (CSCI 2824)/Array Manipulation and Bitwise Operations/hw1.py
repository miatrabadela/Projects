#DO NOT CHANGE THE NAMES OF THE FILE, CLASS or METHOD
class BitWise:
    def BitAND(self,arr1, arr2):
        result = []
        for i in range(len(arr1)):
            result.append(arr1[i] & arr2[i])
        return result

# For testing your code uncomment below lines.

# f = BitWise()
# print(f.BitAND([1,1,1], [0,1,0]))
# print(f.BitAND([1,1,1,0], [0,0,1,0]))
# print(f.BitAND([0,0,1,1,0], [0,1,0,1,1]))
#Comment or delete the above code before submitting
