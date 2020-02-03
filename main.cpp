#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/ShaderProgram.h"
#include "src/Texture.h"
#include "src/camera.h"


void programOne(GLFWwindow* window);
void programArc(GLFWwindow* window);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int run()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if ( ! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//stbi_set_flip_vertically_on_load(true);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//programOne(window);
	programArc(window);

	glfwTerminate();
	return 0;
}


void programArc(GLFWwindow* window)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	/*
		Player 1
	*/

	// setup vertices
	float arcVertices[] = {
		// positions      
		 0.0f,  0.8f, 0.0f
	};
	unsigned int arcVAO, arcVBO;
	glGenVertexArrays(1, &arcVAO);
	glGenBuffers(1, &arcVBO);
	glBindVertexArray(arcVAO);
	glBindBuffer(GL_ARRAY_BUFFER, arcVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(arcVertices), arcVertices, GL_STATIC_DRAW);
	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	Texture textureContainer = Texture("./assets/image/container.jpg");
	ShaderProgram arcShaderProgram = ShaderProgram(
		"./src/shaders/arc.vert",
		"./src/shaders/arc.frag",
		"./src/shaders/arc.geom"
	);
	arcShaderProgram.use();
	arcShaderProgram.set1i("aTexture", 0);
	arcShaderProgram.set1f("size", 30.0f);


	/*
		Skybox
	*/
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	std::vector<std::string> skyboxImages
	{
		"./assets/image/skybox/right.jpg",
		"./assets/image/skybox/left.jpg",
		"./assets/image/skybox/top.jpg",
		"./assets/image/skybox/bottom.jpg",
		"./assets/image/skybox/front.jpg",
		"./assets/image/skybox/back.jpg"
	};
	Texture textureSkybox = Texture(skyboxImages);
	ShaderProgram skyboxShaderProgram = ShaderProgram(
		"./src/shaders/skybox.vert",
		"./src/shaders/skybox.frag"
	);
	skyboxShaderProgram.use();
	skyboxShaderProgram.set1i("skybox", 0);


	// main loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Arc Player
		arcShaderProgram.use();
		arcShaderProgram.set1f("angle", 30.0 * (float)glfwGetTime());
		glActiveTexture(GL_TEXTURE0);
		textureContainer.bind();
		glBindVertexArray(arcVAO);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);

		// Skybox
		glDepthFunc(GL_LEQUAL);
		skyboxShaderProgram.use();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		skyboxShaderProgram.setMat4("view", view);
		skyboxShaderProgram.setMat4("projection", projection);

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		textureSkybox.bindSkybox();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &arcVAO);
	glDeleteBuffers(1, &arcVBO);

	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
}


void programOne(GLFWwindow* window)
{
	Texture textureContainer = Texture("./assets/image/container.jpg");
	Texture textureFace = Texture("./assets/image/awesomeface.png");
	ShaderProgram shaderProgram = ShaderProgram("./src/shaders/vertex.vert", "./src/shaders/fragment.frag");

	// setup vertices
	float vertices[] = {
		// positions            // texture coords
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f    // top left 
	};
	unsigned int indices[] = {
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	shaderProgram.use();
	shaderProgram.set1i("aTexture1", 0);
	shaderProgram.set1i("aTexture2", 1);

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		shaderProgram.setMatrix4fv("transform", 1, GL_FALSE, glm::value_ptr(trans));

		glActiveTexture(GL_TEXTURE0);
		textureContainer.bind();

		glActiveTexture(GL_TEXTURE1);
		textureFace.bind();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


int main()
{
	try {
		return run();
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
}

