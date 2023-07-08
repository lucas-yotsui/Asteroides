#ifndef _TIRO_
#define _TIRO_

#include <SFML/Graphics.hpp>
#include <cmath>

namespace trabalho	{
	class Tiro	{
		private:
			sf::CircleShape	corpo;
			sf::FloatRect	hitbox;
			sf::Vector2f	direcao;
			float 			velocidade;

		public:
			Tiro(const sf::Vector2f& origem, const sf::Vector2f& alvo);
			void			atualiza(float deltaTempo);
			void 			setHitbox(const sf::FloatRect& h);
			sf::FloatRect	getHitbox();
			sf::CircleShape getCorpo();
	};
}

#endif