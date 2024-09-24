#ifndef AIComponent_H
#define AIComponent_H

#include <ECS/Components.h>
#include <game.h>

class AIComponent : public Component {
private:
    TransformComponent* transform;
    TransformComponent* ballTransform;

public:
    AIComponent(TransformComponent* b) {
        this->ballTransform = b;
    }

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
    }

    int predict(TransformComponent* ball) {
        if(ball->velocity.x == 0) ball->velocity.x = 1;
        float slope = static_cast<float> (ball->velocity.y / ball->velocity.x);
        int paddle_distance = ball->position.x - transform->position.x;
        int predicted_y = abs(slope * -(paddle_distance) + ball->position.y);
        int number_of_reflections = predicted_y / Game::HEIGHT;
        if (number_of_reflections % 2 == 0)
            predicted_y = predicted_y % Game::HEIGHT;
        else
            predicted_y = Game::HEIGHT - (predicted_y % Game::HEIGHT);
        return predicted_y;
    }

    void update() override {
        // Simple AI: Follow the ball's y position
        transform->velocity.x = 0;
        transform->velocity.y = 0;
        if(ballTransform->position.x > Game::WIDTH*3/5 && ballTransform->velocity.x > 0) {
            // Follow the ball
            if(transform->position.y < predict(ballTransform) - 2) {
                transform->velocity.y = 0.8;
            } else if (transform->position.y > predict(ballTransform) + 2) {
                transform->velocity.y = -0.8;
            }
        }
        else if(ballTransform->velocity.x <= 0) {
            // Left paddle slowly moves to the center
            if(transform->position.y + transform->height / 2 < Game::HEIGHT / 2) {
                transform->velocity.y = 0.2;
            } else if (transform->position.y + transform->height / 2 > Game::HEIGHT / 2) {
                transform->velocity.y = -0.2;
            }
        }
    }
};

#endif