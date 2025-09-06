// *****************************************************************************
// Practica 4
// Alumno: Álvarez Lugo Victor Manuel
// No. de cuenta: 319306972
// Fecha de entrega: 05/09/2025
// *****************************************************************************
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4 Alvarez Lugo Victor Manuel", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers



	//Matriz que se va a usar para el cuerpo
	float vertices[] = { 
		-0.5f, -0.5f, 0.5f, 0.16f, 0.60f,0.60f,//Front
		0.5f, -0.5f, 0.5f,  0.16f, 0.60f,0.60f,
		0.5f,  0.5f, 0.5f,  0.16f, 0.60f,0.60f,
		0.5f,  0.5f, 0.5f,  0.16f, 0.60f,0.60f,
		-0.5f,  0.5f, 0.5f, 0.16f, 0.60f,0.60f,
		-0.5f, -0.5f, 0.5f, 0.16f, 0.60f,0.60f,

		-0.5f, -0.5f,-0.5f, 0.16f, 0.60f,0.60f,//Back
		 0.5f, -0.5f,-0.5f, 0.16f, 0.60f,0.60f,
		 0.5f,  0.5f,-0.5f, 0.16f, 0.60f,0.60f,
		 0.5f,  0.5f,-0.5f, 0.16f, 0.60f,0.60f,
		-0.5f,  0.5f,-0.5f, 0.16f, 0.60f,0.60f,
		-0.5f, -0.5f,-0.5f, 0.16f, 0.60f,0.60f,

		0.5f, -0.5f, 0.5f,  0.16f, 0.60f,0.60f,
		0.5f,-0.5f,-0.5f,   0.16f, 0.60f,0.60f,
		0.5f, 0.5f, -0.5f,  0.16f, 0.60f,0.60f,
		0.5f, 0.5f, -0.5f,  0.16f, 0.60f,0.60f,
		0.5f, 0.5f,  0.5f,  0.16f, 0.60f,0.60f,
		0.5f,-0.5f, 0.5f,   0.16f, 0.60f,0.60f,

		-0.5f, 0.5f,  0.5f, 0.16f, 0.60f,0.60f,
		-0.5f, 0.5f, -0.5f, 0.16f, 0.60f,0.60f,
		-0.5f, -0.5f,-0.5f, 0.16f, 0.60f,0.60f,
		-0.5f, -0.5f,-0.5f, 0.16f, 0.60f,0.60f,
		-0.5f, -0.5f, 0.5f, 0.16f, 0.60f,0.60f,
		-0.5f,  0.5f, 0.5f, 0.16f, 0.60f,0.60f,

		-0.5f, -0.5f,-0.5f, 0.16f, 0.60f,0.60f,
		0.5f, -0.5f, -0.5f, 0.16f, 0.60f,0.60f,
		0.5f, -0.5f,  0.5f, 0.16f, 0.60f,0.60f,
		0.5f, -0.5f,  0.5f, 0.16f, 0.60f,0.60f,
		-0.5f, -0.5f, 0.5f, 0.16f, 0.60f,0.60f,
		-0.5f, -0.5f,-0.5f, 0.16f, 0.60f,0.60f,

		-0.5f,  0.5f,-0.5f, 0.16f, 0.60f,0.60f,
		0.5f,  0.5f, -0.5f, 0.16f, 0.60f,0.60f,
		0.5f,  0.5f,  0.5f, 0.16f, 0.60f,0.60f,
		0.5f,  0.5f,  0.5f, 0.16f, 0.60f,0.60f,
		-0.5f,  0.5f, 0.5f, 0.16f, 0.60f,0.60f,
		-0.5f,  0.5f,-0.5f, 0.16f, 0.60f,0.60f,
	};

	//Vertices con color amarillo para las patas, cola y pico/trompa

	float verticesYellow[] = {
		-0.5f, -0.5f, 0.5f, 1.00f, 0.60f,0.00f,//Front
		0.5f, -0.5f, 0.5f,  1.00f, 0.60f,0.00f,
		0.5f,  0.5f, 0.5f,  1.00f, 0.60f,0.00f,
		0.5f,  0.5f, 0.5f,  1.00f, 0.60f,0.00f,
		-0.5f,  0.5f, 0.5f, 1.00f, 0.60f,0.00f,
		-0.5f, -0.5f, 0.5f, 1.00f, 0.60f,0.00f,

		-0.5f, -0.5f,-0.5f, 1.00f, 0.60f,0.00f,//Back
		 0.5f, -0.5f,-0.5f, 1.00f, 0.60f,0.00f,
		 0.5f,  0.5f,-0.5f, 1.00f, 0.60f,0.00f,
		 0.5f,  0.5f,-0.5f, 1.00f, 0.60f,0.00f,
		-0.5f,  0.5f,-0.5f, 1.00f, 0.60f,0.00f,
		-0.5f, -0.5f,-0.5f, 1.00f, 0.60f,0.00f,

		0.5f, -0.5f, 0.5f,  1.00f, 0.60f,0.00f,
		0.5f,-0.5f,-0.5f,   1.00f, 0.60f,0.00f,
		0.5f, 0.5f, -0.5f,  1.00f, 0.60f,0.00f,
		0.5f, 0.5f, -0.5f,  1.00f, 0.60f,0.00f,
		0.5f, 0.5f,  0.5f,  1.00f, 0.60f,0.00f,
		0.5f,-0.5f, 0.5f,   1.00f, 0.60f,0.00f,

		-0.5f, 0.5f,  0.5f, 1.00f, 0.60f,0.00f,
		-0.5f, 0.5f, -0.5f, 1.00f, 0.60f,0.00f,
		-0.5f, -0.5f,-0.5f, 1.00f, 0.60f,0.00f,
		-0.5f, -0.5f,-0.5f, 1.00f, 0.60f,0.00f,
		-0.5f, -0.5f, 0.5f, 1.00f, 0.60f,0.00f,
		-0.5f,  0.5f, 0.5f, 1.00f, 0.60f,0.00f,

		-0.5f, -0.5f,-0.5f, 1.00f, 0.60f,0.00f,
		0.5f, -0.5f, -0.5f, 1.00f, 0.60f,0.00f,
		0.5f, -0.5f,  0.5f, 1.00f, 0.60f,0.00f,
		0.5f, -0.5f,  0.5f, 1.00f, 0.60f,0.00f,
		-0.5f, -0.5f, 0.5f, 1.00f, 0.60f,0.00f,
		-0.5f, -0.5f,-0.5f, 1.00f, 0.60f,0.00f,

		-0.5f,  0.5f,-0.5f, 1.00f, 0.60f,0.00f,
		0.5f,  0.5f, -0.5f, 1.00f, 0.60f,0.00f,
		0.5f,  0.5f,  0.5f, 1.00f, 0.60f,0.00f,
		0.5f,  0.5f,  0.5f, 1.00f, 0.60f,0.00f,
		-0.5f,  0.5f, 0.5f, 1.00f, 0.60f,0.00f,
		-0.5f,  0.5f,-0.5f, 1.00f, 0.60f,0.00f,
	};

	//Vertices con color blanco para los ojos

	float verticesWhite[] = {
		-0.5f, -0.5f, 0.5f, 1.00f, 1.00f,1.00f,//Front
		0.5f, -0.5f, 0.5f,  1.00f, 1.00f,1.00f,
		0.5f,  0.5f, 0.5f,  1.00f, 1.00f,1.00f,
		0.5f,  0.5f, 0.5f,  1.00f, 1.00f,1.00f,
		-0.5f,  0.5f, 0.5f, 1.00f, 1.00f,1.00f,
		-0.5f, -0.5f, 0.5f, 1.00f, 1.00f,1.00f,

		-0.5f, -0.5f,-0.5f, 1.00f, 1.00f,1.00f,//Back
		 0.5f, -0.5f,-0.5f, 1.00f, 1.00f,1.00f,
		 0.5f,  0.5f,-0.5f, 1.00f, 1.00f,1.00f,
		 0.5f,  0.5f,-0.5f, 1.00f, 1.00f,1.00f,
		-0.5f,  0.5f,-0.5f, 1.00f, 1.00f,1.00f,
		-0.5f, -0.5f,-0.5f, 1.00f, 1.00f,1.00f,

		0.5f, -0.5f, 0.5f,  1.00f, 1.00f,1.00f,
		0.5f,-0.5f,-0.5f,   1.00f, 1.00f,1.00f,
		0.5f, 0.5f, -0.5f,  1.00f, 1.00f,1.00f,
		0.5f, 0.5f, -0.5f,  1.00f, 1.00f,1.00f,
		0.5f, 0.5f,  0.5f,  1.00f, 1.00f,1.00f,
		0.5f,-0.5f, 0.5f,   1.00f, 1.00f,1.00f,

		-0.5f, 0.5f,  0.5f, 1.00f, 1.00f,1.00f,
		-0.5f, 0.5f, -0.5f, 1.00f, 1.00f,1.00f,
		-0.5f, -0.5f,-0.5f, 1.00f, 1.00f,1.00f,
		-0.5f, -0.5f,-0.5f, 1.00f, 1.00f,1.00f,
		-0.5f, -0.5f, 0.5f, 1.00f, 1.00f,1.00f,
		-0.5f,  0.5f, 0.5f, 1.00f, 1.00f,1.00f,

		-0.5f, -0.5f,-0.5f, 1.00f, 1.00f,1.00f,
		0.5f, -0.5f, -0.5f, 1.00f, 1.00f,1.00f,
		0.5f, -0.5f,  0.5f, 1.00f, 1.00f,1.00f,
		0.5f, -0.5f,  0.5f, 1.00f, 1.00f,1.00f,
		-0.5f, -0.5f, 0.5f, 1.00f, 1.00f,1.00f,
		-0.5f, -0.5f,-0.5f, 1.00f, 1.00f,1.00f,

		-0.5f,  0.5f,-0.5f, 1.00f, 1.00f,1.00f,
		0.5f,  0.5f, -0.5f, 1.00f, 1.00f,1.00f,
		0.5f,  0.5f,  0.5f, 1.00f, 1.00f,1.00f,
		0.5f,  0.5f,  0.5f, 1.00f, 1.00f,1.00f,
		-0.5f,  0.5f, 0.5f, 1.00f, 1.00f,1.00f,
		-0.5f,  0.5f,-0.5f, 1.00f, 1.00f,1.00f,
	};

	//Vertices con color negro para las pupilas
	float verticesBlack[] = {
		-0.5f, -0.5f, 0.5f, 0.00f, 0.00f,0.00f,//Front
		0.5f, -0.5f, 0.5f,  0.00f, 0.00f,0.00f,
		0.5f,  0.5f, 0.5f,  0.00f, 0.00f,0.00f,
		0.5f,  0.5f, 0.5f,  0.00f, 0.00f,0.00f,
		-0.5f,  0.5f, 0.5f, 0.00f, 0.00f,0.00f,
		-0.5f, -0.5f, 0.5f, 0.00f, 0.00f,0.00f,

		-0.5f, -0.5f,-0.5f, 0.00f, 0.00f,0.00f,//Back
		 0.5f, -0.5f,-0.5f, 0.00f, 0.00f,0.00f,
		 0.5f,  0.5f,-0.5f, 0.00f, 0.00f,0.00f,
		 0.5f,  0.5f,-0.5f, 0.00f, 0.00f,0.00f,
		-0.5f,  0.5f,-0.5f, 0.00f, 0.00f,0.00f,
		-0.5f, -0.5f,-0.5f, 0.00f, 0.00f,0.00f,

		0.5f, -0.5f, 0.5f,  0.00f, 0.00f,0.00f,
		0.5f,-0.5f,-0.5f,   0.00f, 0.00f,0.00f,
		0.5f, 0.5f, -0.5f,  0.00f, 0.00f,0.00f,
		0.5f, 0.5f, -0.5f,  0.00f, 0.00f,0.00f,
		0.5f, 0.5f,  0.5f,  0.00f, 0.00f,0.00f,
		0.5f,-0.5f, 0.5f,   0.00f, 0.00f,0.00f,

		-0.5f, 0.5f,  0.5f, 0.00f, 0.00f,0.00f,
		-0.5f, 0.5f, -0.5f, 0.00f, 0.00f,0.00f,
		-0.5f, -0.5f,-0.5f, 0.00f, 0.00f,0.00f,
		-0.5f, -0.5f,-0.5f, 0.00f, 0.00f,0.00f,
		-0.5f, -0.5f, 0.5f, 0.00f, 0.00f,0.00f,
		-0.5f,  0.5f, 0.5f, 0.00f, 0.00f,0.00f,

		-0.5f, -0.5f,-0.5f, 0.00f, 0.00f,0.00f,
		0.5f, -0.5f, -0.5f, 0.00f, 0.00f,0.00f,
		0.5f, -0.5f,  0.5f, 0.00f, 0.00f,0.00f,
		0.5f, -0.5f,  0.5f, 0.00f, 0.00f,0.00f,
		-0.5f, -0.5f, 0.5f, 0.00f, 0.00f,0.00f,
		-0.5f, -0.5f,-0.5f, 0.00f, 0.00f,0.00f,

		-0.5f,  0.5f,-0.5f, 0.00f, 0.00f,0.00f,
		0.5f,  0.5f, -0.5f, 0.00f, 0.00f,0.00f,
		0.5f,  0.5f,  0.5f, 0.00f, 0.00f,0.00f,
		0.5f,  0.5f,  0.5f, 0.00f, 0.00f,0.00f,
		-0.5f,  0.5f, 0.5f, 0.00f, 0.00f,0.00f,
		-0.5f,  0.5f,-0.5f, 0.00f, 0.00f,0.00f,
	};



	GLuint VBO, VAO, VBO2, VAO2, VBO3, VAO3, VBO4, VAO4;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	//Ahora para el color Amarillo 
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesYellow), verticesYellow, GL_STATIC_DRAW);

	// Posición
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Ahora para el color Blanco
	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);

	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesWhite), verticesWhite, GL_STATIC_DRAW);

	// Posición
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Ahora para el color Negro
	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);

	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBlack), verticesBlack, GL_STATIC_DRAW);

	// Posición
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);

		//Ahora en vez de numeros se le van a pasar Variables
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);//Matriz con el color para el Cuerpo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 0.5f)); //Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		glBindVertexArray(VAO2); //Matriz para los detalles Amarillos
		//Aqui se dibuja la primera pata del Ornitorrinco
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.18f, 0.09f, 0.15f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(2.8f, -0.0f, 3.3f));//Se ubica en el lado derecho del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		////Segunda pata del ornitorrinco
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.18f, 0.09f, 0.15f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(-1.0f, -0.0f, 3.3f));//Se ubica en el lado izquierdo del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
		////Tercera Pata (Pata trasera)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.18f, 0.09f, 0.15f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(-1.0f, -0.0f, 0.0f));//Se ubica en la parte posterior derecha del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		////Cuarta pata (Pata trasera)
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.18f, 0.09f, 0.15f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(2.8f, -0.0f, 0.0f));//Se ubica en la parte posterior izquierda del cuerpo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Primera parte de su cola
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.18f, 0.09f, 0.5f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(-3.2f, 3.0f, 0.5f));//Se ubica en la parte trasera del cuerpo a una altura media
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Segunda Parte de su cola
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.18f, 0.09f, 0.3f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(-4.0f, 3.0f, 0.9f));//Se ubica un poco mas atras de la primera parte de la cola
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Pico o Trompa del Ornitorrinco
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.09f, 0.3f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(2.1f, 3.0f, 0.83f));//Se ubica en la parte de enfrente del cuerpo a una altura media
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(VAO3);//Matriz para los ojos
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(2.9f, 3.7f,-0.0f));//Se ubica un poco mas arriba del cuerpo de lado derecho
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(2.9f, 3.7f, 3.5f));//Se ubica un poco mas arriba del cuerpo de lado izquierdo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

	
		glBindVertexArray(VAO4); //Matriz para las pupilas
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(6.8f, 8.6f, 8.3f));//Se ubica casi al borde el ojo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));//Se moldea a un tamaño adecuado
		model = glm::translate(model, glm::vec3(6.8f, 8.6f, -0.6f));//Se ubican casi al borde del rojo
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//Si presionamos D se mueve la visa a la derecha
		movX += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//Si presionamos A se mueve la vista a la izquierda
		movX -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)//Si presionamos  se mueve la vista a la
		movY += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)//Si presionamos  se mueve la vista a la 
		movY -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//Si presionamos W se mueve la vista hacia atras
		movZ -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//Si presionamos S se mueve la vista hacia enfrente
		movZ += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)//Si presionamos  se mueve la vista a la izquierda
		rot += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)//Si presionamos  se mueve la vista a la izquierda
		rot -= 0.01f;
}
