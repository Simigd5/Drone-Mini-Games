#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab5/lab_camera.h"
#include "components/transform.h"

namespace m1
{
    class Lab5 : public gfxc::SimpleScene
    {
     public:
         struct ViewportArea
         {
             ViewportArea() : x(0), y(0), width(1), height(1) {}
             ViewportArea(int x, int y, int width, int height)
                 : x(x), y(y), width(width), height(height) {}
             int x;
             int y;
             int width;
             int height;
         };
        Lab5();
        ~Lab5();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        //void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderScene();

        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
        bool hasPassedGate1 = false;
        bool hasPassedGate2 = false;
        bool hasPassedGate3 = false;
        bool hasPassedGate4 = false;
        bool hasPassedGate5 = false;
        bool hasPassedGate6 = false;
        bool hasPassedGate7 = false;
     protected:
        implemented::Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        bool projectionType;
        float pitchAngle = 0.0f; // Înclinarea pe axa Ox (sus-jos)
        float yawAngle = 0.0f;   // Rotirea pe axa Oy (stânga-dreapta)
        float rollAngle = 0.0f;  // Rotirea pe axa Oz (trigonometric/anti-trigonometric)

        GLfloat right;
        GLfloat left;
        GLfloat bottom;
        GLfloat top;
        GLfloat fov;
        glm::vec3 finishAreaMin = glm::vec3(18.0f, 0.0f, -24.0f); // Colțul minim al box-ului de finish
        glm::vec3 finishAreaMax = glm::vec3(24.0f, 2.0f, -18.0f);  // Colțul maxim al box-ului de finish
        glm::vec3 pomMin = glm::vec3(5.0f, 0.0f, 5.0f); // Coordonatele minime ale pomului
        glm::vec3 pomMax = glm::vec3(6.0f, 2.0f, 6.0f); // Coordonatele maxime ale pomului
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        GLenum polygonMode;
        ViewportArea miniViewportArea;
        float rotationAngleY = 0;
        float frequency = 1.0f;
        float amplitude = 3.0f;
        float planeX, planeY;
        bool hasFinished = false; // Variabilă pentru verificarea coliziunii

        std::vector<glm::vec3> treePositions;
        std::vector<glm::vec3> conPositions;
        std::vector<glm::vec3> obs2Positions;
        // Dimensiunea (raza) pomilor
        float treeRadius = 0.8f;
        const float gravity = -9.8f; // Acceleratia gravitationala
        float velocityY = 0.0f;      // Viteza verticala pe Oy
        float thrust = 0.0f;         // Forta de propulsie generata de motoare
        float mass = 1.0f;           // Masa dronei
        glm::mat4 droneMatrix; // Matricea transformării dronei
        float pitch = 0.0f;   // Înclinarea pe axa Ox
        float yaw = 0.0f;     // Rotația pe axa Oy
        float roll = 0.0f;    // Rotația pe axa Oz

        glm::vec3 droneRotation = glm::vec3(0.0f);
    };
}   // namespace m1
