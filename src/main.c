


#define SAMPLES 30 

#include "everything.c"



int main(void)
{

  
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");
  SetTargetFPS(60);              
  Point point1 = {{100, 100}, false};
  Point point2 = {200, 100};
  Point point3 = {300, 100};
  Point point4 = {300, 150};
  Point point5 = {300, 200};
  Point point6 = {(300+100)/2, 200};
  Point point7 = {100, 200};
  Point point8 = {100, 150};
  Vector2 *curve1;
  Vector2 *curve2;
  Vector2 *curve3;
  Vector2 *curve4;
  Point allPoints[8] = {
        point1,
        point2,
        point3,
        point4,
        point5,
        point6,
        point7,
        point8
      };


  
  initPatch();

  
  while (!WindowShouldClose())
    {
      
      
      Vector2 mouse = GetMousePosition();
      Vector2 mouse2 = GetMouseDelta();

      checkPositions(mouse, allPoints);
      Vector2 points[3] =  {allPoints[0].p, allPoints[1].p, allPoints[2].p};
      Vector2 points2[3] = {allPoints[2].p, allPoints[3].p, allPoints[4].p};
      Vector2 points3[3] = {allPoints[4].p, allPoints[5].p, allPoints[6].p};
      Vector2 points4[3] = {allPoints[6].p, allPoints[7].p, allPoints[0].p};

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
      DrawFPS(22,22);
      reverseArray(curve3);
      reverseArray(curve4);

      //use this exact configuration unless the function changes ok
      createBilinearSurface(allPoints[0].p, allPoints[2].p, allPoints[6].p, allPoints[4].p);


      createRuledSurface(curve1, curve2, curve3, curve4);
      blendSurface();

      
      DrawPatch();
      
      drawPoints(allPoints);
      free(curve1);
      free(curve2);
      free(curve3);
      free(curve4);
      EndDrawing();
    }
  CloseWindow();
  return 0;
}



