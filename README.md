# Game-of-Life
An example of Conways game of life programmed on C.

The game of life is an example of cellular automation and is played on an infinte 2D rectangular grid. The rules are as follows:

  -> If a cell is alive and it has less than 2 live neighbours is dies, as if by under-population.
  -> If a cell is alive and exactly 2 or 3 it lives on to the next generation.
  -> If a cell is alive and has more than 3 live neighbours it dies, as if by overcrowding.
  -> If a cell is dead and has exactly 3 live neighbours is becomes alive, as if by reproduction.
  
To run the program you need to pass 4 arguments:
  
  -> A file with all the coordinates of live cells for the first generation.
  -> An integer for the width
  -> An integer for the height
  -> An intefer for the number of generations you want.
  
For example you would compile the code as follows: gcc GameOfLife.c -o life
For example you would run the code as follows: ./ life traffic 5 5 3

