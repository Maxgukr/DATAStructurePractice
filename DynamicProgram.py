'''
53. 最大子序和
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
'''


def maxSubArray(nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    s = max(nums)
    i = j = nums.index(s)
    n = 1
    while n <= len(nums):
        i-=1
        s1 = sum(nums[max(i, 0):min(j + 1, len(nums))])
        j+=1
        s2 = sum(nums[i:min(j + 1, len(nums))])
        s=max([s,s1,s2])
        n = n + 1
    return s

def main():
    nums=[-2,1,-3,4,-1,2,1,-5,4]
    maxSubArray(nums)

if __name__=="__main__":
    main()