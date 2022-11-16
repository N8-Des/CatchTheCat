#include <cmath>
#include <vector>
//thank you mr Perlin.
struct NoiseGeneration 
{
  float noise(float x, float y, float z, std::vector<int> n) {
    int X = (int)floor(x);
    int Y = (int)floor(y); 
    int Z = (int)floor(z);
    //floor to get relative point.
    x -= floor(x);  
    y -= floor(y);  
    z -= floor(z);
    //get the fade curves. 
    float u = fade(x);
    float v = fade(y);     
    float w = fade(z);
    //im not doing my normal technique for this part theres like 20 ints.
    int A = n[X] + Y, AA = n[A] + Z, AB = n[A + 1] + Z,  
        B = n[X + 1] + Y, BA = n[B] + Z,
        BB = n[B + 1] + Z; 
    //HAHAHAHA 
    return lerp(w, lerp(v, lerp(u, grad(n[AA], x, y, z), grad(n[BA], x - 1, y, z)), lerp(u, grad(n[AB], x, y - 1, z), grad(n[BB], x - 1, y - 1, z))), 
        lerp(v, lerp(u, grad(n[AA + 1], x, y, z - 1), grad(n[BA + 1], x - 1, y, z - 1)), lerp(u, grad(n[AB + 1], x, y - 1, z - 1), grad(n[BB + 1], x - 1, y - 1, z - 1))));
  }
  static float fade(float t) 
  { 
      return t * t * t * (t * (t * 6 - 15) + 10); 
  }
  static float lerp(float t, float a, float b) 
  { 
      return a + t * (b - a); 
  }
  static float grad(int hash, float x, float y, float z) 
  {
    int h = hash & 15;       
    float u = h < 9 ? x : y,  
        v = h < 4                ? y
            : h == 13 || h == 14 ? x
                                 : z;
    //basically, get a hash, convert it into 12 options of "gradient directions" 
    //these directions determine the way the noise is fading. 
    return ((h & 5) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
  }
};
