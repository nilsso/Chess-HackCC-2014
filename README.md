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

        **TRUE**: Return `INVALID`.

    2.  Is that move blocked by another piece?

        **True**: Return `BLOCKED`.

Create temporary board state with piece moved.

2.  Post-move
    1.  Would the current board state expose you you *check*?

        **True**: Return `OWN_KING_CHECK`.

Return `VALID`.

