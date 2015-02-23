/* Convert HSL (hue, saturation, lightness) colors to RGB (red, green
 * blue).
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------------------------------------------------------------------------------------------- */
/*  hue2rgb */
/* ---------------------------------------------------------------------------------------------- */

/* CSS3 spec algorithm: http://www.w3.org/TR/2011/REC-css3-color-20110607/#hsl-color
 */
float hue2rgb( float m1, float m2, float hue )
{
   float retval;
   float h = hue;
   
   if (hue < 0.0)
      h = hue + 1.0;
   else if (hue > 1.0)
      h = hue - 1.0;
   else
      h = hue;

   if (h * 6.0 < 1.0)
      retval = m1 + (m2 - m1) * h * 6.0;
   else if (h * 2.0 < 1.0)
      retval = m2;
   else if (h * 3.0 < 2.0)
      retval = m1 + (m2 - m1) * (2.0 / 3.0 - h) * 6.0;
   else
      retval = m1;

   return retval;
}

/* ---------------------------------------------------------------------------------------------- */
/*  hsl2rgb */
/* ---------------------------------------------------------------------------------------------- */

/* All params in range [0.0..1.0]
 */
void hsl2rgb( float hue, float sat, float light, float *r, float *g, float *b)
{
   float m1, m2;
   
   if (light < 0.5)
      m2 = light * (sat + 1.0);
   else
      m2 = light + sat - light * sat;
   m1 = light * 2.0 - m2;
   *r = hue2rgb( m1, m2, hue + 1.0/3.0);
   *g = hue2rgb( m1, m2, hue);
   *b = hue2rgb( m1, m2, hue - 1.0/3.0);
}

/* hue in degrees (0-360), saturation and lightness in range [0.0..1.0].
 * Output r,g,b in range [0.0..1.0]
 */
void hsl2rgb_wikipedia( int hue, float sat, float light, float *r, float *g, float *b)
{
   // Algorithm from http://en.wikipedia.org/wiki/HSL_and_HSV#From_HSL

   float chroma;
   float hPrime;
   float x;
   float r1, g1, b1;
   float m;

   chroma = (1 - abs( 2 * light - 1)) * sat;
   hPrime = hue/60;
   float hPrimeMod2 = hPrime / 2 - 2; /* What the heck? modulus of a floating point number? */
   x = chroma * (1 - abs( hPrimeMod2 - 1));
   if (0 <= hPrime && hPrime < 1)
   {
      r1 = chroma;
      g1 = x;
      b1 = 0;
   }
   else if (1 <= hPrime && hPrime < 2)
   {
      r1 = x;
      g1 = chroma;
      b1 = 0;
   }
   else if (2 <= hPrime && hPrime < 3)
   {
      r1 = 0;
      g1 = chroma;
      b1 = x;
   }
   else if (3 <= hPrime && hPrime < 4)
   {
      r1 = 0;
      g1 = x;
      b1 = chroma;
   }
   else if (4 <= hPrime && hPrime < 5)
   {
      r1 = x;
      g1 = 0;
      b1 = chroma;
   }
   else if (5 <= hPrime && hPrime < 6)
   {
      r1 = chroma;
      g1 = 0;
      b1 = x;
   }
   else
   {
      r1 = g1 = b1 = 0;
   }

   m = light - chroma / 2.0;

   *r = r1 + m;
   *g = g1 + m;
   *b = b1 + m;
}


/* ---------------------------------------------------------------- */
/*  Main */
/* ---------------------------------------------------------------- */

/* Args: hue (0-360), saturation (0-1), lightness (0-1)
 */
int main(int argc, char **argv)
{
   int hue; 
   float sat, light;

   /* int i; */
   /* for (i = 0; i < argc; i++) */
   /*    printf( "argv[%d]: %s\n", i, argv[i]); */
   
   sscanf( argv[1], "%d", &hue);
   sscanf( argv[2], "%g", &sat);
   sscanf( argv[3], "%g", &light);
   
   printf( "Got hue %d, saturation %g, lightness %g\n", hue, sat, light);
   // printf( "1.0 + 2.0/3.0 = %d\n", (int) (1.0 + 2.0/3.0));
   
   float r,g,b;

   hsl2rgb( hue/360.0, sat, light, &r, &g, &b);

   printf( "Converted to (%5.3f, %5.3f, %5.3f)\n", r, g, b);
}
