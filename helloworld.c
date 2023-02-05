#include <stdio.h>
#include "src/raylib.h"

int main(void)
{

    InitWindow(400, 200, "hello idiots");

    while(!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(WHITE);

        EndDrawing();
    }

    CloseWindow();

    printf("you fucking bitch");
    return 0;
}