# 🔷 Transformação de Figuras

Sistema desenvolvido para a **Atividade 5 – Transformação de Figuras**, com foco no estudo e aplicação de **matrizes e transformações geométricas**.

O projeto tem como objetivo apresentar uma figura geométrica em uma aplicação gráfica e permitir que o usuário realize diferentes transformações utilizando **operações matriciais**.

---

## 📚 Sobre o projeto

O projeto está sendo desenvolvido em **C++**, utilizando a biblioteca **SFML 3.1** para a criação da aplicação gráfica.

A proposta é aplicar, de forma prática, os conceitos de **matrizes aplicadas à geometria**, permitindo transformar uma figura por meio de operações matemáticas.

As principais transformações previstas para o sistema são:

- 🔍 **Escala** — aumentar ou diminuir a figura;
- 🔄 **Rotação** — alterar a orientação da figura;
- ↔️ **Reflexão** — refletir a figura em relação a um eixo.

---

## 🎯 Objetivo

O principal objetivo do projeto é desenvolver uma aplicação capaz de demonstrar, de maneira visual e interativa, como as **operações matriciais podem ser utilizadas para realizar transformações geométricas**.

Com o sistema, será possível trabalhar conceitos como:

- Matrizes aplicadas à geometria;
- Transformação de escala;
- Rotação;
- Reflexão;
- Representação gráfica de figuras;
- Interação do usuário com a aplicação.

---

## ⚙️ Como funciona

O funcionamento previsto do sistema segue o seguinte fluxo:

```text
             ┌─────────────────────┐
             │  Iniciar aplicação  │
             └──────────┬──────────┘
                        │
                        ▼
             ┌─────────────────────┐
             │ Apresentar figura   │
             └──────────┬──────────┘
                        │
                        ▼
             ┌─────────────────────┐
             │ Usuário escolhe     │
             │ uma transformação   │
             └──────────┬──────────┘
                        │
             ┌──────────┼──────────┐
             ▼          ▼          ▼
          Escala     Rotação    Reflexão
             │          │          │
             └──────────┼──────────┘
                        ▼
             ┌─────────────────────┐
             │ Operação matricial  │
             └──────────┬──────────┘
                        │
                        ▼
             ┌─────────────────────┐
             │ Figura transformada │
             └─────────────────────┘
```

---

## 🔷 Transformações geométricas

### 🔍 Escala

Permite **aumentar ou diminuir o tamanho da figura**, aplicando fatores de escala aos seus pontos.

### 🔄 Rotação

Permite **girar a figura** em torno de um ponto, alterando sua orientação.

### ↔️ Reflexão

Permite **inverter a figura** em relação a um eixo, utilizando uma transformação matricial.

---

## 🖱️ Interação com o usuário

A aplicação deverá permitir que o usuário interaja com a figura e escolha as transformações que deseja aplicar.

O sistema será desenvolvido de forma que as alterações possam ser visualizadas graficamente na aplicação.

---

## 🧮 Operações matriciais

As transformações geométricas serão realizadas por meio de **operações com matrizes**.

As matrizes serão utilizadas para modificar as coordenadas dos pontos que formam a figura, permitindo alterar seu:

- 📏 Tamanho;
- 🔄 Ângulo;
- ↔️ Orientação.

Dessa forma, o projeto relaciona os conceitos matemáticos estudados com sua representação visual em uma aplicação gráfica.

---

## 🛠️ Tecnologias utilizadas

- 💻 **C++20**
- 🎨 **SFML 3.1**
- 🪟 **Visual Studio**
- 🐙 **GitHub**

---

## 📁 Estrutura do projeto

```text
figuras_AL/
│
├── projeto_configurado/
│   │
│   ├── include/
│   │   └── Interfaces e declarações
│   │
│   ├── src/
│   │   └── Implementações
│   │
│   ├── projeto_configurado.cpp
│   └── projeto_configurado.vcxproj
│
└── README.md
```

### 📂 Acesso às pastas

- 📁 [projeto_configurado](./projeto_configurado)
- 📁 [include](./projeto_configurado/include)
- 📁 [src](./projeto_configurado/src)

### 📄 Arquivos principais

- 📄 [projeto_configurado.cpp](./projeto_configurado/projeto_configurado.cpp)
- ⚙️ [projeto_configurado.vcxproj](./projeto_configurado/projeto_configurado.vcxproj)

---

## 🔄 Ciclo da aplicação

A aplicação utiliza uma estrutura dividida em etapas principais:

```text
Eventos
   ↓
processEvents()
   ↓
update()
   ↓
render()
   ↓
Exibição gráfica
```

### 🖱️ `processEvents()`

Responsável pelo processamento dos eventos da janela e das interações realizadas pelo usuário.

### 🔄 `update()`

Responsável pela atualização do estado da aplicação e das transformações realizadas na figura.

### 🎨 `render()`

Responsável pela representação gráfica da figura na janela.

---

## 📈 Desenvolvimento do projeto

```text
📐 Matrizes aplicadas à geometria
              ↓
🔷 Criação da figura
              ↓
🔍 Escala
              ↓
🔄 Rotação
              ↓
↔️ Reflexão
              ↓
🖱️ Interação com o usuário
              ↓
🧪 Testes
              ↓
🎓 Apresentação
```

🚧 **Projeto em desenvolvimento.**

---

## 🎓 Atividade acadêmica

**Atividade 5 – Transformação de Figuras**

**Tema:** Matrizes e transformações geométricas.

### Conteúdos

- Matrizes aplicadas à geometria;
- Rotação;
- Escala;
- Reflexão.

### Proposta

Desenvolver um programa que apresente uma figura simples, como um quadrado ou triângulo, permitindo ao usuário aplicar transformações geométricas utilizando operações matriciais.

As transformações previstas são:

- 🔍 Aumentar ou diminuir a figura;
- 🔄 Rotacionar a figura;
- ↔️ Refletir a figura.

---

⭐ Projeto desenvolvido para fins acadêmicos.
