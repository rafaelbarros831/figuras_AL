# figuras_AL

Projeto base em C++20 com SFML 3.1 para experimentar figuras geométricas.

## Estrutura

```text
projeto_configurado/
|- include/                 # Interfaces das classes
|  `- App.hpp
|- src/                     # Implementações
|  `- App.cpp
|- projeto_configurado.cpp  # Ponto de entrada (main)
`- projeto_configurado.vcxproj
```

## Fluxo da aplicação

`App::run()` executa o ciclo principal e separa as responsabilidades em:

- `processEvents()`: eventos da janela;
- `update()`: regras e estado da aplicação;
- `render()`: desenho na tela.

O projeto está configurado para procurar headers em `include/` e usa SFML instalado em `C:\SFML-3.1.0`.
