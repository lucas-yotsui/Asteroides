#include <entidade.h>

trabalho::Entidade::Entidade(float maxVel, float acel, int life, float limX, float limY):vida(life), maxVelocidade(maxVel), aceleracao(acel), atrito(0.95f), limJanelaX(limX), limJanelaY(limY)	{}

void trabalho::Entidade::setHitbox(const sf::FloatRect& h)	{
	hitbox = h;
}

sf::FloatRect trabalho::Entidade::getHitbox()	{
	return getTransform().transformRect(hitbox);
}

sf::RectangleShape trabalho::Entidade::getBarraDeVida ()	{
	return barraDeVida;
}

int trabalho::Entidade::getVida()	{
	return vida;
}

void trabalho::Entidade::ganhaVida()	{
	vida += 25;
}

bool trabalho::Entidade::operator== (Entidade& e)	{
	return getHitbox().intersects(e.getHitbox());
}

void trabalho::Entidade::operator-- (int)	{
	vida -= 50;
}