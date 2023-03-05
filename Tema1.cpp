#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
    txCorp = tyCorp = angCorp = txAripa1 = tyAripa1 = txAripa2 = txCap = tyCap =
        tyAripa2 = angAripa1 = angAripa2 = angCioc = txCioc = tyCioc = angCorp = 
        txRata = tyRata = angRata = txHitBox = tyHitBox = 0;
    directieX = directieY = 1;
    duckSpeed = 0;
    hitBoxSize = 160;
    showHitBox = false;
    circleSmoothness = 50;
    baseSpeed = 0;
    modelMatrix = glm::mat3(1);
    shot = escape = falling = onEndScreen = restart = specialDuck = false;
    timeAlive = timePlayed = 0;
    baseScore = 5;
    timeDuckOnScreen = 6;
    rateGenerate = vieti = gloante = 0;
    scor = 0;
}


Tema1::~Tema1()
{
}

void Tema1::GenereazaRata(int mode) {

    if (mode == 1) {
        txCorp = float(rand() % (window->GetResolution().x - 200) + 100);
        tyCorp = 100;
        angCorp = float((M_PI * 500 - rand() % (int)(M_PI * 1000)) / 1000);
        if (angCorp < 0.4f && angCorp > 0.0f) angCorp += 0.4f;
        if (angCorp < 0.0f && angCorp > -0.4f) angCorp -= 0.4f;
        if (angCorp > M_PI / 2 - 0.4f) angCorp -= 0.4f;
        if (angCorp < -M_PI / 2 + 0.4f) angCorp += 0.4f;
        directieX = (angCorp > 0.0f) ? -1 : 1;
        directieY = 1;
        ++rateGenerate;
    }
    else if (mode == 0) {
        txCorp = window->GetResolution().x / 2.0f;
        tyCorp = window->GetResolution().y / 2.0f;
        angCorp = float(- M_PI / 4);
        directieX = 1;
        directieY = 1;
    }
    else {
        txCorp = 0;
        tyCorp = 0;
        angCorp = float(- atan(16.0 / 9));
        directieX = 1;
        directieY = 1;
    }

    Mesh* Corp = object2D::CreateTriangle("corp", glm::vec3(txCorp, tyCorp, 0), 100, glm::vec3(0.58, 0.3, 0), true);
    AddMeshToList(Corp);

    txAripa1 = txCorp + 30;
    tyAripa1 = tyCorp;
    angAripa1 = float(- M_PI / 2 + 0.3);

    Mesh* Aripa1 = object2D::CreateTriangle("aripa1", glm::vec3(txAripa1, tyAripa1, 0), 50, glm::vec3(0.58, 0.3, 0), true);
    AddMeshToList(Aripa1);

    txAripa2 = txCorp - 30;
    tyAripa2 = tyCorp;
    angAripa2 = float(M_PI / 2 - 0.3);

    Mesh* Aripa2 = object2D::CreateTriangle("aripa2", glm::vec3(txAripa2, tyAripa2, 0), 50, glm::vec3(0.58, 0.3, 0), true);
    AddMeshToList(Aripa2);

    txCap = txCorp;
    tyCap = tyCorp + 90;

    Mesh* Cap = object2D::CreateCircle("cap", glm::vec3(txCap, tyCap, 0), 30, circleSmoothness, glm::vec3(0, 0.4, 0), true);
    AddMeshToList(Cap);

    txCioc = txCap;
    tyCioc = tyCap + 25;
    angCioc = 0;

    Mesh* Cioc = object2D::CreateTriangle("cioc", glm::vec3(txCioc, tyCioc, 0), 40, glm::vec3(1, 1, 0), true);
    AddMeshToList(Cioc);

    txHitBox = txCorp;
    tyHitBox = tyCorp;

    Mesh* Hitbox = object2D::CreateCircle("hitbox", glm::vec3(txHitBox, tyHitBox, 0), hitBoxSize, circleSmoothness, glm::vec3(1, 0, 0), false);
    AddMeshToList(Hitbox);

    txRata = tyRata = angRata = 0;
   
}

void Tema1::GenereazaUI() {
        Mesh* Viata1 = object2D::CreateCircle("viata1", glm::vec3(30, window->GetResolution().y - 30, 0), 17, circleSmoothness, glm::vec3(1, 0, 0), true);
        AddMeshToList(Viata1);

        Mesh* Viata2 = object2D::CreateCircle("viata2", glm::vec3(70, window->GetResolution().y - 30, 0), 17, circleSmoothness, glm::vec3(1, 0, 0), true);
        AddMeshToList(Viata2);

        Mesh* Viata3 = object2D::CreateCircle("viata3", glm::vec3(110, window->GetResolution().y - 30, 0), 17, circleSmoothness, glm::vec3(1, 0, 0), true);
        AddMeshToList(Viata3);

        Mesh* Glont1 = object2D::CreateRectangle("glont1", glm::vec3(30, window->GetResolution().y - 70, 0), 30, 10, glm::vec3(0.85, 0.64, 0.125), true);
        AddMeshToList(Glont1);

        Mesh* Glont2 = object2D::CreateRectangle("glont2", glm::vec3(70, window->GetResolution().y - 70, 0), 30, 10, glm::vec3(0.85, 0.64, 0.125), true);
        AddMeshToList(Glont2);

        Mesh* Glont3 = object2D::CreateRectangle("glont3", glm::vec3(110, window->GetResolution().y - 70, 0), 30, 10, glm::vec3(0.85, 0.64, 0.125), true);
        AddMeshToList(Glont3);

        Mesh* BaraScor = object2D::CreateRectangle("BaraScor", glm::vec3(window->GetResolution().x - 200, window->GetResolution().y - 50, 0), 300, 50,
            glm::vec3(0, 0, 0.54), false);
        AddMeshToList(BaraScor);

        Mesh* Iarba = object2D::CreateRectangle("iarba", glm::vec3(window->GetResolution().x / 2, 50, 0), (float)window->GetResolution().x, 100,
            glm::vec3(0, 0.6, 0.09), true);
        AddMeshToList(Iarba);
}

void Tema1::GenereazaScorNou() {
    if (scor > 500) scor = 500;
    Mesh* Scor = object2D::CreateRectangle("Scor", glm::vec3(window->GetResolution().x - 200 - 145 * (1 - scor / 500.0f),
        window->GetResolution().y - 50, 0), (290 * scor / 500.0f), 42, glm::vec3(0.67, 0.84, 0.9), true);
    AddMeshToList(Scor);
}

void Tema1::AfiseazaRata() {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(txRata, tyRata) *
        transform2D::Translate(txCorp, tyCorp) *
        transform2D::Rotate(angRata + angCorp) *
        transform2D::Translate(-txCorp, -tyCorp);
    RenderMesh2D(meshes["cap"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(txRata, tyRata) *
        transform2D::Translate(txCorp, tyCorp) *
        transform2D::Rotate(angRata + angCorp) *
        transform2D::Translate(-txCorp, -tyCorp);
    RenderMesh2D(meshes["corp"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(txRata, tyRata) *
        transform2D::Translate(txCorp, tyCorp) *
        transform2D::Rotate(angRata + angCorp) *
        transform2D::Translate(-txCorp, -tyCorp) *
        transform2D::Translate(txCioc, tyCioc) *
        transform2D::Rotate(angCioc) *
        transform2D::Translate(-txCioc, -tyCioc);
    RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(txRata, tyRata) *
        transform2D::Translate(txCorp, tyCorp) *
        transform2D::Rotate(angRata + angCorp) *
        transform2D::Translate(-txCorp, -tyCorp) *
        transform2D::Translate(txAripa1, tyAripa1) *
        transform2D::Rotate(angAripa1) *
        transform2D::Translate(-txAripa1, -tyAripa1);
    RenderMesh2D(meshes["aripa1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(txRata, tyRata) *
        transform2D::Translate(txCorp, tyCorp) *
        transform2D::Rotate(angRata + angCorp) *
        transform2D::Translate(-txCorp, -tyCorp) *
        transform2D::Translate(txAripa2, tyAripa2) *
        transform2D::Rotate(angAripa2) *
        transform2D::Translate(-txAripa2, -tyAripa2);
    RenderMesh2D(meshes["aripa2"], shaders["VertexColor"], modelMatrix);

    if (showHitBox) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(txRata, tyRata);
        RenderMesh2D(meshes["hitbox"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::AfiseazaUI() {

    modelMatrix = glm::mat3(1);
    if (vieti > 0) RenderMesh2D(meshes["viata1"], shaders["VertexColor"], modelMatrix);
    if (vieti > 1) RenderMesh2D(meshes["viata2"], shaders["VertexColor"], modelMatrix);
    if (vieti > 2) RenderMesh2D(meshes["viata3"], shaders["VertexColor"], modelMatrix);
    if (gloante > 0) RenderMesh2D(meshes["glont1"], shaders["VertexColor"], modelMatrix);
    if (gloante > 1) RenderMesh2D(meshes["glont2"], shaders["VertexColor"], modelMatrix);
    if (gloante > 2) RenderMesh2D(meshes["glont3"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["BaraScor"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["Scor"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["iarba"], shaders["VertexColor"], modelMatrix);
}

void Tema1::MiscaRata(float deltaTimeSeconds) {
    if (angAripa1 > -M_PI / 2 - 0.3) angAripa1 -= deltaTimeSeconds;
    else angAripa1 = float(- M_PI / 2 + 0.3);

    if (angAripa2 < M_PI / 2 + 0.3) angAripa2 += deltaTimeSeconds;
    else angAripa2 = float(M_PI / 2 - 0.3);

    if (directieX == 1) {
        if (txRata + txCioc + 80 + deltaTimeSeconds * duckSpeed * abs(sin(angRata + angCorp)) <= window->GetResolution().x ||
            (specialDuck && txRata + 80 <= window->GetResolution().x)) {
            txRata += deltaTimeSeconds * duckSpeed * abs(sin(angRata + angCorp));
        }
        else {
            directieX = -1;
            if (directieY == -1) {
                angRata -= float(2 * (angCorp + angRata));
            }
            else {
                angRata += float(- 2 * (angCorp + angRata));
            }
        }
    }
    else {
        if (txRata + txCioc - 80 - deltaTimeSeconds * duckSpeed * abs(sin(angRata + angCorp)) >= 0 ||
            (specialDuck && txRata - 80 >= 0)) {
            txRata -= deltaTimeSeconds * duckSpeed * abs(sin(angRata + angCorp));

        }
        else {

            directieX = 1;
            if (directieY == -1) {
                angRata += float(- 2 * (angCorp + angRata));
            }
            else {
                angRata -= float(2 * (angCorp + angRata));
            }
        }
    }

    if (directieY == 1) {
        if (escape || tyRata + tyCioc - 50 + deltaTimeSeconds * duckSpeed * abs(cos(angRata + angCorp)) <= window->GetResolution().y ||
            (specialDuck && tyRata + 80 * 9.0 / 16 <= window->GetResolution().y)) {
            tyRata += deltaTimeSeconds * duckSpeed * abs(cos(angRata + angCorp));
        }
        else {
            directieY = -1;
            if (directieX == -1) {
                angRata += float(M_PI - 2 * (angCorp + angRata));
            }
            else {
                angRata -= float(M_PI + 2 * (angCorp + angRata));
            }
        }
    }
    else {
        if (falling || tyRata + tyCioc - 200 - deltaTimeSeconds * duckSpeed * abs(cos(angRata + angCorp)) >= 0 ||
            (specialDuck && tyRata - 80 * 9.0 / 16 >= 0)) {
            tyRata -= deltaTimeSeconds * duckSpeed * abs(cos(angRata + angCorp));
        }
        else {
            directieY = 1;
            if (directieX == 1) {
                angRata += float(- M_PI - 2 * (angCorp + angRata));
            }
            else {
                angRata -= float(- M_PI + 2 * (angCorp + angRata));
            }
        }
    }
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    vieti = gloante = 0; 
    scor = 0;
    baseSpeed = 300;
    duckSpeed = 0;
    timePlayed = 0;
    specialDuck = restart = onEndScreen = false;
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    if (vieti == 0 && !escape) {
        if (restart) {
            vieti = 3;
            gloante = 3;
            duckSpeed = baseSpeed;
            scor = restart = rateGenerate = 0;
            shot = escape = falling = false;
            timeAlive = 0;
            timePlayed = 0;
            onEndScreen = 0;
            specialDuck = false;
            GenereazaRata(1);
            GenereazaUI();
            GenereazaScorNou();
        }
        else {
            if (!onEndScreen) {
                duckSpeed = baseSpeed;
                if (scor >= 500) {
                    GenereazaRata(2);
                    printf("You win! Time : ");
                    int minutes = int(timePlayed / 60), seconds = int(timePlayed) % 60,
                        miliseconds = int(timePlayed * 1000) % 1000;
                    if (minutes < 10) printf("0");
                    printf("%d : ", minutes);

                    if (seconds < 10) printf("0");
                    printf("%d : ", seconds);

                    if (miliseconds < 100) printf("0");
                    if (miliseconds < 10) printf("0");
                    printf("%d  Try to beat 00 : 37 : 774 !\n", miliseconds);
                    specialDuck = true;
                }
                else {
                    if (tyRata > 0) {
                        printf("You Lose! ");
                    }
                    printf("Click anywhere to play\n");
                    GenereazaRata(0);
                }
                onEndScreen = 1;
            }
            MiscaRata(deltaTimeSeconds);
            AfiseazaRata();
            return;
        }
    }
    timeAlive += deltaTimeSeconds;
    timePlayed += deltaTimeSeconds;
    if (shot) {
        directieY = -1;
        angRata = float(M_PI - angCorp);
        shot = 0;
        falling = 1;
    }
    if (falling && tyRata + 200 <= 0) {
        falling = 0;
        timeAlive = 0;
        scor += baseScore * (duckSpeed / float(baseSpeed));
        GenereazaScorNou();
        GenereazaRata(1);
        gloante = 3;
    }
    if ((timeAlive > timeDuckOnScreen && !escape && !falling) || (gloante == 0 && !escape && !falling)) {
        escape = 1;
        directieY = 1;
        angRata = -angCorp;
    }
    if (escape && tyRata - 30 >= window->GetResolution().y) {
        escape = 0;
        timeAlive = 0;
        --vieti;
        if (vieti) GenereazaRata(1);
        gloante = 3;
    }

    if (rateGenerate > 1 && rateGenerate % 5 == 1) {
        duckSpeed += 100;
        rateGenerate -= 5;
    }
    if (vieti || (!vieti && escape)) {
        MiscaRata(deltaTimeSeconds);
        AfiseazaUI();
        AfiseazaRata();
        if (scor >= 500) {
            vieti = 0;
        }
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_H) {
        showHitBox = !showHitBox;
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event

    if (button == GLFW_MOUSE_BUTTON_2) {
        if (vieti == 0 && !escape) {
            restart = 1;
            return;
        }
        if (shot || escape || falling) {
            return;
        }
        int x = mouseX, y = window->GetResolution().y - mouseY;
        float a = (txHitBox + txRata), b = tyHitBox + tyRata;

        float dist = sqrt((x - a) * (x - a) + (y - b) * (y - b));

        if (dist <= hitBoxSize) {
            shot = true;
        }
        --gloante;
    }
       
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
