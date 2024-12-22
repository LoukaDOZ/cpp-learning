# 3152. Special Array II

An array is considered special if every pair of its adjacent elements contains two numbers with different parity.

You are given an array of integer `nums` and a 2D integer matrix queries, where for `queries[i]` = [fromi, toi] your task is to check that
subarray `nums[fromi..toi]` is special or not.

Return an array of booleans `answer` such that `answer[i]` is `true` if `nums[fromi..toi]` is special.

# Example 1

| input                                   | Output  | Explanation                                           |
|-----------------------------------------|---------|-------------------------------------------------------|
| `nums = [3,4,1,2,6], queries = [[0,4]]` | `false` | The subarray is `[3,4,1,2,6]`. 2 and 6 are both even. |

# Example 2

| input                                       | Output         | Explanation                                                                                                                                                                                                                                                       |
|---------------------------------------------|----------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `nums = [4,3,1,6], queries = [[0,2],[2,3]]` | `[false,true]` | <ul><li>The subarray is `[4,3,1]`. 3 and 1 are both odd. So the answer to this query is `false`.</li><li>The subarray is `[1,6]`. There is only one pair: `(1,6)` and it contains numbers with different parity. So the answer to this query is `true`.</li></ul> |

# Constraints

- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^5`
- `1 <= queries.length <= 10^5`
- `queries[i].length == 2`
- `0 <= queries[i][0] <= queries[i][1] <= nums.length - 1`