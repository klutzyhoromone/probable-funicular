


#define SAMPLES 30 

#include "everything.c"



int main(void)
{

  
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");
  SetTargetFPS(60);              
  Vector2 point1 = {100, 100};
  Vector2 point2 = {200, 100};
  Vector2 point3 = {300, 100};
  Vector2 point4 = {300, 150};
  Vector2 point5 = {300, 200};
  Vector2 point6 = {(300+100)/2, 200};
  Vector2 point7 = {100, 200};
  Vector2 point8 = {100, 150};
  Vector2 *curve1;
  Vector2 *curve2;
  Vector2 *curve3;
  Vector2 *curve4;
      Vector2 allPoints[8] = {
        point1,
        point2,
        point3,
        point4,
        point5,
        point6,
        point7,
        point8
      };


  while (!WindowShouldClose())
    {
      
      DrawFPS(20, 20);

      Vector2 mouse = GetMousePosition();

      checkPositions(mouse, allPoints);
      DrawText(TextFormat("allPoints[ %d x: %f \n y: %f \n", 1, allPoints[0].x, allPoints[0].y), 600, 20 ,10, RED);
      DrawText(TextFormat("allPoints[ %d x: %f \n y: %f \n", 2, allPoints[1].x, allPoints[1].y), 600, 40 ,10, RED);
      DrawText(TextFormat("allPoints[ %d x: %f \n y: %f \n", 3, allPoints[2].x, allPoints[2].y), 600, 60 ,10, RED);
      DrawText(TextFormat("allPoints[ %d x: %f \n y: %f \n", 4, allPoints[3].x, allPoints[3].y), 600, 80 ,10, RED);
      DrawText(TextFormat("allPoints[ %d x: %f \n y: %f \n", 5, allPoints[4].x, allPoints[4].y), 600, 100 ,10, RED);
      DrawText(TextFormat("allPoints[ %d x: %f \n y: %f \n", 6, allPoints[5].x, allPoints[5].y), 600, 120 ,10, RED);
      DrawText(TextFormat("allPoints[ %d x: %f \n y: %f \n", 7, allPoints[6].x, allPoints[6].y), 600, 140 ,10, RED);
      DrawText(TextFormat("allPoints[ %d x: %f \n y: %f \n", 8, allPoints[7].x, allPoints[7].y), 600, 160 ,10, RED);
      Vector2 points[3] =  {allPoints[0], allPoints[1], allPoints[2]};
      Vector2 points2[3] = {allPoints[2], allPoints[3], allPoints[4]};
      Vector2 points3[3] = {allPoints[4], allPoints[5], allPoints[6]};
      Vector2 points4[3] = {allPoints[6], allPoints[7], allPoints[0]};

      curve1 = calloc(SAMPLES, sizeof(Vector2));
      curve2 = calloc(SAMPLES, sizeof(Vector2));
      curve3 = calloc(SAMPLES, sizeof(Vector2));
      curve4 = calloc(SAMPLES, sizeof(Vector2));

      getPoints(points, curve1);

      getPoints(points2, curve2);
      getPoints(points3, curve3);
      getPoints(points4, curve4);



      BeginDrawing();
      ClearBackground(RAYWHITE);



      drawPoints(allPoints);
      reverseArray(curve3);
      reverseArray(curve4);

      //use this exact configuration unless the function changes ok
      createBilinearSurface(allPoints[0], allPoints[2], allPoints[6], allPoints[4]);


      createRuledSurface(curve1, curve2, curve3, curve4);
      blendSurface();

      free(curve1);
      free(curve2);
      free(curve3);
      free(curve4);
      EndDrawing();
    }
    CloseWindow();
    return 0;
}



