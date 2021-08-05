#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct CELLS {
    /*for a cell to be alive the following variable needs to have a value of 1,
    for the cell to be dead it needs to have a value of 0*/
    int cell_live_or_dead;
    int cell_age;
} all_cells[50][78],temp_cells[50][78];

void getting_live_cells (char *infile) {

    char line[6];
    int count, y_pos, x_pos;
    FILE *pf;

    pf = fopen(infile,"r");
    count = 0;
    
    while (fgets(line,6,pf) != NULL) {

        if (count != 0) {
            sscanf(line,"%i %i", &y_pos,&x_pos);
            all_cells[y_pos][x_pos].cell_live_or_dead = 1;
            all_cells[y_pos][x_pos].cell_age = 0;
        }
        count++;

    }

    fclose(pf);
}

void print_board(int *w, int *h) {

    int width = *w;
    int height = *h;
    int y,x;

    for (y = -1;y <= height;y++) {
        for (x = -1;x <= width;x++) {
            
            if (y == -1 && x == -1 || y == -1 && x == width || y == height && x == -1 || y == height & x == width) {
                fprintf(stdout,"*");
                continue;
            }
            else if (x == -1 || x == width) {
                fprintf(stdout,"|");
            }
            else if (y == -1 || y == height) {
                fprintf(stdout,"-");
                continue;
            }
            else if ((x > -1 && x <= width) && (all_cells[y][x].cell_live_or_dead == 0)) printf(" ");
            else if (all_cells[y][x].cell_live_or_dead == 1) fprintf(stdout,"%i",(all_cells[y][x].cell_age));
        }
        puts(" ");
    }

    puts("");
    puts("");
}


void generation(int *w, int *h) {

    int width = *w;
    int height = *h;
    int y,x;
    int a,b;
    int neighbours;

    for (y=0;y<height;y++) {
        for (x=0;x<width;x++) {
            neighbours = 0;
            for (a=-1;a<2;a++) {
                for (b=-1;b<2;b++) {
                    
                    if ((y+a < 0) || (x+b < 0)) continue;
                    if (a == 0 && b == 0) continue;
                    if (all_cells[y+a][x+b].cell_live_or_dead == 1) neighbours++;
                }
            }
        
            /*Sets the cell to being dead if there is less than 2 neighbours and the cell is already alive*/
            if (all_cells[y][x].cell_live_or_dead == 1 && (neighbours<2)) {
                temp_cells[y][x].cell_live_or_dead = 0;
                temp_cells[y][x].cell_age = 0;
            }
            
            /*Keeps the cell alive if it has exactly 2 or 3 neighbours and is already alive*/
            if (all_cells[y][x].cell_live_or_dead == 1 && (neighbours == 2 || neighbours == 3)) {
                temp_cells[y][x].cell_live_or_dead = 1;
                temp_cells[y][x].cell_age += 1;
            }
            
            /*Sets the cell to being dead if theres more than 3 neighbours and the cell is already alive*/
            if (all_cells[y][x].cell_live_or_dead == 1 && (neighbours > 3)) {
                temp_cells[y][x].cell_live_or_dead = 0;
                temp_cells[y][x].cell_age = 0;
            }
            
            /*Sets the cell to being alive if it has exactly 3 neighbours and it is already dead*/
            if (all_cells[y][x].cell_live_or_dead == 0 && neighbours == 3) {
                temp_cells[y][x].cell_live_or_dead = 1;
            }
        }
    }

    for (y = 0;y < height;y++) {
        for (x = 0;x < width;x++) {
            all_cells[y][x].cell_live_or_dead = temp_cells[y][x].cell_live_or_dead;
            all_cells[y][x].cell_age = temp_cells[y][x].cell_age;
        }
    }

}

int main (int argc, char* argv[]) {

    char line[6];
    int count,y_pos,x_pos,Number_of_live_cells;
    int width, height;
    int round;
    char *infile;

    int *w = &width;
    int *h = &height;

    if (argc != 5) {
        fprintf(stderr, "Not enough input parameters!");
        return EXIT_FAILURE;
    }

    infile = argv[1]; 
    width = atoi(argv[2]);
    height = atoi(argv[3]);
    round = atoi(argv[4]);


    /*sets all the cells to be dead*/
    for (int y=0;y<height;y++) {
        for (int x=0;x<width;x++) {
            all_cells[y][x].cell_live_or_dead = 0;
        }
    }

    getting_live_cells(infile);
    print_board(w,h);

    for (int y=0;y<round;y++) {
        generation(w,h);
        print_board(w,h);
        if (y==round-1) {
            printf("Finished");
        }
    }
}