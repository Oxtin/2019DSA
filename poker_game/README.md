# Best strategy in a poker game

## Problem definition
* Alice and Bob are playing a simple poker game with the following rules:
* Each player gets n cards from the deck, and all the cards are open to both players.
* Alice moves first, and then they take turns to play cards.
* At each move, the current player can only play a card that has the same suit or number as the previous one.
* A player can pass if and only if there is no suitable card in his/her hand.
* When a player passes, the next player can play any card in his/her hand.
* The game stops when one of the players has no more card in his/her hand.

When the game ends, the loser still has some cards at hand, and the total points of these cards indicate how much the loser needs to pay the winner. (A card's points are defined by its number, as explain below.)

During the game, the winner wants to maximize the points of the loser's remaining cards, while the loser want to minimize it. Your mission is to design a stragegy for both players to play optimally, and find out who is the winner and the remaining points of the loser.

A card can be denoted by its suit and number:
* A suit can be represented by C (club), D (diamond), H (heart), and S (spade).
* A number can be represented by A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K.

Therefore a card can be represented by a two-character string, such as "DT" (diamond 10) or "SA" (spade A), etc.

Note that a card's points are denoted by its number, such that A==>1, 2==>2, 3==>3, ..., 9==>9, T==>10, J==>11, Q==>12, K==>13.

## I/O formats
### Input format
* Line 1 is a single integer n (n≤17), which is the number of cards for each player initially.
* Line 2 lists Alice's cards with n distinct space-separated two-characters string
* Line 3 lists Bob's cards similarly.
### Output format
* Line 1 is the winner, "Alice" or "Bob", without quotes.
* Line 2 is the total remaining points of the loser.

## Hints and Suggestions
* You need to use some pruning method, such as alpha-beta cut.
* You need to memorize some results obtained previously (using unordered map or hash).

## Slide
http://mirlab.org/jang/courses/dsa/homework/2019/hw03/?count=3&dueDate=20190430%2023:59:59
