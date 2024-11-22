#pragma once

Vector2f movementControls(float speed) {
    Vector2f velocity(0, 0);

    if (Keyboard::isKeyPressed(Keyboard::Scan::Right))
        velocity.x += speed;
    if (Keyboard::isKeyPressed(Keyboard::Scan::Left))
        velocity.x -= speed;
    if (Keyboard::isKeyPressed(Keyboard::Scan::Up))
        velocity.y -= speed;
    if (Keyboard::isKeyPressed(Keyboard::Scan::Down))
        velocity.y += speed;
    return velocity;
}