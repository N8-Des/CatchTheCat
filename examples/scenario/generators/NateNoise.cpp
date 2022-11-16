#include <random>
#include "NateNoise.h"
#include <cmath>
#include <iostream>

std::string NateNoise::GetName() 
{    
    return "Nate Noise"; 
}

struct GradientSegment
{
  float percent;
  Color32 color;
};
//create a gradient to supplement the existing gradient.
Color32 rgb(float ratio) 
{
    ratio /= 100;
    // kinda big by default so Im gonna turn it into regions.
    GradientSegment colors[5];
    colors[0].color = Color32(7, 60, 136);
    colors[0].percent = 0;

    colors[1].color = Color32(11, 70, 200);
    colors[1].percent = 0.2;

    colors[2].color = Color32(220, 198, 0);
    colors[2].percent = 0.4;

    colors[3].color = Color32(45, 200, 80);
    colors[3].percent = 0.6;

    colors[4].color = Color32(20, 110, 30);
    colors[4].percent = 1;
    
    Color32 finalColor;
    for (int i = 0; i < 5; i++)
    {
        if (colors[i].percent <= ratio && colors[i + 1].percent >= ratio)
        {
            float lerpTime = ratio / colors[i + 1].percent;
            finalColor.r = colors[i].color.r + lerpTime * (colors[i + 1].color.r - colors[i].color.r);
            finalColor.g = colors[i].color.g + lerpTime * (colors[i + 1].color.g - colors[i].color.g);
            finalColor.b = colors[i].color.b + lerpTime * (colors[i + 1].color.b - colors[i].color.b);
            return finalColor;
        }
    }
    return finalColor;
}

std::vector<Color32> NateNoise::Generate(int sideSize, float displacement) 
{
  int seed = 136;
  std::vector<int> vect;
  std::vector<Color32> colorReturn;
  vect.resize(256);
  for (int i = 0; i < 256; i++) {
    vect[i] = i;
  }
  siv::BasicPerlinNoise<float> noise;
  //NoiseGeneration noise;
  // hey its a random engine, learned about this and figured i would give it a shot.

  std::default_random_engine engine(seed);

  //hey a shuffle funciton. Handy. 
  std::shuffle(vect.begin(), vect.end(), engine);
  vect.insert(vect.end(), vect.begin(), vect.end());


  //now use the noise to generate the image.
  for (int l = 0; l < sideSize; l++) {
    for (int c = 0; c < sideSize; c++) 
    {
      //generate the noise!
      float n = (abs(noise.octave3D(c / 50.0, l / 50.0, displacement, 3)) - abs(noise.octave3D(c / 136.0, l / 136.0, displacement, 10))) * 255;
            
      //square the gradient!
      float x = 2 * (float)l / ((float)sideSize) - 1;
      float y = 2 * (float)c / ((float)sideSize) - 1;
      float d = 1 - ((1 - (x * x)) * (1 - (y * y)));
      n = abs(n + ((1 - d) * 255)) / 4;
      //change colors!
      Color32 col;
      col.r = n;
      col.g = n;
      col.b = n;
      col.a = n;
      col = rgb(n);
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


