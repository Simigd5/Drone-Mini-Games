#include "lab_m1/lab5/lab5.h"

#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "lab_m1/lab4/transform3D.h"
#include "lab_m1/lab5/lab_camera.h"
using namespace std;
using namespace m1;

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab5::Lab5()
{
}


Lab5::~Lab5()
{
    hasPassedGate1 = false;
    hasPassedGate2 = false;
    hasPassedGate3 = false;
    hasPassedGate4 = false;
    hasPassedGate5 = false;
    hasPassedGate6 = false;
    hasPassedGate7 = false;
    translateX = 0.0f; // Inițializezi și alte variabile dacă este cazul
    translateY = 0.0f;
    translateZ = 0.0f;
}
std::chrono::high_resolution_clock::time_point startTime;
//bool hasFinished = false; // Variabilă pentru verificarea coliziunii


void Lab5::Init()
{
    renderCameraTarget = false;
    projectionType = true;

    right = 10.f;
    left = .01f;
    bottom = .01f;
    top = 10.f;
    fov = 40.f;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));


    startTime = std::chrono::high_resolution_clock::now();

    treePositions = {
        glm::vec3(-13.0f, 0.1f, 18.0f),
        glm::vec3(-18, 0.1f, 14),
        glm::vec3(-3, 0.1f, 18),
        glm::vec3(-3, 0.1f, 13),
        glm::vec3(-11, 0.1f, 11),
        glm::vec3(-13, 0.1f, 2),
        glm::vec3(2, 0.1f, 6),
        glm::vec3(2, 0.1f, 22),
        glm::vec3(10, 0.1f, 7),
        glm::vec3(19, 0.1f, 22),
        glm::vec3(10, 0.1f, 17),
        glm::vec3(18, 0.1f, 1),
        glm::vec3(4, 0.1f, -3),
        glm::vec3(12, 0.1f, -2),
        glm::vec3(12, 0.1f, -7),
        glm::vec3(19, 0.1f, -8),
        glm::vec3(16, 0.1f, -16),
        glm::vec3(7, 0.1f, -12),
        glm::vec3(7, 0.1f, -21),
        glm::vec3(-6, 0.1f, -4),
        glm::vec3(-13, 0.1f, -5),
        glm::vec3(-19, 0.1f, -2),
        glm::vec3(-4, 0.1f, -3),
        glm::vec3(-9, 0.1f, -12),
        glm::vec3(-14, 0.1f, -13),
        glm::vec3(-20, 0.1f, -19),
        glm::vec3(-2, 0.1f, -16),
        glm::vec3(-16, 0.1f, -20),
    };
    conPositions = {
         glm::vec3(-7, 0.1f, 21),
         glm::vec3(-15, 0.1f, 13),
         glm::vec3(-4, 0.1f, 9),
         glm::vec3(-8, 0.1f, 3),
         glm::vec3(-7, 0.1f, 21),
         glm::vec3(2, 0.1f, 1),
         glm::vec3(6, 0.1f, 2),
         glm::vec3(2, 0.1f, 14),
         glm::vec3(14, 0.1f, 19),
         glm::vec3(16, 0.1f, 8),
         glm::vec3(19, 0.1f, -2),
         glm::vec3(9, 0.1f, -5),
         glm::vec3(3, 0.1f, -9),
         glm::vec3(2, 0.1f, -19),
         glm::vec3(7, 0.1f, -16),
         glm::vec3(16, 0.1f, -10),
         glm::vec3(17, 0.1f, 21),
         glm::vec3(-10, 0.1f,-4),
         glm::vec3(-5, 0.1f,-10),
         glm::vec3(-6, 0.1f,-17),
         glm::vec3(-20, 0.1f,-17),
         glm::vec3(-10, 0.1f,-19),
         glm::vec3(-12, 0.1f,-22),
         glm::vec3(-19, 0.1f,-4),
         glm::vec3(-14, 0.1f,-9),
         glm::vec3(-8, 0.1f,-23),
    };
    obs2Positions = {
    glm::vec3(-16, 0.1f, 21),
    glm::vec3(-18, 0.1f, 10),
    glm::vec3(-12, 0.1f, 6),
    glm::vec3(-23, 0.1f, 1),
    glm::vec3(-2, 0.1f, 2),
    glm::vec3(-7, 0.1f, 16),
    glm::vec3(5, 0.1f, 10),
    glm::vec3(8, 0.1f, 13),
    glm::vec3(6, 0.1f, 19),
    glm::vec3(16, 0.1f, 14),
    glm::vec3(13, 0.1f, 3),
    glm::vec3(10, 0.1f, 0),
    glm::vec3(1, 0.1f, -5),
    glm::vec3(2, 0.1f, -14),
    glm::vec3(12, 0.1f, -13),
    glm::vec3(19, 0.1f, -13),
    glm::vec3(13, 0.1f, 20),
    glm::vec3(-3, 0.1f,-2),
    glm::vec3(-15, 0.1f,-2),
    glm::vec3(-2, 0.1f,-7),
    glm::vec3(-9, 0.1f,-7),
    glm::vec3(-19, 0.1f,-8),
    glm::vec3(-23, 0.1f,-13),
    glm::vec3(-5, 0.1f,-13),
    glm::vec3(-13, 0.1f,-16),
    glm::vec3(-21, 0.1f,-21),
    };
    // Raza pomilor
    //treeRadius = 0.5f;


    planeX = 1;
    planeY = 3;

    //glm::vec3 center = glm::vec3(0, 0, 0);


    {
        Mesh* mesh = new Mesh("pom");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "pom.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("bazaSteag");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "bazaSteag.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("Steag");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "steag.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("PatrateSteag");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "patrateSteag.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("BazaObstacol2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "obstacol2Baza.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("negru");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "alb2.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("portocaliu");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "portocaliu2.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("poarta");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "poarta.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("st");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cevastart.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("conA");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "con.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("conP");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "conbaza.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("1");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "1.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "2.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("3");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "3.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("4");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "4.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("5");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "5.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("6");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "6.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("7");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "7.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    int m = 51;
    int n = 51;  // Numărul de celule pe axa Z
    float cellSize = 1.0f;  // Dimensiunea fiecărei celule

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    float centerX = (n * cellSize) / 2.0f;  // Centru pe axa X
    float centerZ = (m * cellSize) / 2.0f;  // Centru pe axa Z

    // Generăm vertecșii pentru grid
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            float x = j * cellSize - centerX;  // Ajustăm poziția X pentru a centra terenul
            float z = i * cellSize - centerZ;  // Ajustăm poziția Z pentru a centra terenul
            glm::vec3 color = glm::vec3(0.9f, 0.8f, 0.2f);  // Culoare verde
            vertices.emplace_back(glm::vec3(x, 0.1, z), glm::vec3(0, 1, 0), color);  // Poziție, normală, culoare
        }
    }
    // Generăm indicii pentru triunghiuri
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int topLeft = i * (n + 1) + j;
            int topRight = topLeft + 1;
            int bottomLeft = topLeft + (n + 1);
            int bottomRight = bottomLeft + 1;

            // Triunghiul 1 (diagonală principală)
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);

            // Triunghiul 2 (diagonală inversă)
            indices.push_back(topLeft);
            indices.push_back(bottomRight);
            indices.push_back(topRight);
        }
    }
    // Creăm mesh-ul
    Mesh* terrainMesh = new Mesh("terrain");
    terrainMesh->InitFromData(vertices, indices);
    meshes[terrainMesh->GetMeshID()] = terrainMesh;


    polygonMode = GL_FILL;

    Mesh* mesh = new Mesh("box");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[mesh->GetMeshID()] = mesh;

    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0.2f;
    translateZ = 0;

    // Initialize sx, sy and sz (the scale factors)
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);


    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("PomShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "pom", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "pom", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("DronaShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "drona", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "drona", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("EliceShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "elice", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "elice", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("BazaSteagShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "bazaSteag", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "BazaSteag", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("SteagShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "steag", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "steag", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("PatrateSteagShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "patrateSteag", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "patrateSteag", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("BazaObstacol2");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "obstacol2Baza", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "obstacol2Baza", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("Negru2");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "negru2", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "negru2", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("Portocaliu2");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "portocaliu2", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "portocaliu2", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("alb");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "Alb", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "Alb", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("green");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "green", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "green", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("yellow");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "yellow", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "yellow", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("red");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "red", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "red", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("pink");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "pink", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "pink", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("purple");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "purple", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab7", "purple", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }


    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

}

void Lab5::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.3, 0.0, 0.4, 1.0); // Dark purple, more towards purple

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Lab5::RenderScene() {
    glUseProgram(shaders["Simple"]->program);
    glUniform1f(glGetUniformLocation(shaders["Simple"]->program, "frequency"), frequency);
    glUniform1f(glGetUniformLocation(shaders["Simple"]->program, "amplitude"), amplitude);


    glm::mat4 modelMatrix = glm::mat4(1);
    RenderMesh(meshes["terrain"], shaders["LabShader"], modelMatrix);


    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(-120);
    modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    modelMatrix *= transform3D::Scale(1.0f, 0.05f, 0.05f);
    RenderMesh(meshes["box"], shaders["DronaShader"], modelMatrix);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(120);
    modelMatrix *= transform3D::Scale(1.0f, 0.05f, 0.05f);
    RenderMesh(meshes["box"], shaders["DronaShader"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.37f, 0.05f, 0.27f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(-120);
    modelMatrix *= transform3D::Scale(0.08f, 0.05f, 0.05f);
    RenderMesh(meshes["box"], shaders["DronaShader"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-0.37f, 0.05f, 0.27f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(120);
    modelMatrix *= transform3D::Scale(0.08f, 0.05f, 0.05f);
    RenderMesh(meshes["box"], shaders["DronaShader"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-0.37f, 0.05f, -0.27f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(-120);
    modelMatrix *= transform3D::Scale(0.08f, 0.05f, 0.05f);
    RenderMesh(meshes["box"], shaders["DronaShader"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.37f, 0.05f, -0.27f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(120);
    modelMatrix *= transform3D::Scale(0.08f, 0.05f, 0.05f);
    RenderMesh(meshes["box"], shaders["DronaShader"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.37f, 0.08f, 0.27f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(glm::radians(rotationAngleY));
    modelMatrix *= transform3D::Scale(0.02f, 0.02f, 0.25f);
    RenderMesh(meshes["box"], shaders["EliceShader"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-0.37f, 0.08f, 0.27f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(glm::radians(rotationAngleY));
    modelMatrix *= transform3D::Scale(0.02f, 0.02f, 0.25f);
    RenderMesh(meshes["box"], shaders["EliceShader"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-0.37f, 0.08f, -0.27f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(glm::radians(rotationAngleY));
    modelMatrix *= transform3D::Scale(0.02f, 0.02f, 0.25f);
    RenderMesh(meshes["box"], shaders["EliceShader"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.37f, 0.08f, -0.27f);
    modelMatrix *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrix *= transform3D::RotateOY(glm::radians(rotationAngleY));
    modelMatrix *= transform3D::Scale(0.02f, 0.02f, 0.25f);
    RenderMesh(meshes["box"], shaders["EliceShader"], modelMatrix);

    for (const auto& treePos : treePositions) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(treePos.x, treePos.y, treePos.z);
        modelMatrix *= transform3D::Scale(0.35f, 0.35f, 0.35f); // Dimensiunea pomului
        RenderMesh(meshes["pom"], shaders["PomShader"], modelMatrix);
    }

    for (const auto& conPos : conPositions) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(conPos.x, conPos.y, conPos.z);
        modelMatrix *= transform3D::Scale(0.75f, 0.75f, 0.75f);
        RenderMesh(meshes["conP"], shaders["Portocaliu2"], modelMatrix);

        glm::mat4 modelMatrix1 = glm::mat4(1);
        modelMatrix1 *= transform3D::Translate(conPos.x, conPos.y, conPos.z);
        modelMatrix1 *= transform3D::Scale(0.76f, 0.76f, 0.76f);
        RenderMesh(meshes["conA"], shaders["SteagShader"], modelMatrix1);
    }

    for (const auto& obs2Pos : obs2Positions) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(obs2Pos.x, obs2Pos.y, obs2Pos.z);
        modelMatrix *= transform3D::Scale(0.35f, 0.35f, 0.35f);
        RenderMesh(meshes["BazaObstacol2"], shaders["BazaObstacol2"], modelMatrix);

        glm::mat4 modelMatrix1 = glm::mat4(1);
        modelMatrix1 *= transform3D::Translate(obs2Pos.x, obs2Pos.y, obs2Pos.z);
        modelMatrix1 *= transform3D::Scale(0.35f, 0.35f, 0.35f);
        RenderMesh(meshes["negru"], shaders["Negru2"], modelMatrix1);

        glm::mat4 modelMatrix2 = glm::mat4(1);
        modelMatrix2 *= transform3D::Translate(obs2Pos.x, obs2Pos.y, obs2Pos.z);
        modelMatrix2 *= transform3D::Scale(0.36f, 0.36f, 0.36f);
        RenderMesh(meshes["portocaliu"], shaders["Portocaliu2"], modelMatrix2);
    }
    RenderMesh(meshes["bazaSteag"], shaders["BazaSteagShader"], glm::vec3(20, 0.1f, -20), glm::vec3(0.75f));
    RenderMesh(meshes["Steag"], shaders["SteagShader"], glm::vec3(20, 0.1f, -20), glm::vec3(0.75f));
    RenderMesh(meshes["PatrateSteag"], shaders["PatrateSteagShader"], glm::vec3(20, 0.1f, -20), glm::vec3(0.75f));
    RenderMesh(meshes["bazaSteag"], shaders["BazaSteagShader"], glm::vec3(-22, 0.1f, 22), glm::vec3(0.75f));
    RenderMesh(meshes["st"], shaders["green"], glm::vec3(-23.9, -0.25f, 22), glm::vec3(0.43f));
    RenderMesh(meshes["1"], shaders["alb"], glm::vec3(-18.3f, 1.3, 18.0f), glm::vec3(0.30f));
    RenderMesh(meshes["2"], shaders["Portocaliu2"], glm::vec3(11.7f, 1.3f, 12.0f), glm::vec3(0.30f));
    RenderMesh(meshes["3"], shaders["green"], glm::vec3(-6.3f, 1.3f, 6.0f), glm::vec3(0.30f));
    RenderMesh(meshes["4"], shaders["yellow"], glm::vec3(-0.3f, 1.3f, 0.0f), glm::vec3(0.30f));
    RenderMesh(meshes["5"], shaders["red"], glm::vec3(5.7f, 1.3f, -6.0f), glm::vec3(0.30f));
    RenderMesh(meshes["6"], shaders["pink"], glm::vec3(-12.3f, 1.3f, -12.0f), glm::vec3(0.30f));
    RenderMesh(meshes["7"], shaders["purple"], glm::vec3(17.7f, 1.3f, -18.0f), glm::vec3(0.30f));
    // Desenare Poarta 1

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-18.0f, 0.1f, 18.0f);
    modelMatrix *= transform3D::Scale(0.8f, 1.0f, 0.45f);
    RenderMesh(meshes["poarta"], shaders["alb"], modelMatrix);

    // Desenare Poarta 2
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(12.0f, 0.1f, 12.0f);
    modelMatrix *= transform3D::Scale(0.8f, 1.0f, 0.45f);
    RenderMesh(meshes["poarta"], shaders["Portocaliu2"], modelMatrix);

    // Desenare Poarta 3
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-6.0f, 0.1f, 6.0f);
    modelMatrix *= transform3D::Scale(0.8f, 1.0f, 0.45f);
    RenderMesh(meshes["poarta"], shaders["green"], modelMatrix);

    // Desenare Poarta 4
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(0.0f, 0.1f, 0.0f);
    modelMatrix *= transform3D::Scale(0.8f, 1.0f, 0.45f);
    RenderMesh(meshes["poarta"], shaders["yellow"], modelMatrix);

    // Desenare Poarta 5
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(6.0f, 0.1f, -6.0f);
    modelMatrix *= transform3D::Scale(0.8f, 1.0f, 0.45f);
    RenderMesh(meshes["poarta"], shaders["red"], modelMatrix);

    // Desenare Poarta 6
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(-12.0f, 0.1f, -12.0f);
    modelMatrix *= transform3D::Scale(0.8f, 1.0f, 0.45f);
    RenderMesh(meshes["poarta"], shaders["pink"], modelMatrix);

    // Desenare Poarta 7
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D::Translate(18.0f, 0.1f, -18.0f);
    modelMatrix *= transform3D::Scale(0.8f, 1.0f, 0.45f);
    RenderMesh(meshes["poarta"], shaders["purple"], modelMatrix);
}
void Lab5::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Gravitația și propulsia
   // float accelerationY = gravity + thrust / mass; // Acceleratia neta pe Oy
   // velocityY += accelerationY * deltaTimeSeconds; // Update viteza pe Oy
   // translateY += velocityY * deltaTimeSeconds;    // Update poziția pe Oy

    // Prevenirea coliziunii cu solul
    if (translateY < 0.2f) {
        translateY = 0.2f;
        velocityY = 0.0f; // Oprește viteza dacă drona atinge solul
    }

    // Prevenirea coliziunii cu solul
    if (translateY > 5.0f) {
       translateY = 5.0f;
        velocityY = 0.0f; // Oprește viteza dacă drona atinge solul
    }
    // Control rotație și mișcare
    rotationAngleY += deltaTimeSeconds * 200.0f;
    if (rotationAngleY > 360.0f) {
        rotationAngleY -= 360.0f;
    }
    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    RenderScene();
    DrawCoordinateSystem();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    RenderScene();
    DrawCoordinateSystem();


    rotationAngleY += deltaTimeSeconds * 3000.0f;
    if (rotationAngleY > 360.0f) {
        rotationAngleY -= 360.0f;
    }


    if (rotationAngleY > 360.0f) {
        rotationAngleY -= 360.0f;
    }

    if (window->KeyHold(GLFW_KEY_UP)) amplitude += deltaTimeSeconds;  // Crește amplitudinea
    if (window->KeyHold(GLFW_KEY_DOWN)) amplitude -= deltaTimeSeconds;  // Scade amplitudinea
    if (window->KeyHold(GLFW_KEY_LEFT)) frequency -= deltaTimeSeconds;  // Scade frecvența
    if (window->KeyHold(GLFW_KEY_RIGHT)) frequency += deltaTimeSeconds;  // Crește frecvența


    // Desenăm scena
    RenderScene();
    DrawCoordinateSystem();
}


void Lab5::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Lab5::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab5::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(!GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W))
        {
            // Translate the camera forward
            camera->TranslateForward(deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_A))
        {
            // Translate the camera to the left
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_S))
        {
            // Translate the camera backwards
            camera->TranslateForward(-deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_D))
        {
            // Translate the camera to the right
            camera->TranslateRight(deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_Q))
        {
            // Translate the camera down
            camera->TranslateUpward(-deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_E))
        {
            // Translate the camera up
            camera->TranslateUpward(deltaTime * cameraSpeed);
        }
    }

    float speed = 2;
    //float treeradius = 0.35;
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

        // Control thrust (propulsia)
       /* if (window->KeyHold(GLFW_KEY_W)) {
            thrust += 2.0f * deltaTime; 
            translateY += 2.0f * deltaTime; 
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            thrust -= 3.0f * deltaTime; 
            translateY -= 3.0f * deltaTime; 
        }

        // Limitează propulsia pentru a evita valori extreme
        if (thrust < 0.0f) thrust = 0.0f; 
        if (thrust > 10.0f) thrust = 10.0f; 
        */
        // Evită ca drona să coboare sub sol
        if (translateY < 0.2f) {
            translateY = 0.2f;
            thrust = 0.0f; // Resetează thrust-ul când atinge solul
        }

        // Controlează mișcările laterale și înainte/înapoi
        if (window->KeyHold(GLFW_KEY_A)) translateX -= 2 * deltaTime; // Move left
        if (window->KeyHold(GLFW_KEY_D)) translateX += 2 * deltaTime; // Move right
        if (window->KeyHold(GLFW_KEY_R)) translateZ += 2 * deltaTime; // Move forward
        if (window->KeyHold(GLFW_KEY_F)) translateZ -= 2 * deltaTime; // Move backward
        if (window->KeyHold(GLFW_KEY_W)) translateY += 2 * deltaTime; // Move forward
        if (window->KeyHold(GLFW_KEY_S)) translateY -= 2 * deltaTime; // Move backward

        // Verificare coliziuni cu pomii
        for (const auto& treePos : treePositions) {
            float distanceXZ = glm::distance(glm::vec2(translateX, translateZ), glm::vec2(treePos.x, treePos.z));

            // h pom
            float treeHeight = 1.8f;

            if (distanceXZ < treeRadius && translateY >= treePos.y && translateY <= treePos.y + treeHeight) {
                /*std::cout << "Collision with tree at: "
                    << treePos.x << ", "
                    << treePos.y << ", "
                    << treePos.z << std::endl;*/
                    /* { if (translateY < 2.0f) {
                        translateY = 2.0f;
                        velocityY = 2.0f; // Oprește viteza dacă drona atinge solul
                    }
                    // Revenire la poziția anterioară
                    if (window->KeyHold(GLFW_KEY_W)) thrust += 5.0f * deltaTime; // Crește propulsia
                    if (window->KeyHold(GLFW_KEY_S)) thrust -= 5.0f * deltaTime; // Reduce propulsia
                    }*/
                    // Limitează thrust pentru a evita valori extreme
                //if (thrust < 0.0f) thrust = 0.0f;
                if (window->KeyHold(GLFW_KEY_W)) translateY -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_S)) translateY += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_A)) translateX += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_D)) translateX -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_R)) translateZ -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_F)) translateZ += speed * deltaTime;
            }
        }

        for (const auto& conPos : conPositions) {
            float distanceXZ = glm::distance(glm::vec2(translateX, translateZ), glm::vec2(conPos.x, conPos.z));

            // h con
            float conH = 1.0f;

            if (distanceXZ < treeRadius && translateY >= conPos.y && translateY <= conPos.y + conH) {
                /*std::cout << "Collision with tree at: "
                    << treePos.x << ", "
                    << treePos.y << ", "
                    << treePos.z << std::endl;*/
                    /* { if (translateY < 2.0f) {
                        translateY = 2.0f;
                        velocityY = 2.0f; // Oprește viteza dacă drona atinge solul
                    }
                    // Revenire la poziția anterioară
                    if (window->KeyHold(GLFW_KEY_W)) thrust += 5.0f * deltaTime; // Crește propulsia
                    if (window->KeyHold(GLFW_KEY_S)) thrust -= 5.0f * deltaTime; // Reduce propulsia
                    }*/
                    // Limitează thrust pentru a evita valori extreme
                //if (thrust < 0.0f) thrust = 0.0f;
                if (window->KeyHold(GLFW_KEY_W)) translateY -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_S)) translateY += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_A)) translateX += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_D)) translateX -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_R)) translateZ -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_F)) translateZ += speed * deltaTime;
            }
        }
        for (const auto& obs2Pos : obs2Positions) {
            float distanceXZ = glm::distance(glm::vec2(translateX, translateZ), glm::vec2(obs2Pos.x, obs2Pos.z));

            // h obstacol
            float obsH = 1.1f;

            if (distanceXZ < treeRadius && translateY >= obs2Pos.y && translateY <= obs2Pos.y + obsH) {
                /*std::cout << "Collision with tree at: "
                    << treePos.x << ", "
                    << treePos.y << ", "
                    << treePos.z << std::endl;*/
                    /* { if (translateY < 2.0f) {
                        translateY = 2.0f;
                        velocityY = 2.0f; // Oprește viteza dacă drona atinge solul
                    }
                    // Revenire la poziția anterioară
                    if (window->KeyHold(GLFW_KEY_W)) thrust += 5.0f * deltaTime; // Crește propulsia
                    if (window->KeyHold(GLFW_KEY_S)) thrust -= 5.0f * deltaTime; // Reduce propulsia
                    }*/
                    // Limitează thrust pentru a evita valori extreme
                //if (thrust < 0.0f) thrust = 0.0f;
                if (window->KeyHold(GLFW_KEY_W)) translateY -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_S)) translateY += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_A)) translateX += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_D)) translateX -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_R)) translateZ -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_F)) translateZ += speed * deltaTime;
            }
        }

        // Zona porților
        //1
        glm::vec3 gate1Min(-18.5f, 0.0f, 17.5f);
        glm::vec3 gate1Max(-17.5f, 2.5f, 18.5f);

        //2
        glm::vec3 gate2Min(11.5f, 0.0f, 11.5f);
        glm::vec3 gate2Max(12.5f, 2.5f, 12.5f);

        //3
        glm::vec3 gate3Min(-6.5f, 0.0f, 5.5f);
        glm::vec3 gate3Max(-5.5f, 2.5f, 6.5f);

        //4
        glm::vec3 gate4Min(-0.5f, 0.0f, -0.5f);
        glm::vec3 gate4Max(0.5f, 2.2f, 0.5f);

        //5
        glm::vec3 gate5Min(5.5f, 0.0f, -5.5f);
        glm::vec3 gate5Max(-6.5f, 2.5f, -6.5f);

        //6
        glm::vec3 gate6Min(-12.5f, 0.0f, -11.5f);
        glm::vec3 gate6Max(-11.5f, 1.0f, -12.5f);

        //7
        glm::vec3 gate7Min(17.5f, 0.0f, -17.5f);
        glm::vec3 gate7Max(18.5f, 2.5f, 18.5f);

        // Verificare coliziune pentru poarta 1
        if (!hasPassedGate1) {
            if (translateX >= gate1Min.x && translateX <= gate1Max.x &&
                translateY >= gate1Min.y && translateY <= gate1Max.y &&
                translateZ >= gate1Min.z && translateZ <= gate1Max.z)
            {
                hasPassedGate1 = true;
                std::cout << "Poarta 1 a fost trecuta!" << std::endl;
            }
        }

        // Verificare coliziune pentru poarta 2 (doar dacă poarta 1 a fost trecută)
        if (hasPassedGate1 && !hasPassedGate2) {
            if (translateX >= gate2Min.x && translateX <= gate2Max.x &&
                translateY >= gate2Min.y && translateY <= gate2Max.y &&
                translateZ >= gate2Min.z && translateZ <= gate2Max.z)
            {
                hasPassedGate2 = true;
                std::cout << "Poarta 2 a fost trecuta!" << std::endl;
            }
        }

        // Blocare trecere prin poarta 2 dacă nu a fost trecută poarta 1
        if (!hasPassedGate1) {
            if (translateX >= gate2Min.x && translateX <= gate2Max.x &&
                translateY >= gate2Min.y && translateY <= gate2Max.y &&
                translateZ >= gate2Min.z && translateZ <= gate2Max.z)
            {
                std::cout << "Nu poti trece prin Poarta 2 inainte de Poarta 1!" << std::endl;

                if (window->KeyHold(GLFW_KEY_A)) translateX += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_D)) translateX -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_R)) translateZ -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_F)) translateZ += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_Y)) translateY -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_S)) translateY += speed * deltaTime;
            }
        }
        // Verificare coliziune pentru poarta 3 (doar dacă poarta 2 a fost trecută)
        if (hasPassedGate2 && !hasPassedGate3) {
            if (translateX >= gate3Min.x && translateX <= gate3Max.x &&
                translateY >= gate3Min.y && translateY <= gate3Max.y &&
                translateZ >= gate3Min.z && translateZ <= gate3Max.z)
            {
                hasPassedGate3 = true;
                std::cout << "Poarta 3 a fost trecuta!" << std::endl;
            }
        }

        // Blocare trecere prin poarta 3 dacă nu a fost trecută poarta 2
        if (!hasPassedGate2) {
            if (translateX >= gate3Min.x && translateX <= gate3Max.x &&
                translateY >= gate3Min.y && translateY <= gate3Max.y &&
                translateZ >= gate3Min.z && translateZ <= gate3Max.z)
            {
                std::cout << "Nu poti trece prin Poarta 3 inainte de Poarta 2!" << std::endl;

                if (window->KeyHold(GLFW_KEY_A)) translateX += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_D)) translateX -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_R)) translateZ -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_F)) translateZ += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_Y)) translateY -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_S)) translateY += speed * deltaTime;
            }
        }
        // Verificare coliziune pentru poarta 4 (doar dacă poarta 3 a fost trecută)
        if (hasPassedGate3 && !hasPassedGate4) {
            if (translateX >= gate4Min.x && translateX <= gate4Max.x &&
                translateY >= gate4Min.y && translateY <= gate4Max.y &&
                translateZ >= gate4Min.z && translateZ <= gate4Max.z)
            {
                hasPassedGate4 = true;
                std::cout << "Poarta 4 a fost trecuta!" << std::endl;
            }
        }

        // Blocare trecere prin poarta 4 dacă nu a fost trecută poarta 3
        if (!hasPassedGate3) {
            if (translateX >= gate4Min.x && translateX <= gate4Max.x &&
                translateY >= gate4Min.y && translateY <= gate4Max.y &&
                translateZ >= gate4Min.z && translateZ <= gate4Max.z)
            {
                std::cout << "Nu poti trece prin Poarta 4 înainte de Poarta 3!" << std::endl;

                if (window->KeyHold(GLFW_KEY_A)) translateX += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_D)) translateX -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_R)) translateZ -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_F)) translateZ += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_Y)) translateY -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_S)) translateY += speed * deltaTime;
            }
        }
        // Verificare coliziune pentru poarta 5 (doar dacă poarta 4 a fost trecută)
        if (hasPassedGate4 && !hasPassedGate5) {
            if (translateX >= gate5Min.x && translateX <= gate5Max.x &&
                translateY >= gate5Min.y && translateY <= gate5Max.y &&
                translateZ >= gate5Min.z && translateZ <= gate5Max.z)
            {
                hasPassedGate5 = true;
                std::cout << "Poarta 5 a fost trecuta!" << std::endl;
            }
        }

        // Blocare trecere prin poarta 5 dacă nu a fost trecută poarta 4
        if (!hasPassedGate4) {
            if (translateX >= gate5Min.x && translateX <= gate4Max.x &&
                translateY >= gate5Min.y && translateY <= gate4Max.y &&
                translateZ >= gate5Min.z && translateZ <= gate4Max.z)
            {
                std::cout << "Nu poti trece prin Poarta 5 inainte de Poarta 4!" << std::endl;

                if (window->KeyHold(GLFW_KEY_A)) translateX += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_D)) translateX -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_R)) translateZ -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_F)) translateZ += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_Y)) translateY -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_S)) translateY += speed * deltaTime;
            }
        }
        // Verificare coliziune pentru poarta 6 (doar dacă poarta 5 a fost trecută)
        if (hasPassedGate5 && !hasPassedGate5) {
            if (translateX >= gate6Min.x && translateX <= gate6Max.x &&
                translateY >= gate6Min.y && translateY <= gate6Max.y &&
                translateZ >= gate6Min.z && translateZ <= gate6Max.z)
            {
                hasPassedGate6 = true;
                std::cout << "Poarta 6 a fost trecuta!" << std::endl;
            }
        }

        // Blocare trecere prin poarta 6 dacă nu a fost trecută poarta 5
        if (!hasPassedGate4) {
            if (translateX >= gate6Min.x && translateX <= gate6Max.x &&
                translateY >= gate6Min.y && translateY <= gate6Max.y &&
                translateZ >= gate6Min.z && translateZ <= gate6Max.z)
            {
                std::cout << "Nu poti trece prin Poarta 6 inainte de Poarta 5!" << std::endl;

                if (window->KeyHold(GLFW_KEY_A)) translateX += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_D)) translateX -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_R)) translateZ -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_F)) translateZ += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_Y)) translateY -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_S)) translateY += speed * deltaTime;
            }
        }
        // Verificare coliziune pentru poarta 7 (doar dacă poarta 6 a fost trecută)
        if (hasPassedGate6 && !hasPassedGate7) {
            if (translateX >= gate7Min.x && translateX <= gate7Max.x &&
                translateY >= gate7Min.y && translateY <= gate7Max.y &&
                translateZ >= gate7Min.z && translateZ <= gate7Max.z)
            {
                hasPassedGate7 = true;
                std::cout << "Poarta 7 a fost trecuta!" << std::endl;
            }
        }

        // Blocare trecere prin poarta 7 dacă nu a fost trecută poarta 6
        if (!hasPassedGate6) {
            if (translateX >= gate7Min.x && translateX <= gate7Max.x &&
                translateY >= gate7Min.y && translateY <= gate7Max.y &&
                translateZ >= gate7Min.z && translateZ <= gate7Max.z)
            {
                std::cout << "Nu poti trece prin Poarta 7 inainte de Poarta 6!" << std::endl;

                if (window->KeyHold(GLFW_KEY_A)) translateX += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_D)) translateX -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_R)) translateZ -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_F)) translateZ += speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_Y)) translateY -= speed * deltaTime;
                if (window->KeyHold(GLFW_KEY_S)) translateY += speed * deltaTime;
            }
        }
        glm::vec3 finishAreaMin = glm::vec3(18.0f, 0.0f, -24.0f); // Colțul minim al box-ului de finish
        glm::vec3 finishAreaMax = glm::vec3(24.0f, 2.0f, -18.0f);  // Colțul maxim al box-ului de finish

        // Verifica daca drona a ajuns in zona de finish 
        if (hasPassedGate7 && !hasFinished) {
            if (translateX >= finishAreaMin.x && translateX <= finishAreaMax.x &&
                translateY >= finishAreaMin.y && translateY <= finishAreaMax.y &&
                translateZ >= finishAreaMin.z && translateZ <= finishAreaMax.z)
            {
                hasFinished = true;

                // Calculează timpul scurs de la început
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration<float>(currentTime - startTime).count();

                std::cout << "Finish! Time elapsed: " << elapsedTime << " seconds" << std::endl;
            }
        }
        if (!hasPassedGate7) {
            if (translateX >= finishAreaMin.x && translateX <= finishAreaMax.x &&
                translateY >= finishAreaMin.y && translateY <= finishAreaMax.y &&
                translateZ >= finishAreaMin.z && translateZ <= finishAreaMax.z)
            {
                hasFinished = false;
                std::cout << "Nu ai trecut prin toate portile!" << std::endl;

            }
        }
    }

}


void Lab5::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections

}


void Lab5::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0)
        {
            renderCameraTarget = false;
            // Rotate the camera in First-person mode around OX and OY using deltaX and deltaY
            // Use the sensitivity variables for setting up the rotation speed
            camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
            camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
        }

        if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL)
        {
            renderCameraTarget = true;
            // Rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
            // Use the sensitivity variables for setting up the rotation speed
            camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
            camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
        }
    }
}


void Lab5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab5::OnWindowResize(int width, int height)
{
}