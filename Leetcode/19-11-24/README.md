# 2461. Maximum Sum of Distinct Subarrays With Length K

You are given an integer array `nums` and an integer `k`. Find the maximum subarray sum of all the subarrays of `nums` that meet the following conditions:

The length of the subarray is `k`, and all the elements of the subarray are distinct.

Return the maximum subarray sum of all the subarrays that meet the conditions. If no subarray meets the conditions, return `0`.

A subarray is a contiguous non-empty sequence of elements within an array.

#### Example 1:

| input                           | Output | Explanation                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
|---------------------------------|--------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `nums = [1,5,4,2,9,9,9], k = 3` | `15`   | The subarrays of nums with length 3 are: <ul><li>[1,5,4] which meets the requirements and has a sum of 10.</li><li>[1,5,4] which meets the requirements and has a sum of 10.</li><li>[4,2,9] which meets the requirements and has a sum of 15.</li><li>[2,9,9] which does not meet the requirements because the element 9 is repeated.</li><li>[9,9,9] which does not meet the requirements because the element 9 is repeated.</li></ul>We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions. |

#### Example 2:

| input                   | Output | Explanation                                                                                                                                                                                     |
|-------------------------|--------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `nums = [4,4,4], k = 3` | `0`    | The subarrays of nums with length 3 are: <ul><li>[4,4,4] which does not meet the requirements because the element 4 is repeated.</li></ul>We return 0 because no subarrays meet the conditions. |
 
#### Constraints:

`1 <= k <= nums.length <= 105`\
`1 <= nums[i] <= 105`

