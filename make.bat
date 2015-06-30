cl mandelbrot_sequencial.cpp
cl mandelbrot_simd_avx.cpp
cl mandelbrot_simd_mmx.cpp

for /f %%f in ('dir /b in\') do mandelbrot_sequencial in\%%f out\%%f
for /f %%f in ('dir /b in\') do mandelbrot_simd_avx in\%%f out\SIMD_%%f
for /f %%f in ('dir /b in\') do mandelbrot_simd_mmx in\%%f out\SIMD_%%f

mandelbrot_sequencial
mandelbrot_simd_avx
mandelbrot_simd_mmx
pause
