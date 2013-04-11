#include ""

// TextParticle
#define MESSAGE_LIFETIME   5.0
#define MESSAGE_SPEED      50

messageParticle::messageParticle(const sf::Vector2f& offset, const sf::String& text, const sf::Color& color)
{
        text_.setString(text);
        text_.setCharacterSize(12);
        text_.setColor(color);
        text_.setPosition(offset);
        text_.setFont(Resources::getFont("Ubuntu-R.ttf"));
        timer_ = 0.f;
}


bool messageParticle.cpp::OnUpdate(float frametime)
{
        timer_ += frametime;
        text_.move(0, -MESSAGE_SPEED * frametime);
        // transparence
        sf::Color color = text_.getColor();
        color.a = static_cast<sf::Uint8> (255 - 255 * timer_ / MESSAGE_LIFETIME);
        text_.setColor(color);
        return timer_ >= MESSAGE_LIFETIME;
}
