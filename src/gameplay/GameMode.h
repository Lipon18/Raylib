#pragma once

class Zombie;

class GameMode {
    public:
    GameMode();

    void Init();
    void Update(float dt);

    void OnZombieKilled(const Zombie* zombie);
    int GetScore() const {return m_Score;}

    private:
    int m_Score;
};