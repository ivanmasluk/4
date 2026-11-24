#pragma once

#include <string>

class Building {
protected:
    int id_;
    std::string type_;
    int health_;
    int x_;
    int y_;
    int buildProgress_;
    bool completed_;

public:
    Building(int id, const std::string& type, int health, int x, int y);
    virtual ~Building() = default;

    int getId() const;
    const std::string& getType() const;
    int getHealth() const;
    int getX() const;
    int getY() const;
    int getBuildProgress() const;
    bool isCompleted() const;

    virtual void update();
    virtual bool canProduce() const;
};
