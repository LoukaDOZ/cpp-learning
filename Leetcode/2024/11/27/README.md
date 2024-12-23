# 3243. Shortest Distance After Road Addition Queries I

You are given an integer `n` and a 2D integer array `queries`.

There are `n` cities numbered from `0` to `n - 1`. Initially, there is a unidirectional road from city `i` to city `i + 1` for all `0 <= i < n - 1`.

`queries[i] = [ui, vi]` represents the addition of a new unidirectional road from city `ui` to city `vi`. After each query, you need to find the length of the shortest path from city `0` to city `n - 1`.

Return an array `answer` where for each `i` in the range `[0, queries.length - 1]`, `answer[i]` is the length of the shortest path from city `0` to city `n - 1` after processing the first `i + 1` queries.

# Example 1

| input                          | Output | Explanation                                                                            |
|--------------------------------|--------|----------------------------------------------------------------------------------------|
| `n = 5, queries = [[2,4],[0,2],[0,4]]` | `[3,2,1]` | <ul><li>![Example 1-1](assets/image.png)</li><li>After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.</li><li>![Example 1-2](assets/image-1.png)</li><li>After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.</li><li>![Example 1-3](assets/image-2.png)</li><li>After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.</li></ul> |

# Example 2

| input                          | Output | Explanation                                                                            |
|--------------------------------|--------|----------------------------------------------------------------------------------------|
| `n = 4, queries = [[0,3],[0,2]]` | `[1,1]` | <ul><li>![Example 2-1](assets/image-3.png)</li><li>After the addition of the road from 0 to 3, the length of the shortest path from 0 to 3 is 1.</li><li>![Example 2-2](assets/image-4.png)</li><li>After the addition of the road from 0 to 2, the length of the shortest path remains 1.</li></ul> |

# Constraints

- `3 <= n <= 500`
- `1 <= queries.length <= 500`
- `queries[i].length == 2`
- `0 <= queries[i][0] < queries[i][1] < n`
- `1 < queries[i][1] - queries[i][0]`
- There are no repeated roads among the queries.