# TODOS for HW2

- DD Figure out game state
  - how to store board
- DD Do file parsing

  - read input format of othello board

- DD Do calculateTurnMoves function

  - move must be on empty space
  - must be adjacent enemy piece
  - must be in line with one of your pieces

- DD Do playTurnMove
  - Flip pieces based on choice
  - calculate change of / total score
  - toggle in place

TODO

- Do basic evaluation function
- Do minimax
- Do alpha-beta pruning
- Do goated evaluation
- Have to think about persistent game state
  - keep track of your moves and opponents move
  - keep track of last game state
    - use last game state to calculate opponents move
  - keep track of previous allowed moves
  - then use their move to calculate how allowed moves changes
    - HUGE OPTIMIZATION
- Have to also think about calibration
  - needa discuss with other people how they did their calibration
