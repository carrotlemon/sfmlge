#pragma once

float moveUntilCollision(const Room& room, float start, float end, const Vector2f& pos, const Vector2f& size, bool isX) {
    float low = start;
    float high = end;
    float result = start;

    while (std::abs(high - low) > 0.01f) { // Precision threshold
        float mid = (low + high) / 2;
        Vector2f testPos = pos;
        if (isX) testPos.x += mid; // Test X movement
        else testPos.y += mid;    // Test Y movement

        if (!room.collides(testPos, size)) {
            result = mid;
            low = mid; // Move forward
        }
        else {
            high = mid; // Move backward
        }
    }

    return result;
}

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