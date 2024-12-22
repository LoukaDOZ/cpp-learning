# 2516. Take K of Each Character From Left and Right

You are given a string `s` consisting of the characters `'a'`, `'b'`, and `'c'` and a non-negative integer `k`. Each minute, you may take either the leftmost character of `s`, or the rightmost character of `s`.

Return the minimum number of minutes needed for you to take at least `k` of each character, or return `-1` if it is not possible to take `k` of each character.

 

#### Example 1:

| input                       | Output | Explanation                                                                                                                                                                                                                                                                                                                                                         |
|-----------------------------|--------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `s = "aabaaaacaabc", k = 2` | `8`    | <ul><li>Take three characters from the left of s. You now have two 'a' characters, and one 'b' character.</li><li>Take five characters from the right of s. You now have four 'a' characters, two 'b' characters, and two 'c' characters.</li><li>A total of 3 + 5 = 8 minutes is needed.</li></ul>It can be proven that 8 is the minimum number of minutes needed. |

#### Example 2:

| input                 | Output | Explanation                                             |
|-----------------------|--------|---------------------------------------------------------|
| `s = "s = "a", k = 1` | `-1`   | It is not possible to take one 'b' or 'c' so return -1. |

#### Constraints:

`1 <= s.length <= 10^5`\
`s consists of only the letters 'a', 'b', and 'c'.`\
`0 <= k <= s.length`