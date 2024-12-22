# 769. Max Chunks To Make Sorted

You are given an integer array `arr` of length `n` that represents a permutation of the integers in the range `[0, n - 1]`.

We split `arr` into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.

Return the largest number of chunks we can make to sort the array.

# Example 1

| input               | Output | Explanation                                                                                                                                                                                        |
|---------------------|--------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `arr = [4,3,2,1,0]` | `1`    | <ul><li>Splitting into two or more chunks will not return the required result.</li><li>For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.</li></ul> |

# Example 2

| input               | Output | Explanation                                                                                                                                                                |
|---------------------|--------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `arr = [1,0,2,3,4]` | `4`    | <ul><li>We can split into two chunks, such as [1, 0], [2, 3, 4].</li><li>However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.</li></ul> |

# Constraints

- `n == arr.length`
- `1 <= n <= 10`
- `0 <= arr[i] < n`
- All the elements of `arr` are unique.