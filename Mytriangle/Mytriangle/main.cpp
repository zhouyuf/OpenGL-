#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);//��Ⱦ���ڵĴ�С
void processInput(GLFWwindow *window);//�������

// ���ڿ�Ⱥ͸߶�
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//������ɫ��glsl
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Ƭ����ɫ��glsl
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main() {
	
	//--------��ʼ������---------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	//-------�������ڶ���--------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mytriangle", NULL, NULL);//��������
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();//������ʧ�ܣ��رմ���
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//ע�ắ�����ı䴰�ڴ�Сʱ����
	
	//����opengl����֮ǰ��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	
	//-----------������ɫ��-----------
	
	//������ɫ��
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//������ɫ������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//������ɫ��Դ����
	glCompileShader(vertexShader);//����
	//�����ɫ�������Ƿ�ɹ�
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX";
	}
	
	//Ƭ����ɫ��
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//������ɫ������
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//������ɫ��Դ����
	glCompileShader(fragmentShader);//����
	//����Ƿ����ɹ�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILEATION_FAILED\n" << infoLog << endl;
	}
	
	//--------��������ɫ���������ӵ�һ����ɫ������--------
	int shaderProgram = glCreateProgram();//������ɫ������
	glAttachShader(shaderProgram, vertexShader);//��������ɫ�����ӵ���ɫ������
	glAttachShader(shaderProgram, fragmentShader);//��Ƭ����ɫ�����ӵ���ɫ������
	glLinkProgram(shaderProgram);//�������и�����ɫ��
    //������Ӵ���
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	//ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	//��������
	float vertices[] = {
		-0.5f,-0.5f,0.0f,//�󶥵�
		 0.5f,-0.5f,0.0f,//�Ҷ���
		 0.0f, 0.5f,0.0f //�϶���
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);//�����������
	
	glGenBuffers(1, &VBO);//����������
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) 
	{
		processInput(window);

		//����ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);//������ɫ������
		glfwPollEvents();//����Ƿ񴥷��¼�
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
