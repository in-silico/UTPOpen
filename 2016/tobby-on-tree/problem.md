do you remember Tobby ? He is a very s̶m̶a̶r̶t̶ cute dog that lives in tobbyland.

Tobby lives in a city where any two houses are connected by exactly one path, and that path
is bidirectional. All the houses are identified by an integer $0 < id < N$, and have another
integer indicating the value of that house.

Tobby found on internet an interesting game called, "the substraction game" that goes as follow.

given a secuence of $N$ elements:  $a_0, a_1, ..., a_{n-1}$ :

    If all the numbers are equal, the game ends.
    Otherwise
        Select two numbers which are unequal
        Subtract the smaller number from the larger number
        Replace the larger number with the result from above.


The game *always* ends and no matter how you play, it will always terminate *on the same value*.
The result of a game is that value.

The game is so cool for toby that he decides to play it as much as possible, for this reason
each day Tobby visits two friends that live in the houses $u$ and $v$ and records all the values
of the houses in the path from $u$ to $v$ (inclusive) and at the final of the day he plays the substraction game with the secuence that he wrote.

The value of the house can change sometimes, but Tobby always will know the new value.

In order to help tobby, you are asked to respond the following type of queries.

      1. given u, v: Find the result of the substraction
                     game on the path from u to v (inclusive).
      2. given u, x: Change the value of the house u by x.


### Input:

The first line contains an integer $N \le 50000$, the number of houses.
The next line contains $N$ integers, the $i$-th number is the value of the $i$-th house $1 \le value \le 10000$.
The next $N - 1$ lines contain two integers $0 \le u, v \le N - 1$ indicating a connection between the houses $u$ and $v$.

Next line contains an integer $1 \le q \le 10000$ followed by $q$ lines each containing a query as described above.

### Output:

for each query $1 u v$, print the result of the substraction game in the path from $u$ to $v$.

### sample input:
<pre>
5
5 15 20 15 9
0 2
0 3
3 1
3 4
3

1 2 1
2 3 3
1 1 4
</pre>

### sample output:
<pre>
5
3
</pre>
