#include "Entity.h"

class TextParticle: public Entity
{
public:
	TextParticle(const sf::Vector2f& offset, const sf::String& text, const sf::Color& color);
	~TextParticle() {};
	bool OnUpdate(float frametime);

	inline void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text_, states);
	}
private:
	sf::Text text_;
	float timer_;
};