# DO NOT CHANGE THE NAMES OF THE FILE, CLASS or METHOD
class LocalMaxima:
    def find_local_maxima(self, array, left, right):
        n = len(array)
        if n == 0:
            return -1
        
        left = max(left, 0)
        right = min(right, n - 1)
        while left <= right:
            mid = (left + right) // 2
            mid_val = array[mid]
            if mid > 0:
                left_val = array[mid - 1] 
            else:
                left_val = float("-inf")
            if mid < n - 1:
                right_val = array[mid + 1]
            else:
                right_val = float("-inf")

            if mid_val >= left_val and mid_val >= right_val:
                return mid
            
            if left_val > mid_val:
                right = mid - 1
            else:
                left = mid + 1

        return -1
        
# For testing your code uncomment below lines.
# f = LocalMaxima()
# print(f.find_local_maxima([1,3,2,1],0,3))
# print(f.find_local_maxima([1,2,3,1],0,3))
# Comment or delete the above test code before submitting.