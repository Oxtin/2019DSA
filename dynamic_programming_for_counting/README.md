## Description：
You have a graph paper of size N by M, each grid is either O or X.

The action you can take is tearing it, and in each step, you can only choose one of two following operations to perform.


1. Select a piece of graph paper with more than one column and choose one of the columns filled with only O. Delete that column.

2. Select a piece of graph paper with more than one row and choose one of the rows filled with only O. Delete that row.

You can perform the operations above on the graph paper as many times as you want. 

Note that after performing an operation, that piece of paper may become two pieces.

The following demonstrates a viable way to the tear graph paper and its look after each step:

```
N = 4, M = 6
The graph paper looks like:
OOOOOO
OOOXXX
XXOOOO
OOOOOO
1. Choose the only piece, delete the third column, and there are two pieces now.
OO_OOO
OO_XXX
XX_OOO
OO_OOO
2. Choose the right piece, delete the third row of it, and there are three pieces now.
OO_OOO
OO_XXX
XX____
OO_OOO
3. Choose the upper right piece, delete the first row of it, and there are still three pieces.
OO____
OO_XXX
XX____
OO_OOO
4. Choose the lower right piece, delete the second column of it, and there are four pieces now.
OO____
OO_XXX
XX____
OO_O_O

......(you can perform more operations and stop at any time)

```

Now you are given the look of a graph paper, please calculate the number of ways to tear it.

Note: Two ways of tearing a graph paper are not regarded as the same if and only if there is a i such that the grids we delete are not identical in ith step in two ways.


## Input Format：
There are two integers N, M, which represent the size of the graph paper in the first line.
The next $N$ lines contain M characters each, which represents the graph paper.

## Output Format：
Print the number of ways to tear the graph paper modulo 10^9 + 7.

## Limit
1 <= N, M <= 10

## Sample inputs 1
```
1 2
OO
```
## Sample outputs 1
```
3
```
The three possibilities are:

1. No operations.
2. Delete the first column.
3. Delete the second column.

## Sample inputs 2
```
2 2
OO
OX
```
## Sample outputs 2
```
5
```
The five possibilities are:

1. No operations.
2. Delete the first column.
3. Delete the first row.
4. Delete the first row and than the first column.
5. Delete the first column and than the first row.

## Sample inputs 3
```
5 5
OOOOO
OOOOO
OOOOO
OOOOO
OOOOO
```
## Sample outputs 3
```
582176824
```

