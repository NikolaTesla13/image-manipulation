#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <utility>
#include <cstdarg>
#include <float.h>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <functional>
#include <list>


#include <xorstr.h>

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include <GLFW/glfw3.h>
#include <imgui/imfilebrowser.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <shader.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

glm::vec3 camera(0, 0, 0);

enum Stages 
{
    CHOOSE_FILE, EDIT, SETTINGS
};

void customize()
{
    ImGuiStyle * style = &ImGui::GetStyle();
 
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;
    style->WindowBorderSize = 0.0f;
 
	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.06f, 0.05f, 0.07f, 1.0f); //
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);


    ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\ARLRDBD.ttf"), 21);
}

unsigned char *data;
int width, height, nrChannels;



int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Editor", NULL, NULL);

    if(window == NULL) {
        std::cout<<"Failed to create the window\n";
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    //load opengl pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<<"Failed to init GLAD\n";
        return -1;
    }

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();


    customize();

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), camera);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 mvp = proj * view * model;

    // build and compile shader program
    Shader ourShader("../shaders/vertexShader.vs", "../shaders/fragmentShader.fs");
    ourShader.use();
    ourShader.setMat4("u_MVP", mvp);

    ImVec4 clear_color = ImVec4(5.0f/255.0f, 10.0f/255.0f, 34.0f/255.0f, 1.0f);
    float dist = 3.0f;

    Stages stage = CHOOSE_FILE;
    ImGui::FileBrowser fileDialog;
    unsigned int texture;
    unsigned int VBO, VAO, EBO;
    
    // (optional) set browser properties
    fileDialog.SetTitle("Choose a file");
    fileDialog.SetTypeFilters({ ".jpg", ".png" });
    //render loop
    while(!glfwWindowShouldClose(window)) {
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        //render    
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplGlfwGL3_NewFrame();

        switch(stage)
        {
            case CHOOSE_FILE:
                {
                        if(ImGui::Begin("Welcome, user!"))
                        {
                            // open file dialog when user clicks this button
                            if(ImGui::Button("Choose a photo"))
                                fileDialog.Open();
                        }
                        ImGui::End();
                        
                        fileDialog.Display();
                        
                        if(fileDialog.HasSelected())
                        {
                            std::cout << "Selected filename " << fileDialog.GetSelected().string() << std::endl;
                            std::string path = fileDialog.GetSelected().string();
                            fileDialog.ClearSelected();

                            std::replace( path.begin(), path.end(), '\\', '/');

                            stbi_set_flip_vertically_on_load(true);
                            data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

                            float x = SCR_WIDTH/2.0f-width/2.0f, y=SCR_HEIGHT/2.0f-height/2.0f;

                            // set up vertex data and buffers and configure vertex attributes
                            float vertecies[] = {
                                // position            //colors           //textures
                                x + (float)width, y + (float)height, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
                                x + (float)width, y, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
                                x, y, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom-left
                                x, y + (float)height, 0.0f,   1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top-left
                            };

                            camera.x = (float)SCR_WIDTH-(float)width/2.0f;
                            camera.y= (float)SCR_HEIGHT-(float)height/2.0f;

                            unsigned int indices[] = {
                                0, 1, 3, // first triangle
                                3, 2, 1 // second triangle
                            };

                            glGenVertexArrays(1, &VAO);
                            glGenBuffers(1, &VBO);
                            glGenBuffers(1, &EBO);

                            glBindVertexArray(VAO);
                            glBindBuffer(GL_ARRAY_BUFFER, VBO);
                            glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

                            //position attribute
                            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
                            glEnableVertexAttribArray(0);

                            //color attribute
                            glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
                            glEnableVertexAttribArray(1);

                            //texture coords attribute
                            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
                            glEnableVertexAttribArray(2);

                            //load and create texture
                            glGenTextures(1, &texture);
                            glBindTexture(GL_TEXTURE_2D, texture);

                            //set the texture wrapping parameters
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                            // set texture filtering parameters
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                            if(data) {
                                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                                glGenerateMipmap(GL_TEXTURE_2D);
                            } else {
                                std::cout<<"Failed to load texture\n";
                            }

                            stbi_image_free(data);
                            stage = EDIT;
                        }
                }
                break;

            case EDIT:
                glBindTexture(GL_TEXTURE_2D, texture);

                view = glm::translate(glm::mat4(1.0f), camera);
                mvp = proj * view * model;
                ourShader.use();
                ourShader.setMat4("u_MVP", mvp);
                ourShader.setFloat("dist", 6.1f-dist);

                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                {
                    ImGui::Text("Options");
                    ImGui::SliderFloat("x", &camera.x, -(float)SCR_WIDTH, (float)SCR_WIDTH);
                    ImGui::SliderFloat("y", &camera.y, -(float)SCR_HEIGHT, (float)SCR_HEIGHT);
                    ImGui::SliderFloat("z", &dist, 1.0f, 5.0f);
                    ImGui::ColorEdit3("clear color", (float*)&clear_color);
                    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                }
                break;

            case SETTINGS:

                break;
        }
        

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // dealocate all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //terminate, clear all resources
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0, width, height);
}
