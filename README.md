# MulPers
An unnecessary tool nobody asked for that finds numbers with high multiplicative persistence.

It iterates through every base-10 number with n digits and finds the lowest number with the highest multiplicative persistence for any n-digit number. It does so until you kill the process or unplug the power supply. 

Here is how it works:
- it works with numbers represented by a vector of digits between 0-9. So you could also use it to find MP's of other bases. 
Base 2 is especially interesting. The vector representation also works with numbers with many digits and doesn't overflow after two seconds. (Not that anything interesting happens after 277777788888899 unless you have a super computer.)
- It only checks numbers with increasing digits. A number 311 will always have the same MP as 113. This is what makes this code somewhat fast since most of the number with n digits can be skipped. 

Output looks something like this:

```
10E0: Winner is 1 with 0 steps (0ms)
10E1: Winner is 77 with 4 steps (0ms)
10E2: Winner is 679 with 5 steps (0ms)
10E3: Winner is 6788 with 6 steps (0ms)
10E4: Winner is 68889 with 7 steps (0ms)
10E5: Winner is 168889 with 7 steps (0ms)
10E6: Winner is 2677889 with 8 steps (2ms)
10E7: Winner is 26888999 with 9 steps (2ms)
10E8: Winner is 126888999 with 9 steps (5ms)
10E9: Winner is 3778888999 with 10 steps (10ms)
10E10: Winner is 13778888999 with 10 steps (17ms)
10E11: Winner is 113778888999 with 10 steps (35ms)
10E12: Winner is 1113778888999 with 10 steps (78ms)
10E13: Winner is 11113778888999 with 10 steps (140ms)
10E14: Winner is 277777788888899 with 11 steps (246ms)
10E15: Winner is 1277777788888899 with 11 steps (158ms)

```
