#include "smokeParticle.h"
#include "Math.h"
#include "Application.h"

// SmokeParticle
#define SMOKE_MAX_LIFETIME 1.2f
#define SMOKE_MIN_SPEED  40
#define SMOKE_MAX_SPEED  80
#define SMOKE_MIN_SIZE     0.2f
#define SMOKE_MAX_SIZE     0.8f
#define SMOKE_MIN_ANGLE    (1.0f)
#define SMOKE_MAX_ANGLE    (1.8f)

smokeParticle::smokeParticle(GameState* state, Entity* handle) : Entity(state,false),_handle(handle)
{
    Load(state->getApp()->gettextureManager().Get("Content/smoke.png"));
    float size = math::random(SMOKE_MIN_SIZE, SMOKE_MAX_SIZE);
    GetSprite().setScale(size, size);
    base_speed = math::random(SMOKE_MIN_SPEED, SMOKE_MAX_SPEED);

	float angle = math::to_rad(_handle->GetSprite().getRotation());

	float minAngle = angle - 0.5;

	float maxAngle = angle + 0.5;

	float newAngle = math::random(minAngle, maxAngle);

    vspeed_.x = -std::cos(newAngle) * base_speed;
    vspeed_.y = -std::sin(newAngle) * base_speed;

    timer_ = math::random(0.f, SMOKE_MAX_LIFETIME);

	float rad = math::to_rad(_handle->GetSprite().getRotation());
		
	sf::Vector2f offset = _handle->GetSprite().getPosition();

	float test = 0;

	offset.x += -test*cos(rad);
	offset.y += -test*sin(rad);

	GetSprite().setPosition(offset.x, offset.y);
}


void smokeParticle::Update(float frametime)
{
    timer_ += frametime;
    float size = GetSprite().getScale().x;
    size += frametime * 0.5;
    GetSprite().setScale(size, size);
    if (timer_ >= SMOKE_MAX_LIFETIME)
    {
		alive = false;
			
    }

	if(GetPosition().x < 0) { alive = false; }
	if(GetPosition().y < 0) { alive = false; }

	if(GetPosition().x > _state->getApp()->GetWidth()) { alive = false; }
	if(GetPosition().y > _state->getApp()->GetHeight()) { alive = false; }


    GetSprite().move(vspeed_.x * frametime, vspeed_.y * frametime);
    GetSprite().setColor(sf::Color(255, 255, 255, (sf::Uint8) (255 - 255 * timer_ / SMOKE_MAX_LIFETIME)));
}