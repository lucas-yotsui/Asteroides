#ifndef _ENTIDADE_
#define _ENTIDADE_

#define tempoPorFrame (sf::seconds(1.f / 60.f))

#include <SFML/Graphics.hpp>
#include <random>

namespace trabalho	{
	class Entidade: public sf::Sprite	{
		protected:
			//Caracteristicas Fisicas da Entidade
			sf::Texture 		textura;
			sf::FloatRect		hitbox;
			sf::RectangleShape	barraDeVida;
			int 				vida;

			//Caracteristicas do Movimento da entidade
			sf::Vector2f		velocidadeAtual;
			float				maxVelocidade;
			float 				aceleracao;
			float				atrito;

			float				limJanelaX;
			float				limJanelaY;

		public:
			Entidade(float maxVel, float acel, int life, float limX, float limY);
			void 				setHitbox(const sf::FloatRect& h);
			sf::FloatRect 		getHitbox();
			sf::RectangleShape	getBarraDeVida ();
			int 				getVida();
			void 				ganhaVida();
			virtual	void		atualiza(float deltaTempo) = 0;

			bool	operator== (Entidade& e);
			void	operator-- (int);
	};
}

#endif