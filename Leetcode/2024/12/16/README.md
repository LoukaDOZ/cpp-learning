# 3264. Final Array State After K Multiplication Operations I

You are given an integer array `nums`, an integer `k`, and an integer `multiplier`.

You need to perform `k` operations on `nums`. In each operation:

- Find the minimum value `x` in `nums`. If there are multiple occurrences of the minimum value, select the one that appears first.
- Replace the selected minimum value `x` with `x * multiplier`.

Return an integer array denoting the final state of `nums` after performing all `k` operations.

# Example 1

| input                                       | Output        | Explanation                                                                                                                                                                                                                                                                                                                                                      |
|---------------------------------------------|---------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `nums = [2,1,3,5,6], k = 5, multiplier = 2` | `[8,4,6,5,6]` | <table><tr><th>Operation</th><th>Result</th></tr><tr><td>After operation 1</td><td>[2, 2, 3, 5, 6]</td></tr><tr><td>After operation 2</td><td>[4, 2, 3, 5, 6]</td></tr><tr><td>After operation 3</td><td>[4, 4, 3, 5, 6]</td></tr><tr><td>After operation 4</td><td>[4, 4, 6, 5, 6]</td></tr><tr><td>After operation 5</td><td>[8, 4, 6, 5, 6]</td></tr></table> |

# Example 2

| input                                 | Output   | Explanation                                                                                                                                                                                                      |
|---------------------------------------|----------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `nums = [1,2], k = 3, multiplier = 4` | `[16,8]` | <table><tr><th>Operation</th><th>Result</th></tr><tr><td>After operation 1</td><td>[4, 2]</td></tr><tr><td>After operation 2</td><td>[4, 8]</td></tr><tr><td>After operation 3</td><td>[16, 8]</td></tr></table> |

# Constraints

- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`
- `1 <= k <= 10`
- `1 <= multiplier <= 5`