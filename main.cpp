#include "src/raylib.h"


struct Ball
{
    float x,y;
    float speedX , speedY;
    float radius;
    
    void Draw()
    {
        DrawCircle(x, y , radius, WHITE);
    }

}ball;

struct Paddle
{
    float X, Y;
    float width, height;
    float speed;

   
    Rectangle Colli()
    {
        return Rectangle{X - width/2, Y , 10, 100};
       // return Rectangle{X - width/2, Y , 10, 100};
    }
    void Draw()
    {
        DrawRectangle(X - width/2, Y , 10, 100, WHITE);
    }
}leftPaddle, rightPaddle;




int main()
{
   
    InitAudioDevice();
    
    const char* winner = nullptr;
     struct Ball ball ; 
    //ball
      ball.x = 400.0f;
      ball.y = 200.0f;
      ball.speedX = 150;  
      ball.speedY = 150;
      ball.radius = 5;
    
    //leftpaddle
    struct Paddle leftPaddle;
    leftPaddle.X = 50;
    leftPaddle.Y = 200 ;
    leftPaddle.width = 10;
    leftPaddle.height = 100;
    leftPaddle.speed = 300;

    //rightPaddle
    struct Paddle rightPaddle;
    rightPaddle.X =  750;
    rightPaddle.Y =  200 ;
    rightPaddle.width = 10;
    rightPaddle.height = 100;
    rightPaddle.speed = 300;

    //balltexture
    Image Img = LoadImage("resources/sprites.png");

    //sound loading
    Sound fxhit = LoadSound("resources/hit.wav");
    Sound fxselect = LoadSound("resources/select.wav");


    //window Intialized
    InitWindow(800, 500, "PONG-recreated in raylib by mithil");
    

    SetWindowState(FLAG_VSYNC_HINT);

    while(!WindowShouldClose())
    {
         ball.x += ball.speedX * GetFrameTime();
         ball.y += ball.speedY * GetFrameTime();
        
        //ball window collision
         if(ball.y > GetScreenHeight())
        {
            ball.y = GetScreenHeight();
            ball.speedY *= -1;
            PlaySound(fxhit);
        }
         if(ball.y < 0)
         {
            ball.y = 0;
            ball.speedY *= -1;
            PlaySound(fxhit);
         }

         //paddle collision

         //leftpaddle
         if(leftPaddle.Y > 400)
         {
            leftPaddle.Y = 400;
         }
         if(leftPaddle.Y < 0)
         {
            leftPaddle.Y = 0;
            
         }

         //right paddle
         if(rightPaddle.Y > 400)
         {
            rightPaddle.Y = 400;
         }
         if (rightPaddle.Y < 0)
         {          
            rightPaddle.Y = 0;
         }
         


         //input left paddle
         if(IsKeyDown(KEY_W))
         {
            leftPaddle.Y -= leftPaddle.speed * GetFrameTime();
         }
         else if(IsKeyDown(KEY_S))
         {
            leftPaddle.Y += leftPaddle.speed * GetFrameTime();
         }

         //INPUT RIGHT PADDLE 
         if (IsKeyDown(KEY_UP))
         {
            rightPaddle.Y -= rightPaddle.speed * GetFrameTime();
         }
         else if(IsKeyDown(KEY_DOWN))
         {
            rightPaddle.Y += rightPaddle.speed * GetFrameTime();
         }

         //collision for pads
         if (CheckCollisionCircleRec(Vector2{(float)ball.x, (float)ball.y}, ball.radius , leftPaddle.Colli()))
         {
            if(ball.speedX < 0)
            {
                 ball.speedX *= -1.1f;
                 PlaySound(fxhit);
            }
           
         }

         if(CheckCollisionCircleRec(Vector2{(float) ball.x, (float)ball.y}, ball.radius , rightPaddle.Colli())) 
         {
            if(ball.speedX > 0)
            {
                ball.speedX *= -1.1f;
                PlaySound(fxhit);
            }
            
         }

         //collision for paddle


         //winning criteria 
         if( ball.x < 0)
         {
            winner = "right wins!";
             ball.x = -10.0f;
             ball.y = 000.0f;
             ball.speedX = 0;  
            ball.speedY = 0;
         }
         else if ( ball.x > GetScreenWidth()
         )
         {
            winner =  "left wins!";
             ball.x = -10.0f;
             ball.y = 000.0f;
             ball.speedX = 0;  
            ball.speedY = 0;
         }

         if(winner && IsKeyDown(KEY_SPACE))
         {

             winner = nullptr;
             ball.x = 400.0f;
             ball.y = 200.0f;
             ball.speedX = 150;  
            ball.speedY = 150;
            PlaySound(fxselect);

         }
     
         
         
        BeginDrawing();
            //ImageClearBackground("resources/bg/jpg", WHITE);
            ClearBackground(DARKGRAY);

            //rendering
            ball.Draw();
            leftPaddle.Draw();
            rightPaddle.Draw();

           // DrawTexture(Img, 500, 200, WHITE);
            
           

            if(winner)
            {
                
                DrawText("use SPACE bar to replay",GetScreenWidth() -650,GetScreenHeight()/4 -50, 40, YELLOW);
                DrawText(winner, GetScreenWidth() -600, GetScreenHeight()/2 -30 , 90, RED);
            }


            DrawFPS(10, 10);
        EndDrawing();
    }
      UnloadSound(fxselect);
      UnloadSound(fxhit);
    CloseWindow();

    return 0;
}