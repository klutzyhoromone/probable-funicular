
#include "raylib.h"

#include "rlgl.h"
#define POINTCOUNT 8 
#define SAMPLES 30 
#define RADIUS 10.0
#define ISMOUSEBUTTONDOWN IsMouseButtonDown(MOUSE_LEFT_BUTTON)



void drawSurfaceMesh();
Vector2 midPoint(Vector2 p1, Vector2 p2);
typedef struct Point {
  Vector2 p;
  bool isMoved;

}Point;


Point magic = {
   {0,0},
   false
};

Vector2 interpPoints[SAMPLES][SAMPLES];
Vector2 interpPoints2[SAMPLES][SAMPLES];
Vector2 bilinearPoint[SAMPLES][SAMPLES];
Vector2 blendedPoints[SAMPLES][SAMPLES];
void getPoints(Vector2 *points,Vector2 *out){
  for(int i = 0; i < SAMPLES; i++){\
    float t = (float)i / (SAMPLES - 1);
    out[i] = GetSplinePointBezierQuad(points[0], points[1], points[2], t); 
    
    DrawCircleV(out[i], 5, BLACK);

  }
}

void reverseArray(Vector2 *out){
  Vector2 rArray[SAMPLES];
  for(int i = 0; i < SAMPLES; i++){
    rArray[i] = out[(SAMPLES -1)  - i];
    
    /* DrawCircleV(rArray[i],10, MAGENTA); */
  }
  
  for(int i = 0; i < SAMPLES; i++){
    out[i] = rArray[i];
    
    /* DrawCircleV(rArray[i],10, MAGENTA); */
  }
}

void drawPoints(Vector2 *allPoints){
  for(int i = 0; i < POINTCOUNT; i++){ 
    DrawCircleV(allPoints[i], RADIUS, MAROON);

  }
}

Vector2 Vec2Lerp(Vector2 point1, Vector2 point2, float t){
  Vector2 result;
  result.x = point1.x + (point2.x - point1.x) * t; 
  result.y = point1.y + (point2.y - point1.y) * t;
  
  return result;
}


Vector2 Vec2BiLerp(float s, float t, Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4 ){
  Vector2 result;
  result.x = (point1.x * ((1 - s) * (1 - t)))
    + (point2.x * (s*(1-t)))
    + (point3.x * ((1 - s) * t))
    + (point4.x*(s*t)); 
  result.y = (point1.y * ((1 - s) * (1 - t)))
    + (point2.y * (s*(1-t)))
    + (point3.y * ((1 - s) * t))
    + (point4.y*(s*t));
  return result;
}


void createBilinearSurface(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4){
  for(int i = 0; i < SAMPLES; i++){
    
    float s = (float) i/(SAMPLES-1);
    
    for(int j=0; j < SAMPLES; j++){
      
      float t = (float) j/(SAMPLES-1);
      bilinearPoint[i][j]= Vec2BiLerp( s,  t,  point1,  point2,  point3,  point4);
      /* DrawCircleV(bilinearPoint[i][j], 3, BLUE); */
    }
  }
}





void createRuledSurface(Vector2 *curve1, Vector2 *curve2, Vector2 *curve3, Vector2 *curve4 ){

  for(int i = 0; i < SAMPLES; i++){
    float s = (float) i/(SAMPLES-1);
    for(int j = 0; j < SAMPLES;j++){
      
      float t = (float) j/(SAMPLES-1);
      interpPoints[i][j] = Vec2Lerp(curve1[i], curve3[i], t);
      interpPoints2[i][j] = Vec2Lerp(curve2[j], curve4[j],s);
      /* DrawCircleV(interpPoints[i][j], 2, RED); */

      /* DrawCircleV(interpPoints2[i][j], 2, MAGENTA); */
    }
  }


  
}



void blendSurface(){
  for(int i = 0; i < SAMPLES; i++){
    for(int j = 0; j < SAMPLES; j++){
      Vector2 blendedpoint;
	blendedpoint.x = interpPoints2[i][j].x + interpPoints[i][j].x - bilinearPoint[i][j].x;
	blendedpoint.y = interpPoints2[i][j].y + interpPoints[i][j].y - bilinearPoint[i][j].y;
      blendedPoints[i][j] = blendedpoint;
    }
  }
}



void checkPositions(Vector2 mouse, Vector2 positions[8]){
  for(int i = 0; i < 8; i++){

    if(CheckCollisionPointCircle(mouse, positions[i], RADIUS * 2) && ISMOUSEBUTTONDOWN  ){
      if( (i + 1) % 2 != 0 ){
        positions[i] = mouse;
        if(i == 0){
          positions[7] = midPoint(positions[6], positions[i]);
          positions[i+1] = midPoint(positions[i + 2], positions[i]);
	  DrawText(TextFormat("midpoints: i: %d \n i + 1: %d \n i + 2: %d \n", 7, i + 1, i + 2), 20, 20, 20, RED);
        }
	else if(i == 6){
          positions[i-1] = midPoint(positions[i - 2], positions[i]);
          positions[i+1] = midPoint(positions[0], positions[i]);
	  
	  DrawText(TextFormat("midpoints: i: %d \n i + 1: %d \n i + 2: %d \n", i, i + 1, i + 2), 20, 20, 20, RED);

	}
        else{
	  positions[i-1] = midPoint(positions[i - 2], positions[i]);
          positions[i+1] = midPoint(positions[i + 2], positions[i]);
	  
	  DrawText(TextFormat("midpoints: i: %d \n i + 1: %d \n i + 2: %d \n", i, i + 1, i + 2), 20, 20, 20, RED);

        }
      }

    }

  }
}

Vector2 midPoint(Vector2 p1, Vector2 p2){
  Vector2 result =  {((p1.x + p2.x) /2),((p1.y + p2.y) / 2) };
  return result;
}

GLuint vao = 0;
GLuint vbo = 0;
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);
glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, (SAMPLES * SAMPLES) * sizeof(Vector2) , particles, GL_STATIC_DRAW);

