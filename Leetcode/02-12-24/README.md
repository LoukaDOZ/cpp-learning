# 1455. Check If a Word Occurs As a Prefix of Any Word in a Sentence

Given a sentence that consists of some words separated by a single space, and a `searchWord`, check if `searchWord` is a prefix of any word in `sentence`.

Return the index of the word in `sentence` (1-indexed) where `searchWord` is a prefix of this word. If `searchWord` is a prefix of more than one word, return the index of the first word (minimum index). If there is no such word return `-1`.

A prefix of a string `s` is any leading contiguous substring of `s`.


# Example 1

| input                                                    | Output | Explanation                                                         |
|----------------------------------------------------------|--------|---------------------------------------------------------------------|
| `sentence = "i love eating burger", searchWord = "burg"` | `4`    | "burg" is prefix of "burger" which is the 4th word in the sentence. |

# Example 2

| input                                                              | Output | Explanation                                                                                                                |
|--------------------------------------------------------------------|--------|----------------------------------------------------------------------------------------------------------------------------|
| `sentence = "this problem is an easy problem", searchWord = "pro"` | `2`    | "pro" is prefix of "problem" which is the 2nd and the 6th word in the sentence, but we return 2 as it's the minimal index. |

# Example 3

| input                                         | Output | Explanation                                        |
|-----------------------------------------------|--------|----------------------------------------------------|
| `sentence = "i am tired", searchWord = "you"` | `-1`   | "you" is not a prefix of any word in the sentence. |

# Constraints

- `1 <= sentence.length <= 100`
- `1 <= searchWord.length <= 10`
- `sentence` consists of lowercase English letters and spaces.
-  `searchWord` consists of lowercase English letters.