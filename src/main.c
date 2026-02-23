


#define SAMPLES 22 

#include "everything.c"



int main(void)
{

  
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");
  SetTargetFPS(60);              
  Vector2 point1 = {100, 100};
  Vector2 point2 = {200, 10};
  Vector2 point3 = {200, 20};
  Vector2 point4 = {(300 + 300), 150};
  Vector2 point5 = {300, 200};
  Vector2 point6 = {(300+100)/2, 400};
  Vector2 point7 = {100, 200};
  Vector2 point8 = {20, 150};
  Vector2 *curve1;
  Vector2 *curve2;
  Vector2 *curve3;
  Vector2 *curve4;

  
  while (!WindowShouldClose())
    {
      
      DrawFPS(20, 20);
      Vector2 points[3] = { point1, point2, point3};
      Vector2 points2[3] = {point3, point4, point5};
      Vector2 points3[3] = {point5, point6, point7}; 
      Vector2 points4[3] = {point7, point8, point1};
      Vector2 mouse = GetMousePosition();
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
      drawPoints(allPoints);
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

     
      //use this exact configuration unless the function changes ok 
      createBilinearSurface(curve3[0], curve4[0], curve2[0], curve1[0]);

      
      
      
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



