#include <random>
#include "NateNoise.h"
#include <cmath>
#include <iostream>

std::string NateNoise::GetName() 
{    
    return "Nate Noise"; 
}

//create a gradient to supplement the existing gradient.


std::vector<Color32> NateNoise::Generate(int sideSize, float displacement) 
{
  int seed = 136;
  std::vector<int> vect;
  std::vector<Color32> colorReturn;
  vect.resize(256);
  for (int i = 0; i < 256; i++) {
    vect[i] = i;
  }

  NoiseGeneration noise;
  // hey its a random engine, learned about this and figured i would give it a shot.

  std::default_random_engine engine(seed);

  //hey a shuffle funciton. Handy. 
  std::shuffle(vect.begin(), vect.end(), engine);
  vect.insert(vect.end(), vect.begin(), vect.end());


  //now use the noise to generate the image.
  for (int l = 0; l < sideSize; l++) {
    for (int c = 0; c < sideSize; c++) 
    {
      float x = (float)l / ((float)sideSize);
      float y = (float)c / ((float)sideSize);

      //generate the noise!
      float n = abs(noise.noise(x * 33, y * 33, displacement, vect)) * 255 -
                abs(noise.noise(x * 55, y * 55, displacement, vect)) * 255;
      //square the gradient!
      float xd = 2 * (float)l / ((float)sideSize) - 1;
      float yd = 2 * (float)c / ((float)sideSize) - 1;
      float d = 1 - ((1 - (xd * xd)) * (1 - (yd * yd)));
      n = (n + ((1 - d) * 255)) / 2;
      // change colors!
      Color32 col;
      col.r = n;
      col.g = n;
      col.b = n;
      col.a = n;
      if (n < 39) 
      {
        col.r = 11;
        col.g = 70;
        col.b = 200;
      } 
      else if (n < 50)
      {
        col.r = 220;
        col.g = 198;
        col.b = 0;
      }else 
      {
        col.r = 45;
        col.g = 200;
        col.b = 80;
      }
      colorReturn.emplace_back(col);
    }

  }
  //attempted lerping. It didn't work. 
  /* for (int i = 0; i < colorReturn.size(); i++) 
  {
    Color32 lerpCol; 
    //right
    if (i - 1 < 0) 
    {
      lerpCol = colorReturn[i];
    }
    else 
    {
      lerpCol = colorReturn[i - 1];
    }
    colorReturn[i].r = abs(colorReturn[i].r - lerpCol.r) * 0.5 + colorReturn[i].r;
    colorReturn[i].g = abs(colorReturn[i].g - lerpCol.g) * 0.5 + colorReturn[i].g;
    colorReturn[i].b = abs(colorReturn[i].b - lerpCol.b) * 0.5 + colorReturn[i].b;
    //top
    if (i - sideSize < 0) 
    {
      lerpCol = colorReturn[i];
    } 
    else 
    {
      lerpCol = colorReturn[i - sideSize];
    }
    colorReturn[i].r = abs(colorReturn[i].r - lerpCol.r) * 0.5 + colorReturn[i].r;
    colorReturn[i].g = abs(colorReturn[i].g - lerpCol.g) * 0.5 + colorReturn[i].g;
    colorReturn[i].b = abs(colorReturn[i].b - lerpCol.b) * 0.5 + colorReturn[i].b;
    //left
    if (i + 1 >= vect.size()) 
    {
      lerpCol = colorReturn[i];
    }
    else 
    {
      lerpCol = colorReturn[i + 1];
    }
    colorReturn[i].r = abs(colorReturn[i].r - lerpCol.r) * 0.5 + colorReturn[i].r;
    colorReturn[i].g = abs(colorReturn[i].g - lerpCol.g) * 0.5 + colorReturn[i].g;
    colorReturn[i].b = abs(colorReturn[i].b - lerpCol.b) * 0.5 + colorReturn[i].b;
    //bottom
    if (i + sideSize >= vect.size()) 
    {
      lerpCol = colorReturn[i];
    } 
    else 
    {
      lerpCol = colorReturn[i + sideSize];
    }
    colorReturn[i].r = abs(colorReturn[i].r - lerpCol.r) * 0.5 + colorReturn[i].r;
    colorReturn[i].g = abs(colorReturn[i].g - lerpCol.g) * 0.5 + colorReturn[i].g;
    colorReturn[i].b = abs(colorReturn[i].b - lerpCol.b) * 0.5 + colorReturn[i].b;
  }*/
  return colorReturn;
}


