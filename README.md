# Trabalho de Álgebra Linear - Gabriel

Projeto de figuras geométricas e transformações lineares com matrizes, desenvolvido em **C++20 com SFML** e com uma **versão Web interativa em HTML5 Canvas**.

---

## 1. Como usar a Versão Web

Basta abrir a pasta `versao_web/` e dar dois cliques em [index.html](file:///c:/Users/gabri/OneDrive/Documentos/figuras_AL-gabriel_trbl/versao_web/index.html) para abrir no navegador.

### O que você pode fazer na Web:
- **Ligar e desligar figuras:** botões para mostrar ou esconder o Quadrado, Retângulo, Triângulo, Círculo e a Grade de Quadrados na tela.
- **Digitar sua própria matriz (2x2):** você pode preencher os valores de `a`, `b`, `c` e `d` e clicar no botão **"Aplicar Esta Matriz"** para ver a transformação acontecer na figura na hora.
- **Presets rápidos:** botões de Identidade, Reflexão em X, Reflexão em Y e Cisalhamento.
- **Mover e rotacionar:** sliders para rotação e escala, botões de movimento e opção de arrastar a figura diretamente com o mouse no desenho.
- **Espaço 3D (Cubo):** aba para visualizar o cubo 3D girando nos eixos X, Y e Z ou em auto-giro contínuo.

---

## 2. Como usar o Programa C++ (SFML)

O programa abre com uma janela contendo o painel de controle à esquerda e a área de desenho à direita:

- **Ligar/Desligar e Selecionar Figuras:** clique nos botões `[X] Quadrado`, `[X] Retângulo`, `[X] Triângulo`, `[X] Círculo` e `[X] Grade` para escolher quais quer na tela e qual delas recebe as transformações.
- **Digitar a Matriz no Painel:** clique nas caixas `a:`, `b:`, `c:`, `d:` para focar e digite os números pelo teclado, depois clique em **"✔ Aplicar Matriz"** (ou aperte Enter).
- **Digitar no Console:** se preferir, clique no botão **"Digitar no Console"** e informe os 4 valores no terminal (`std::cin >> a >> b >> c >> d`).
- **Transformações Rápidas:** botões para escala (+10% / -10%), rotação (+15° / -15°), reflexão em X, reflexão em Y e reflexão na origem.
- **Mover as Figuras:** use o D-Pad do painel, as setas do teclado ou clique e arraste com o mouse no desenho.
- **Aba 3D (Cubo):** controle o cubo com rotações em X, Y, Z, escala 3D e botão de auto-giro.

### Atalhos do Teclado:
- `Tab`: alterna entre tela 2D e tela 3D do cubo.
- `1` a `5`: seleciona rapidamente qual figura está ativa.
- `+` / `-`: aumenta ou diminui a escala.
- `,` / `.`: gira em -15° ou +15°.
- `R` / `T`: reflexão em X ou Y.
- `W`, `S`, `A`, `D`, `Z`, `X`: rotacionam o cubo 3D nos eixos.
- `Setas`: movem a figura 2D.
- `Q`: reseta a figura ativa de volta ao padrão.
