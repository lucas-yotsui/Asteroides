#include <tiro.h>

trabalho::Tiro::Tiro(const sf::Vector2f& origem, const sf::Vector2f& alvo):velocidade(450.f){
	corpo.setRadius(2.f);
	corpo.setFillColor(sf::Color::White);
	corpo.setPosition(origem);

	setHitbox({0.f, 0.f, 2.f, 2.f});
	
	direcao = ((alvo - origem) / float(std::sqrt(std::pow((alvo - origem).x, 2) + std::pow((alvo - origem).y, 2))));
}

void trabalho::Tiro::atualiza(float deltaTempo)	{
	corpo.move(direcao * velocidade * deltaTempo);
}

void trabalho::Tiro::setHitbox(const sf::FloatRect& h)	{
	hitbox = h;
}

sf::FloatRect trabalho::Tiro::getHitbox()	{
	return corpo.getTransform().transformRect(hitbox);
}

sf::CircleShape trabalho::Tiro::getCorpo()	{
	return corpo;
}