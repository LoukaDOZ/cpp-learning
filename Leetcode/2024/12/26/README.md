# 494. Target Sum

You are given an integer array `nums` and an integer `target`.

You want to build an expression out of nums by adding one of the symbols `'+'` and `'-'` before each integer in nums and then concatenate all the integers.

- For example, if `nums = [2, 1]`, you can add a `'+'` before `2` and a `'-'` before `1` and concatenate them to build the expression `"+2-1"`.

Return the number of different expressions that you can build, which evaluates to `target`.

# Example 1

| input                            | Output | Explanation                                                                                                                                                                                                                                          |
|----------------------------------|--------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `nums = [1,1,1,1,1], target = 3` | `5`    | <ul><li>There are 5 ways to assign symbols to make the sum of nums be target 3.</li><li>-1 + 1 + 1 + 1 + 1 = 3</li><li>+1 - 1 + 1 + 1 + 1 = 3</li><li>+1 + 1 - 1 + 1 + 1 = 3</li><li>+1 + 1 + 1 - 1 + 1 = 3</li><li>+1 + 1 + 1 + 1 - 1 = 3</li></ul> |

# Example 2

| input                    | Output | Explanation                                                                                                                                                                                                                                                                                      |
|--------------------------|--------|
| `nums = [1], target = 1` | `1`    |

# Constraints

- `1 <= nums.length <= 20`
- `0 <= nums[i] <= 1000`
- `0 <= sum(nums[i]) <= 1000`
- `-1000 <= target <= 1000`