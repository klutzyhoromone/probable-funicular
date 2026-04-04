
#include "raylib.h"

#include "rlgl.h"
#define POINTCOUNT 8 
#define SAMPLES 30 
#define RADIUS 10.0

#define BAROON     CLITERAL(Color){ 190, 33, 55, 125}     // Maroon
Texture2D texture;


void initPatch(){
  
  texture = LoadTexture("resources/wall.png");
}
/* GLuint vao = 0; */
/* GLuint vbo = 0; */
/* RenderTexture debugTexture; */
/* void initPatch(){ */
/*   glGenVertexArrays(1, &vao); */
/*   glBindVertexArray(vao); */
/*   glGenBuffers(1, &vbo); */
/*   glBindBuffer(GL_ARRAY_BUFFER, vbo); */
/* } */
int selectionIndex = -1;
Vector2 midPoint(Vector2 p1, Vector2 p2);
typedef struct Point {
  Vector2 p;
  bool hasMoved;
  bool movePoint;
}Point;


/* void DrawCircleT(Vector2 pos,  Color color){ */
/*   DrawTexture(debugTexture.texture, */
/* 	      (pos.x - debugTexture.texture.width*0.5f), */
/* 	      (pos.y - debugTexture.texture.height*0.5f), */
/* 	      color); */

/* } */


Vector2 interpPoints[SAMPLES * SAMPLES];
Vector2 interpPoints2[SAMPLES * SAMPLES];
Vector2 bilinearPoint[SAMPLES * SAMPLES];
Vector2 blendedPoints[SAMPLES * SAMPLES];
void getPoints(Vector2 *points,Vector2 *out){
  for(int i = 0; i < SAMPLES; i++){\
    float t = (float)i / (SAMPLES - 1);
    out[i] = GetSplinePointBezierQuad(points[0], points[1], points[2], t); 
    
    /* DrawCircleV(out[i], 5, BLACK); */

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

void drawPoints(Point *allPoints){
  for(int i = 0; i < POINTCOUNT; i++){ 
    DrawCircleV(allPoints[i].p, RADIUS, BAROON);

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
      bilinearPoint[(SAMPLES * i) + j]= Vec2BiLerp( s,  t,  point1,  point2,  point3,  point4);
      /* DrawCircleV(bilinearPoint[i][j], 3, BLUE); */
    }
  }
}





void createRuledSurface(Vector2 *curve1, Vector2 *curve2, Vector2 *curve3, Vector2 *curve4 ){

  for(int i = 0; i < SAMPLES; i++){
    float s = (float) i/(SAMPLES-1);
    for(int j = 0; j < SAMPLES;j++){
      
      float t = (float) j/(SAMPLES-1);
      interpPoints[(SAMPLES *i ) + j] = Vec2Lerp(curve1[i], curve3[i], t);
      interpPoints2[(SAMPLES * i) + j] = Vec2Lerp(curve2[j], curve4[j],s);
      /* DrawCircleV(interpPoints[(SAMPLES * i) +j], 2, RED); */

      DrawCircleV(interpPoints2[(SAMPLES * i) +j], 2, BLANK);
    }
  }


  
}



void blendSurface(){
  for(int i = 0; i < SAMPLES; i++){
    for(int j = 0; j < SAMPLES; j++){
      Vector2 blendedpoint;
      blendedpoint.x = interpPoints2[(SAMPLES * i) +j].x + interpPoints[(SAMPLES * i) +j].x - bilinearPoint[(SAMPLES * i) +j].x;
      blendedpoint.y = interpPoints2[(SAMPLES * i) +j].y + interpPoints[(SAMPLES * i) +j].y - bilinearPoint[(SAMPLES * i) +j].y;
      blendedPoints[(SAMPLES * i) +j] = blendedpoint;
      /* DrawCircleV(blendedPoints[(SAMPLES * i) +j], 2, MAGENTA); */
    }
    


  }
  
}



void checkPositions(Vector2 mouse, Point positions[8]){
  
  if(selectionIndex == -1){
    for (int i = 0; i < 8; i++) {
      if (CheckCollisionPointCircle(mouse, positions[i].p, RADIUS * 2)) {
	selectionIndex = i;
	break;
      }
    }
  }
  
  
  
  if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && selectionIndex != -1 && selectionIndex != 6 && selectionIndex != 0 && selectionIndex % 2 == 0){

    if(!positions[selectionIndex + 1].hasMoved) positions[selectionIndex + 1].p = midPoint(positions[selectionIndex].p, positions[selectionIndex + 2].p);
    
    if(!positions[selectionIndex - 1].hasMoved) positions[selectionIndex - 1].p = midPoint(positions[selectionIndex].p, positions[selectionIndex - 2].p);
    positions[selectionIndex].p = mouse;

  }
  // midpoints
  if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && selectionIndex != -1 && selectionIndex % 2 != 0){
    
    positions[selectionIndex].p = mouse;
    positions[selectionIndex].hasMoved = true;
  }


  //edge cases
  if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && selectionIndex == 6){
    positions[6].p = mouse;
    
    if(!positions[selectionIndex + 1].hasMoved) positions[selectionIndex + 1].p = midPoint(positions[selectionIndex].p, positions[0].p);
    
    if(!positions[selectionIndex - 1].hasMoved) positions[selectionIndex - 1].p = midPoint(positions[selectionIndex].p, positions[selectionIndex - 2].p);
  }

  if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && selectionIndex == 0){
    
    positions[0].p = mouse;
    
    if(!positions[selectionIndex + 1].hasMoved) positions[selectionIndex + 1].p = midPoint(positions[selectionIndex].p, positions[selectionIndex + 2].p);
    
    if(!positions[7].hasMoved) positions[7].p = midPoint(positions[selectionIndex].p, positions[6].p);
  }

  if(IsMouseButtonUp(MOUSE_LEFT_BUTTON)){
    selectionIndex = -1;
  }
  
}

Vector2 midPoint(Vector2 p1, Vector2 p2){
  Vector2 result =  {((p1.x + p2.x) /2),((p1.y + p2.y) / 2) };
  return result;
}
void DrawPatch(){
  
Vector2 uvs[SAMPLES * SAMPLES];

 for (int i = 0; i < SAMPLES; i++) {
   
   float s =  1 - (float)i / (SAMPLES - 1);
   for (int j = 0; j < SAMPLES; j++) {
     
     float t = (float)j / (SAMPLES - 1);
     
     uvs[i * SAMPLES + j] = (Vector2){ s, t };
   }
 }
 
 
 
 rlSetTexture(texture.id);
 rlBegin(RL_TRIANGLES);
 
 for (int i = 0; i < SAMPLES - 1; i++) {
   for (int j = 0; j < SAMPLES - 1; j++) {
     //fixes weird tint
     rlColor4ub(255, 255, 255, 255);
      int i0 = i * SAMPLES + j;
      int i1 = i * SAMPLES + (j + 1);
      int i2 = (i + 1) * SAMPLES + j;
      int i3 = (i + 1) * SAMPLES + (j + 1);
      
      // Triangle 1
      rlTexCoord2f(uvs[i0].x, uvs[i0].y);
      rlVertex2f(blendedPoints[i0].x, blendedPoints[i0].y);
      
      rlTexCoord2f(uvs[i2].x, uvs[i2].y);
      rlVertex2f(blendedPoints[i2].x, blendedPoints[i2].y);
      
      rlTexCoord2f(uvs[i1].x, uvs[i1].y);
      rlVertex2f(blendedPoints[i1].x, blendedPoints[i1].y);
      
      // Triangle 2
      rlTexCoord2f(uvs[i1].x, uvs[i1].y);
      rlVertex2f(blendedPoints[i1].x, blendedPoints[i1].y);
      
      rlTexCoord2f(uvs[i2].x, uvs[i2].y);
      rlVertex2f(blendedPoints[i2].x, blendedPoints[i2].y);
      
      rlTexCoord2f(uvs[i3].x, uvs[i3].y);
      rlVertex2f(blendedPoints[i3].x, blendedPoints[i3].y);
   }
 }
 
 rlEnd();
}

