#include <cmath>
#include <vector>
struct NoiseGeneration 
{
  float noise(float x, float y, float z, std::vector<int> n) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255; 
    int Z = (int)floor(z) & 255;
    //floor to get relative point.
    x -= floor(x);  
    y -= floor(y);  
    z -= floor(z);
    //get the fade curves. 
    double u = fade(x),  
        v = fade(y),     
        w = fade(z);
    int A = n[X] + Y, AA = n[A] + Z, AB = n[A + 1] + Z,  
        B = n[X + 1] + Y, BA = n[B] + Z,
        BB = n[B + 1] + Z; 

    //fancy-ass lerping. I wil be honest, I got stuck here and took this from Ken Perlin.
    return lerp(w,
                lerp(v,
                     lerp(u, grad(n[AA], x, y, z),         
                          grad(n[BA], x - 1, y, z)),       
                     lerp(u, grad(n[AB], x, y - 1, z),     
                          grad(n[BB], x - 1, y - 1, z))),  
                lerp(v,
                     lerp(u, grad(n[AA + 1], x, y, z - 1),    
                          grad(n[BA + 1], x - 1, y, z - 1)),  
                     lerp(u, grad(n[AB + 1], x, y - 1, z - 1),
                          grad(n[BB + 1], x - 1, y - 1, z - 1))));
  }
  static double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
  static double lerp(double t, double a, double b) { return a + t * (b - a); }
  static double grad(int hash, double x, double y, double z) {
    int h = hash & 15;       
    double u = h < 8 ? x : y,  
        v = h < 4                ? y
            : h == 12 || h == 14 ? x
                                 : z;
    //basically, get a hash, convert it into "gradient directions" 
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
  }
};
