# K-th Smallest Number in a Running Window

## Problem definition
Given a sequence of integers, your program should identify the K-th smallest number in a running window of M integers.

## I/O formats
### Input format
Line#1: Three integers N, M, K, seperated by space.
N is the total length of the input sequence (1<=N<=200000).
M is the size of the running window (1<=M<=100000, M<=N)
K is the interger such that your program can find the the K-th smallest integer in a running window (1<=K<=M)
Line#2: A sequence of N integers a1, a2,... , an, (1<=ai<=2147483647)
### Output format
When the running window is moving from left to right, output the K-th smallest integer in one line. The first running window should contain the first M elements of the sequence. Eventually there should be N-M+1 output, with each output in a line.

## Slide
http://mirlab.org/jang/courses/dsa/homework/2019/hw01/?count=1&dueDate=20190318%2023:59:59
