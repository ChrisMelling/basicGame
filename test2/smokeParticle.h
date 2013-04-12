#include "Entity.h"


class smokeParticle: public Entity
{
public:
        smokeParticle(GameState* state, Entity* handle);
        ~smokeParticle() { }
		virtual void Update(float frametime);
private:
        int y_offset_;
        float timer_;
        sf::Vector2f vspeed_;
		Entity* _handle;
		float base_speed;
		float angle;
};