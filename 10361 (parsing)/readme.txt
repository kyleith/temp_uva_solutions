10361 - Automatic Poetry
https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=96&page=show_problem&problem=1302


The input has format:
s1<s2>s3<s4>s5
s6...

The result must be:
s1s2s3s4s5
s6s4s3s2s5

s1-s6 are substrings.

The solution uses std::pair<int,int> to represent [firstIndex, lastIndex] of substring location in a line.
Then pairs are encoded and printed in the required order.