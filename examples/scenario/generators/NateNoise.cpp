#include <random>
#include "NateNoise.h"
#include <cmath>
#include <iostream>

std::string NateNoise::GetName() 
{    
    return "Nate Noise"; 
}

//create a gradient to supplement the existing gradient.


std::vector<Color32> NateNoise::Generate(int sideSize, float displacement) {
  int seed = 1501;
  std::vector<int> vect;
  std::vector<Color32> colorReturn;
  vect.resize(256);
  for (int i = 0; i < 256; i++) {
    vect[i] = i;
  }
  //siv::BasicPerlinNoise<float> noise;
  NoiseGeneration noise;
  // hey its a random engine, learned about this and figured i would give it a shot.

  std::default_random_engine engine(seed);

  // and heres why I found out about the shuffle function. Neato!
  std::shuffle(vect.begin(), vect.end(), engine);
  vect.insert(vect.end(), vect.begin(), vect.end());

  int pixelOn = 0;
  //now use the noise to generate the image.
  Color32 pastColor(0, 0, 0);
  for (int l = 0; l < sideSize; l++) {
    for (int c = 0; c < sideSize; c++) 
    {
      float x = (float)l / ((float)sideSize);
      float y = (float)c / ((float)sideSize);
      float n = abs(noise.noise(x * 10, y * 10, displacement, vect));

      // change colors!
      Color32 col;
      col.r = n * 255;
      col.g = n * 255;
      col.b = n * 255;
      if (col.r < 50) 
      {
        col.r = 10;
        col.g = 50;
        col.b = 200;
      } 
      else if (col.r < 75) 
      {
        col.r = 219;
        col.g = 219;
        col.b = 132;
      }else 
      {
        col.r = 113;
        col.g = 148;
        col.b = 96;
      }
      colorReturn.emplace_back(col);
      pixelOn++;
      pastColor = col;
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


