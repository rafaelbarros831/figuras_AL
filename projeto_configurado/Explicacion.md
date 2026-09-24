# Conexão Teórica: Álgebra Linear Aplicada em C++ (2D e 3D)

Este documento detalha a fundamentação teórica da **Álgebra Linear** e a sua implementação direta em **C++20** no projeto de transformações geométricas.

---

## 1. Do Espaço Vetorial aos Tipos de Dados

Na matemática formal, a posição de um ponto no espaço $n$-dimensional é tratada como um vetor coluna em $\mathbb{R}^n$.

* **Espaço 2D ($\mathbb{R}^2$):** Representado pelo vetor $v = \begin{bmatrix} x \\ y \end{bmatrix}$.
* **Espaço 3D ($\mathbb{R}^3$):** Representado pelo vetor $v = \begin{bmatrix} x \\ y \\ z \end{bmatrix}$.

No projeto em C++, esses conceitos traduzem-se diretamente em estruturas de dados compostas por tipos primitivos de ponto flutuante:

```cpp
// Representação em R²
struct Ponto {
    double x, y;
};

// Representação em R³
struct Ponto3D {
    double x, y, z;
};
```
<img width="760" height="368" alt="image" src="https://github.com/user-attachments/assets/166e4e4d-b4b8-4f5c-b2ba-2c254a288250" />
<img width="776" height="449" alt="image" src="https://github.com/user-attachments/assets/8c1c8e51-3706-430b-9c5b-5471f7617126" />
<img width="878" height="348" alt="image" src="https://github.com/user-attachments/assets/76f22717-ffd1-4984-a518-a6e2d90b6f64" />

<img width="756" height="374" alt="image" src="https://github.com/user-attachments/assets/0aa7b0af-8bc6-411d-9a9a-e29701484aa9" />

```cpp
Matriz Transformacao::reflexaoX() {
    return Matriz(
        1.0,  0.0,
        0.0, -1.0
    );
}
```
