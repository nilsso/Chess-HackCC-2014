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

Move given *start position* and *end position*

1.  Pre-move
    1.  Could the piece move from start to end given piece's rule set?
        -   **True**: Return `INVALID`.
    2.  Is that move blocked by another piece?
        -   **True**: Return `BLOCKED`.
    3.   Create temporary board state with piece moved.
2.  Post-move
    1.  Would the current board state expose you you *check*?
    2.  **True**: Return `OWN_KING_CHECK`.
    -   Return `VALID`.

Sources
-------

-   [Chess Images](http://www.clker.com/clipart-7190.html)
-   [Font](https://www.behance.net/gallery/19484739/Big-John-Slim-Joe-FREE-Font)
