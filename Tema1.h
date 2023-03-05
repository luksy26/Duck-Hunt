#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void MiscaRata(float deltaTimeSeconds);
        void GenereazaRata(int mode);
        void GenereazaUI();
        void GenereazaScorNou();
        void AfiseazaRata();
        void AfiseazaUI();

    protected:
        glm::mat3 modelMatrix;
        float txCorp, tyCorp, angCorp, txAripa1, tyAripa1, angAripa1, txAripa2, tyAripa2,
            angAripa2, txCioc, tyCioc, angCioc, txCap, tyCap, txRata, tyRata, angRata,
            txHitBox, tyHitBox, hitBoxSize, timeAlive;

        int directieX, directieY, duckSpeed, baseSpeed, circleSmoothness, rateGenerate, vieti, gloante, baseScore;
        float scor, timePlayed, timeDuckOnScreen;
        bool showHitBox, escape, shot, falling, restart, onEndScreen, specialDuck;

    };
}   // namespace m1
