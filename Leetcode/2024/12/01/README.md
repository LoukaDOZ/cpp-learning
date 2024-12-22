# 1346. Check If N and Its Double Exist

Given an array `arr` of integers, check if there exist two indices `i` and `j` such that :
- `i != j`
- `0 <= i, j < arr.length`
- `arr[i] == 2 * arr[j]`


# Example 1

| input              | Output | Explanation                                              |
|--------------------|--------|----------------------------------------------------------|
| `arr = [10,2,5,3]` | `true` | For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j] |

# Example 2

| input              | Output  | Explanation                                      |
|--------------------|---------|--------------------------------------------------|
| `arr = [3,1,7,11]` | `false` | There is no i and j that satisfy the conditions. |

# Example 3

| input                         | Output                | Explanation                                                                                                                                    |
|-------------------------------|-----------------------|------------------------------------------------------------------------------------------------------------------------------------------------|
| `pairs = [[1,2],[1,3],[2,1]]` | `[[1,2],[2,1],[1,3]]` | <ul><li>This is a valid arrangement since endi-1 always equals starti.</li><li>end0 = 2 == 2 = start1</li><li>end1 = 1 == 1 = start2</li></ul> |

# Constraints

- `2 <= arr.length <= 500`
- `-10^3 <= arr[i] <= 10^3`