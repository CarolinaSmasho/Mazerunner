#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

char maze[MAX_SIZE][MAX_SIZE];
int rows = 0, cols = 0;

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Function prototypes
bool solveMaze(int x, int y);
void writeMazeToFile();
bool isSafe(int x, int y);

// Entry point
int main()
{
    FILE *file = fopen("MAP01.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Read the maze from the file
    char line[MAX_SIZE];
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^\n]", maze[rows]);
        cols = 0;
        while (line[cols] != '\0' && line[cols] != '\n')
            cols++;
        rows++;
    }
    fclose(file);

    // Find the start position 's'
    int startX = -1, startY = -1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 's')
            {
                startX = i;
                startY = j;
                break;
            }
        }
    }

    if (startX == -1 || startY == -1)
    {
        printf("Start position not found.\n");
        return 1;
    }

    // Solve the maze
    if (solveMaze(startX, startY))
    {
        printf("Solution found. Writing to 67010126.txt\n");
        writeMazeToFile(); // Write the solution to the file
    }
    else
    {
        printf("No solution found. Writing to 67010126.txt\n");
        FILE *outputFile = fopen("67010126.txt", "w");
        if (outputFile != NULL)
        {
            fprintf(outputFile, "No solution found.\n");
            fclose(outputFile);
        }
    }

    return 0;
}

// Check if the current position is valid to move to
bool isSafe(int x, int y)
{
    return (x >= 0 && x < rows && y >= 0 && y < cols && (maze[x][y] == ' ' || maze[x][y] == 'E'));
}

// Recursive function to solve the maze
bool solveMaze(int x, int y)
{
    // Base case: if we've reached the end
    if (maze[x][y] == 'E')
    {
        return true;
    }

    // Mark the current position as part of the solution path
    if (maze[x][y] == ' ')
    {
        maze[x][y] = '+';
    }

    // Try moving in all directions
    for (int i = 0; i < 4; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (isSafe(newX, newY))
        {
            if (solveMaze(newX, newY))
            {
                return true;
            }
        }
    }

    // Backtrack: unmark this position (no solution found here)
    if (maze[x][y] == '+')
    {
        maze[x][y] = ' ';
    }

    return false;
}

// Write the maze to the file "67010126.txt"
void writeMazeToFile()
{
    FILE *outputFile = fopen("67010126.txt", "w");
    if (outputFile == NULL)
    {
        printf("Error opening file to write.\n");
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fputc(maze[i][j], outputFile);
        }
        fputc('\n', outputFile); // Newline after each row
    }

    fclose(outputFile);
}
