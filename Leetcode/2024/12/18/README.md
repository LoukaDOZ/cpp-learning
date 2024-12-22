# 1475. Final Prices With a Special Discount in a Shop

You are given an integer array `prices` where `prices[i]` is the price of the `ith` item in a shop.

There is a special discount for items in the shop. If you buy the `ith` item, then you will receive a discount equivalent to `prices[j]` where `j` is the minimum index such that `j > i` and `prices[j] <= prices[i]`. Otherwise, you will not receive any discount at all.

Return an integer array `answer` where `answer[i]` is the final price you will pay for the `ith` item of the shop, considering the special discount.

# Example 1

| input                  | Output        | Explanation                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
|------------------------|---------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `prices = [8,4,6,2,3]` | `[4,2,4,2,3]` | <ul><li>For item 0 with price[0]=8 you will receive a discount equivalent to prices[1]=4, therefore, the final price you will pay is 8 - 4 = 4.</li><li>For item 1 with price[1]=4 you will receive a discount equivalent to prices[3]=2, therefore, the final price you will pay is 4 - 2 = 2.</li><li>For item 2 with price[2]=6 you will receive a discount equivalent to prices[3]=2, therefore, the final price you will pay is 6 - 2 = 4.</li><li>For items 3 and 4 you will not receive any discount at all.</li></ul> |

# Example 2

| input                  | Output        | Explanation                                                            |
|------------------------|---------------|------------------------------------------------------------------------|
| `prices = [1,2,3,4,5]` | `[1,2,3,4,5]` | In this case, for all items, you will not receive any discount at all. |

# Example 3

| input                 | Output      |
|-----------------------|-------------|
| `prices = [10,1,1,6]` | `[9,0,1,6]` |

# Constraints

- `1 <= prices.length <= 500`
- `1 <= prices[i] <= 1000`