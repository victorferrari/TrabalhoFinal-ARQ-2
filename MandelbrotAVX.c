/*
Modified from: http://rosettacode.org/wiki/Mandelbrot_set#PPM_non_interactive
c program:
--------------------------------
1. draws Mandelbrot set for Fc(z)=z*z +c
using Mandelbrot algorithm ( boolean escape time )
-------------------------------         
2. technique of creating ppm file is  based on the code of Claudio Rocchini
http://en.wikipedia.org/wiki/Image:Color_complex_plot.jpg
create 24 bit color graphic file ,  portable pixmap file = PPM 
see http://en.wikipedia.org/wiki/Portable_pixmap
to see the file use external application ( graphic viewer)
*/

//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
	clock_t start, end1;
	double cpu_time_used;
        /* screen ( integer) coordinate */
        int iX,iY;
        const int iXmax = 16384; 
        const int iYmax = 16384;
        /* world ( double) coordinate = parameter plane*/
        float Cx;
	float Cy;
        const float CxMin=-2.5;
        const float CxMax=1.5;
        const float CyMin=-2.0;
        const float CyMax=2.0;
        /* */
        float PixelWidth =(CxMax-CxMin)/iXmax;
        float PixelHeight =(CyMax-CyMin)/iYmax;
        /* color component ( R or G or B) is coded from 0 to 255 */
        /* it is 24 bit color RGB file */
        const int MaxColorComponentValue=255; 
        FILE * fp;
        char *filename="mandelbrot.ppm";
        static unsigned char color[24];
        /* Z=Zx+Zy*i  ;   Z0 = 0 */
        float Zx, Zy;
        float Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
        /*  */
        int Iteration;
        const int IterationMax=256;
	static unsigned char u[3];
        /* bail-out value , radius of circle ;  */
        const float EscapeRadius=2;
        float ER2=EscapeRadius*EscapeRadius;
        /*create new file,give it a name and open it in binary mode  */
        fp= fopen(filename,"wb"); /* b -  binary mode */
        /*write ASCII header to the file*/
        fprintf(fp,"P6\n %d\n %d\n %d\n",iXmax,iYmax,MaxColorComponentValue);
        /* compute and write image data bytes to the file*/

	start = clock();
        for(iY=0;iY<iYmax;iY++)
        {
             Cy=CyMin + iY*PixelHeight;
             if (fabs(Cy)< PixelHeight/2) 
			 Cy=0.0; /* Main antenna */
             for(iX=0;iX<iXmax;iX+=8)
             {         
		Cx=CxMin + iX*PixelWidth;
                /* initial value of orbit = critical point Z= 0 */
                Zx=0.0;
                Zy=0.0;
				
                Zx2=Zx*Zx;
                Zy2=Zy*Zy;  
                /* */
                for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
                {			    
					Zy=2*Zx*Zy + Cy;
					Zx=Zx2-Zy2 +Cx;
					Zx2=Zx*Zx;
					Zy2=Zy*Zy;		
                };
                /* compute  pixel color (24 bit = 3 bytes) */
                if (Iteration==IterationMax)
                { /*  interior of Mandelbrot set = black */
					__asm{
						mov ecx, 4
						xor ebx, ebx
						vpxor xmm0, xmm0, xmm0
					L1:
						vmovq color[ebx], xmm0
						add ebx, 6
						loop L1
					}
				}
                else 
                { /* exterior of Mandelbrot set = white */
					u[0]=((IterationMax-Iteration) % 8) * 63;  /* Red */
                    u[1]=((IterationMax-Iteration) % 4) * 127 ;  /* Green */ 
                    u[2]=((IterationMax-Iteration) % 2) * 255;  /* Blue */
					__asm{
						mov ecx, 4
						xor ebx, ebx
						vmovss xmm3, u
						vpsllq xmm1, xmm3, 24
						vpaddd xmm1, xmm1, xmm3
					L2:
						vmovq color[ebx], xmm1
						add ebx, 6
						loop L2
					}
				}; 
				/*write color to the file*/
                fwrite(color,1,24,fp);
		   }
		}
        end1 = clock();
        fclose(fp);
		cpu_time_used = ((double)(end1 - start)) / CLOCKS_PER_SEC;
		printf("time = %f seconds\n", cpu_time_used);
        return 0;
}
