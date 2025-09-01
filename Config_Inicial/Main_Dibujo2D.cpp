// *****************************************************************************
// Practica 2
// Alumno: Álvarez Lugo Victor Manuel
// No. de cuenta: 319306972
// Fecha de entrega: 22/08/2025
// *****************************************************************************

#include <iostream>
#include <vector>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

//------------------------------------------------------------------------------
// Ajusta el viewport cuando la ventana cambia de tamaño, manteniendo
// siempre un área cuadrada centrada (evita deformar el sprite).
//------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height);

// Dimensiones iniciales de la ventana
const GLint WIDTH = 800, HEIGHT = 600;

//------------------------------------------------------------------------------
// Paleta de colores en formato RGB (valores normalizados 0.0 - 1.0).
// Cada índice corresponde a un color usado en el sprite.
//------------------------------------------------------------------------------
static const std::array<std::array<float, 3>, 6> PALETTE = { {
    {0.95f, 0.95f, 0.95f}, // 0 Fondo
    {0.00f, 0.00f, 0.00f}, // 1 Negro
    {1.00f, 0.80f, 0.60f}, // 2 Piel
    {0.00f, 1.00f, 0.00f}, // 3 Verde
    {0.08f, 0.25f, 0.75f}, // 4 Azul
    {0.53f, 0.81f, 0.98f}  // 5 Azul Cielo
} };

//------------------------------------------------------------------------------
// Sprite 24 X 24 .Cada celda almacena un índice de la paleta.
// 0 = transparente (no se dibuja)
//------------------------------------------------------------------------------
static const int COLS = 24, ROWS = 24;
static const int S[ROWS][COLS] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,2,2,2,2,2,2,2,2,2,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,2,1,2,2,2,2,2,1,2,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,2,2,2,1,1,1,2,2,2,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,1,3,3,0,0,0,0,0,0,0,0,0,3,3,1,0,0,0,0,0},
    {0,0,0,0,1,2,3,5,5,5,5,5,5,5,5,5,3,2,1,0,0,0,0,0},
    {0,0,0,0,1,2,3,5,5,5,5,5,5,5,5,5,3,2,1,0,0,0,0,0},
    {0,0,0,0,1,2,5,5,5,5,5,5,5,5,5,5,5,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,5,5,5,5,5,5,5,5,5,5,5,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,4,4,4,4,4,4,4,4,4,4,4,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,4,4,4,1,1,1,1,1,4,4,4,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

//------------------------------------------------------------------------------
// Genera la geometría de un cuadrado (2 triángulos) en la celda (cx, cy).
// Añade los vértices al buffer V, incluyendo posición y color.
//------------------------------------------------------------------------------
static void pushQuad(std::vector<float>& V, int cx, int cy,
    float cellW, float cellH,
    const std::array<float, 3>& c)
{
    float x0 = -1.0f + cx * cellW;
    float y0 = 1.0f - cy * cellH;
    float x1 = x0 + cellW;
    float y1 = y0 - cellH;

    auto add = [&](float x, float y) {
        V.push_back(x); V.push_back(y); V.push_back(0.0f);
        V.push_back(c[0]); V.push_back(c[1]); V.push_back(c[2]);
        };

    add(x0, y0); add(x1, y0); add(x1, y1);
    add(x0, y0); add(x1, y1); add(x0, y1);
}

//------------------------------------------------------------------------------
// Programa principal:
// - Inicializa GLFW/GLEW
// - Crea la ventana
// - Convierte la matriz en geometría de OpenGL
// - Dibuja el sprite en un bucle principal
//------------------------------------------------------------------------------
int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,
        "Practica 2 Alvarez Lugo Victor Manuel", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(window, resize);

    if (!window) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialise GLEW\n";
        return EXIT_FAILURE;
    }

    std::cout << "> Version:  " << glGetString(GL_VERSION) << '\n';
    std::cout << "> Vendor:   " << glGetString(GL_VENDOR) << '\n';
    std::cout << "> Renderer: " << glGetString(GL_RENDERER) << '\n';

    int fbw, fbh; glfwGetFramebufferSize(window, &fbw, &fbh);
    resize(window, fbw, fbh);

    Shader shader("Shader/core.vs", "Shader/core.frag");

    std::vector<float> vertices;
    vertices.reserve(ROWS * COLS * 6 * 6);

    float cellW = 2.0f / COLS;
    float cellH = 2.0f / ROWS;

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            int code = S[r][c];
            if (code == 0) continue;
            pushQuad(vertices, c, r, cellW, cellH, PALETTE[code]);
        }
    }

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
        vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    bool drawGrid = false;
    GLuint gridVAO = 0, gridVBO = 0;
    std::vector<float> grid;

    if (drawGrid) {
        for (int c = 0; c <= COLS; ++c) {
            float x = -1.0f + c * cellW;
            grid.insert(grid.end(), { x,  1.0f, 0.0f, 0.8f,0.8f,0.8f });
            grid.insert(grid.end(), { x, -1.0f, 0.0f, 0.8f,0.8f,0.8f });
        }
        for (int r = 0; r <= ROWS; ++r) {
            float y = 1.0f - r * cellH;
            grid.insert(grid.end(), { -1.0f, y, 0.0f, 0.8f,0.8f,0.8f });
            grid.insert(grid.end(), { 1.0f,  y, 0.0f, 0.8f,0.8f,0.8f });
        }

        glGenVertexArrays(1, &gridVAO);
        glGenBuffers(1, &gridVBO);
        glBindVertexArray(gridVAO);
        glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
        glBufferData(GL_ARRAY_BUFFER, grid.size() * sizeof(float),
            grid.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
            (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(PALETTE[0][0], PALETTE[0][1], PALETTE[0][2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();

        if (drawGrid) {
            glBindVertexArray(gridVAO);
            glLineWidth(1.0f);
            glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(grid.size() / 6));
        }

        glBindVertexArray(VAO);
        GLsizei count = static_cast<GLsizei>(vertices.size() / 6);
        glDrawArrays(GL_TRIANGLES, 0, count);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
// Ajusta el área de dibujo (viewport) a un cuadrado centrado en la ventana.
//------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    int size = (width < height) ? width : height;
    int x = (width - size) / 2;
    int y = (height - size) / 2;
    glViewport(x, y, size, size);
}
