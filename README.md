Twenty-First Century Prison Chess
=================================

Board Class
-----------

- Has pieces

Piece Class
-----------

- Has common piece properties
- Subclasses implement procedures

Move Checking
-------------

1.  **Is move valid?** Can the piece at position 1 move to position2 give it's
    "is move valid" rulesets.
2.  **Is it not blocked?** In the piece's attempt to move from position 1 to
    position 2 is it blocked by a piece.
3.  **Can take piece is occupied?** If a piece is already at position 2 is it
    of the other team so that the piece can take it?
4.  **Resolve move to temporary state** Create a temporary board state having
    resolved the move.
5.  **Does move put self into check?** If after resolving the move, is does the
    player end up in check. If it does, discard temporary state. If 

Sources
-------

-   [Chess Images](http://www.clker.com/clipart-7190.html)
-   [Font](https://www.behance.net/gallery/19484739/Big-John-Slim-Joe-FREE-Font)
