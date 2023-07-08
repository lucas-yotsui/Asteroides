#ifndef _JOGADOR_
#define _JOGADOR_

#include <entidade.h>
#include <cmath>

namespace trabalho	{
	class Jogador:public Entidade	{
		private:
			bool				cima;
			bool				baixo;
			bool				direita;
			bool				esquerda;
			bool				atirando;
			bool				overheat;
			float				tempoAtirando;
			float				tempoCooldown;

			sf::Vector2f		direcao;
			sf::Clock			tempoDesdeUltimoHit;
			sf::RectangleShape	barraCooldown;
			sf::RectangleShape	barraOverheat;

		public:
			Jogador(float limX, float limY);
			void 				processaInputsDoUsuario(sf::Keyboard::Key tecla, bool pressionada);
			void 				processaInputsDoUsuario(sf::Mouse::Button botao, bool pressionada);
			void 				atualiza(float deltaTempo);
			void 				setDirecao(const sf::Vector2f& d);
			float 				falaTempo();
			void				zeraTimer();
			bool				getAtirando();
			bool 				getOverheated();
			sf::RectangleShape	getBarraCooldown();
			sf::RectangleShape	getBarraOverheat();
	};
}

#endif