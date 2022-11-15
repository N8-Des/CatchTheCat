#include <random>
#include "NateNoise.h"
#include <cmath>

std::string NateNoise::GetName() 
{    
    return "Nate Noise"; 
}

//create a gradient to supplement the existing gradient.
uint32_t rgb(double ratio, int color) 
{
    //kinda big by default so Im gonna turn it into regions. 
  int normalized = int(ratio * 256 * 6);
  int region = normalized / 256;
  int x = normalized % 256;
  //this is *basically* a color ramp from Blender! My specialty!
  int r = 0, g = 0, b = 0;
  switch (region) {
    case 0:
      r = 0;
      g = 20;
      b = 210;
      g += x;
      break;
    case 1:
      r = 237;
      g = 225;
      b = 161;
      r -= x;
      break;
    case 2:
      r = 148;
      g = 109;
      b = 80;
      b += x;
      break;
    case 3:
      r = 30;
      g = 200;
      b = 10;
      g -= x;
      break;
    case 4:
      r = 35;
      g = 180;
      b = 10;
      r += x;
      break;
    case 5:
      r = 50;
      g = 222;
      b = 0;
      b -= x;
      break;
  }
  if (color == 0) 
  {
    return r;
  }
  if (color == 1) 
  {
    return g;
  }
  return b;
}

std::vector<Color32> NateNoise::Generate(int sideSize, float displacement) {
  int seed = 1501;
  std::vector<int> vect;
  std::vector<Color32> colorReturn;
  vect.resize(256);
  for (int i = 0; i < 256; i++) {
    vect[i] = i;
  }
  siv::BasicPerlinNoise<float> noise;
  // hey its a random engine, learned about this and figured i would give it a shot.

  std::default_random_engine engine(seed);

  // and heres why I found out about the shuffle function. Neato!
  std::shuffle(vect.begin(), vect.end(), engine);
  vect.insert(vect.end(), vect.begin(), vect.end());

  int pixelOn = 0;
  //now use the noise to generate the image.
  for (int l = 0; l < sideSize; l++) {
    for (int c = 0; c < sideSize; c++) 
    {
      float x = (float)l / ((float)sideSize);
      float y = (float)c / ((float)sideSize);
      float n = abs(noise.octave3D(x * 5, y * 5, displacement, 1));

      Color32 col;
      col.r = rgb(n, 0);
      col.g = rgb(n, 1);
      col.b = rgb(n, 2);
      //change colors!


      colorReturn.emplace_back(col);
      pixelOn++;
    }
  }
  return colorReturn;
}


