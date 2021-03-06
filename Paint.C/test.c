// Assignment 1 19T2 COMP1511: CS Paint
// paint.c
//
// This program was written by CHAITANYA NARAYAN (z5254637)
// on 02/07/2019
//
// Version 1.0.0 (2019-06-22): Assignment released.

#include <stdio.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define WHITE 4

// IF YOU NEED MORE #defines ADD THEM HERE
#define LINE 1
#define RECTANGLE 2
#define COLOUR 3
#define COPY_PASTE 5

// Provided helper functions:
// Print out the canvas.
void printCanvas(int canvas[N_ROWS][N_COLS]);
// Set the entire canvas to be blank.
void setBlankCanvas(int canvas[N_ROWS][N_COLS]);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE
//Array border
void array_border(int start_row, int start_col, int end_row, 
int end_col);

//Horizontal/Vertical/Diagonal
void line_draw(int start_row, int start_col, int end_row, int end_col, 
int canvas[N_ROWS][N_COLS], int new_shade);

//Rectangle fill
void rectangle_draw(int start_row, int start_col, int end_row, int end_col, 
int canvas[N_ROWS][N_COLS], int new_shade);

//Copy + Paste
void copy_paste(int start_row, int start_col, int end_row, int end_col, 
int target_row, int target_col, int canvas[N_ROWS][N_COLS], int new_shade); 

int main(void) {
    int canvas[N_ROWS][N_COLS];

    setBlankCanvas(canvas);

    // TODO: Add your code here!
    int instruction = {0}; 
    int start_row;
    int start_col;
    int end_row;
    int end_col;
    // Multi_input allows for multiple lines to be read
    int multi_input = 1; 
    int new_shade = 0;
    int target_row;
    int target_col;
    
    while (multi_input == LINE) {
        //scan the instruction
        multi_input = scanf("%d", &instruction);  
        
        //Scan the input line
        if (instruction == LINE || instruction == RECTANGLE) {
            scanf("%d %d %d %d", &start_row, &start_col, &end_row,
      	    &end_col);
      	    
            //Make the array border
            if (array_border(start_row, start_col, end_row, end_col)) { 
            /*(start_row < N_ROWS && start_row >= 0 && end_row < N_ROWS && 
            end_row >= 0 && start_col < N_COLS && start_col >= 0 
            && end_col < N_COLS && end_col >= 0)*/ //{ 
                
                //Stage 1.1 & Stage 2.1
                //Horizontal, Vertical, Diagonal Drawing
                if (instruction == LINE) {
                    line_draw(start_row, start_col, end_row, end_col, canvas, 
                    new_shade); 
                }           
                
                //Stage 1.2
                //Rectangle Drawing  
                else if (instruction == RECTANGLE) {
                    rectangle_draw(start_row, start_col, end_row, end_col, 
                    canvas, new_shade);
                }
           }
        }
        
        //Stage 2.2
        //Changing colours
        if (instruction == COLOUR) {
            int shade;
            scanf("%d", &shade);
            if (shade >= 0 && shade <= 4){
                new_shade = shade;
            }
        }
        
        //Stage 3.1
        //Copy + Paste
        if (instruction == COPY_PASTE) {
            scanf("%d %d %d %d %d %d", &start_row, &start_col, &end_row, 
            &end_col, &target_row, &target_col);
            copy_paste(start_row, start_col, end_row, end_col, target_row, 
            target_col, canvas, new_shade);
        }    
    }       
    printCanvas(canvas);
    return 0;
}
// ADD CODE FOR YOUR FUNCTIONS HERE
void array_border(int start_row, int start_col, int end_row, 
int end_col){
            (start_row < N_ROWS && start_row >= 0 && end_row < N_ROWS && 
            end_row >= 0 && start_col < N_COLS && start_col >= 0 
            && end_col < N_COLS && end_col >= 0);
}
void line_draw(int start_row, int start_col, int end_row, int end_col, 
int canvas[N_ROWS][N_COLS], int new_shade){
    
    //Horizontal Line
    if (start_row == end_row && start_col <= end_col) {
        while (start_col <= end_col) {
            canvas[start_row][start_col] = new_shade;
            start_col++;
        }
    }
    else if (start_row == end_row && start_col >= end_col) {
        while (start_col >= end_col) {
            canvas[start_row][start_col] = new_shade;
            start_col--;
        }
    }

    //Vertical Line
    if (start_col == end_col && start_row <= end_row) {
        while (start_row <= end_row) {
            canvas[start_row][start_col] = new_shade;
            start_row++;
        }
    }      
    else if (start_col == end_col && end_row <= start_row) {       
        while (end_row <= start_row) {
            canvas[start_row][start_col] = new_shade;
            start_row--;
        }
    }
    
    //Diagonal Line
    if (end_col - start_col == start_row - end_row) {
        //Positive Gradient Line
		int m = start_row; //Rows
        int n = start_col; //Columns
        if(start_col > end_col) {
        //IF BACK TO FRONT
                while (n >= end_col) {           
            		canvas[m][n] = new_shade;
      		  		m++;
      		  		n--;          
			    }  
        } 
        else {
                while (n <= end_col) {           
                    canvas[m][n] = new_shade;
                    m--;
                    n++;          
                }
        }  
    }
    else if (end_col - start_col == end_row - start_row) {
  		//Negative Gradient Line
		int m = start_row; //Rows
        int n = start_col; //Columns
        if(start_col > end_col) {
        //IF BACK TO FRONT
            while (m >= end_row) {           
                canvas[m][n] = new_shade;
                m--;
                n--;         
            }            		  
        } 
        else {
            while (n <= end_col) {           
            canvas[m][n] = new_shade;
            m++;
            n++;          
            }
        }
	}
}

//Draw filled rectangles
void rectangle_draw(int start_row, int start_col, int end_row, int end_col, 
int canvas[N_ROWS][N_COLS], int new_shade) {
    
    int swap; //swapping rows or cols
    if (start_col > end_col) {
        swap = start_col;
        start_col = end_col;
        end_col = swap;
    }
    if (start_row > end_row) {
        swap = start_row;
        start_row = end_row;
        end_row = swap;
    }
    
    int x = start_row;
    while (x <= end_row) {
        int y = start_col;
        while (y <= end_col) {
            canvas[x][y] = new_shade;
            y++;
        }
        x++;
    }
}

//Copy Paste
void copy_paste(int start_row, int start_col, int end_row, int end_col, 
int target_row, int target_col, int canvas[N_ROWS][N_COLS], int new_shade) {

}

// Prints the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
//
// You should not need to change the printCanvas function.
void printCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}


// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
//
// You should not need to change the setBlankCanvas function.
void setBlankCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}
