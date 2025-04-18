# 2558. Take Gifts From the Richest Pile

You are given an integer array `gifts` denoting the number of gifts in various piles. Every second, you do the following:

- Choose the pile with the maximum number of gifts.
- If there is more than one pile with the maximum number of gifts, choose any.
- Leave behind the floor of the square root of the number of gifts in the pile. Take the rest of the gifts.

Return the number of gifts remaining after `k` seconds.

# Example 1

| input                            | Output | Explanation                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
|----------------------------------|--------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `gifts = [25,64,9,4,100], k = 4` | `4`    | <ul><li>The gifts are taken in the following way:</li><li>In the first second, the last pile is chosen and 10 gifts are left behind.</li><li>Then the second pile is chosen and 8 gifts are left behind.</li><li>After that the first pile is chosen and 5 gifts are left behind.</li><li>Finally, the last pile is chosen again and 3 gifts are left behind.</li><li>The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.</li></ul> |

# Example 2

| input                      | Output | Explanation                                                                                                                                                                                                     |
|----------------------------|--------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `gifts = [1,1,1,1], k = 4` | `4`    | <ul><li>In this case, regardless which pile you choose, you have to leave behind 1 gift in each pile.</li><li>That is, you can't take any pile with you.</li><li>So, the total gifts remaining are 4.</li></ul> |

# Constraints

- `1 <= gifts.length <= 10^3`
- `1 <= gifts[i] <= 10^9`
- `1 <= k <= 10^3`