#include "raylib.h"

#define POINTCOUNT 8 
#define SAMPLES 22 
#define RADIUS 10.0


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



Vector2 createRuledSurfaceSection(Vector2 point1, Vector2 point2){
  Vector2 arr;

  for(int i = 0; i < SAMPLES; i++){

    float t = (float) i/(SAMPLES-1);
    arr = Vec2Lerp(point1, point2,  t);
    //uncomment for debug mode 
    DrawCircleV(arr, 1, RED);
  }

  return arr;
  
}


void createRuledSurface(Vector2 *curve1, Vector2 *curve2, Vector2 *curve3, Vector2 *curve4 ){

  for(int i = 0; i < SAMPLES-1; i++){
    for(int j = 0; j < SAMPLES-1;j++){
      interpPoints[i][j] = createRuledSurfaceSection(curve1[i], curve3[(SAMPLES-1) - i]);
    }
  }

  for(int i = 0; i < SAMPLES-1; i++){
    for(int j = 0; j < SAMPLES-1;j++){
      interpPoints2[i][j] = createRuledSurfaceSection(curve2[i], curve4[(SAMPLES-1) - i]);
    }
  }

  
}



void blendSurface(){
  for(int i = 0; i < SAMPLES; i++){
    for(int j = 0; j < SAMPLES; j++){
      Vector2 blendedpoint;
	blendedpoint.x = interpPoints[i][j].x + interpPoints2[i][j].x - bilinearPoint[i][j].x;
	blendedpoint.y = interpPoints[i][j].y + interpPoints2[i][j].y - bilinearPoint[i][j].y;
      blendedPoints[i][j] = blendedpoint;
      DrawCircleV(blendedPoints[i][j], 2, BLUE);
    }
  }

}
