<h2>CONJUNTO DE MANDELBROT</h2></br>
<hr>
<h4>Definição</h4>

O conjunto de Mandelbrot, em sua representação gráfica no espaço contínuo, pode ser dividido em um
conjunto infinito de figuras pretas, sendo a maior delas um cardióide localizado ao centro do plano
complexo. Existe uma infinidade de quase-círculos que tangenciam o cardióide e variam de tamanho com
raio tendendo assintoticamente a zero. Cada um desses círculos tem seu próprio conjunto infinito de
pequenos círculos cujos raios também tendem assintoticamente a zero. Esse processo se repete
infinitamente, gerando uma figura fractal.

fonte(http://www.vision.ime.usp.br/~pmiranda/mac110_1s14/EPs/ep02/ep02.pdf).

<img src="http://i.imgur.com/HCyni73.png"></img>

<hr>
<h4>Versão SIMD (MMX -- SSE)</h4>

O algoritmo utilizado como base foi disponibilizado pelo professor.Foram acrescentado 2 trechos de código Inline/Assembly, especicamente, no If e Else do segundo laço. Com uso de instruções SIMD (MMX -- SSE) foi possível realizar o cáculo para 8 pixels por vez, enquanto que no sequncial o cálculo é feito para 1 pixel por vez. Com isso a melhora de desempenho é muito grande, em média o ganho foi de 72%.

<img src="http://i.imgur.com/t027N6f.png"></img>

<hr>
<h4>Versão SIMD (AVX)</h4>

Não pode ser feita muita mudança que pudesse representar uma ganho expressivo. O modelo do processador utilizado é que de fato possibilitou ganho de desempenho. Os testes realizados com esse processador utilizando SSE e AVX praticamente obtiveram o mesmo resultado. O ganho nesse caso, em média foi de 85%.

<img src="http://i.imgur.com/utifTtB.png"></img>

<hr>
<h4>Gráficos -- Testes de Desempenho</h4>

<img src="http://i.imgur.com/bxTvIS6.png"></img>

<img src="http://i.imgur.com/tykZF15.png"></img>

<img src="http://i.imgur.com/Ahi52ho.png"></img>

OBS: processador utilizado nos teste do sequencial e AVX: Intel(R) Core(TM) i5-4200U CPU @ 1.60GHz
<hr>
OBS: processador utilizado nos teste do MMX/SSE: 





