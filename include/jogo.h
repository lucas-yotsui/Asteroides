#ifndef _FRONT_END_
#define _FRONT_END_

#include <vector>
#include <memory>
#include <fstream>
#include <jogador.h>
#include <tiro.h>
#include <asteroide.h>

namespace trabalho {
	class Jogo	{
		private:
			sf::RenderWindow						janela;
			Jogador									jogador;
			sf::Clock								tempoDesdeUltimoTiro;
			std::vector<std::shared_ptr<Asteroide>>	asteroides;
			unsigned int							qtdInicialAsteroides;
			unsigned int							qtdAtualAsteroides;
			std::vector<std::shared_ptr<Tiro>>		tiros;
			unsigned int							qtdAtualTiros;
			sf::Mouse								mouse;
			sf::Font 								fonte;
			sf::Text								fase;
			sf::Text								pontuacao;
			sf::Text 								recorde;
			unsigned int							level;
			unsigned int 							score;
			unsigned int 							highScore;
			bool									pausado;

			void	processaEventos();
			bool	atualizaJogo();
			void	renderiza();
			void	criaAsteroides(unsigned int qtd);
			void	colisaoEntreAsteroides();
			void	tiroNoAsteroide();
			void	colisaoJogador();
			void	trocaFase();
			void	fimDeJogo();

		public:
			Jogo(int dificuldade);
			void	rodaJogo();
			~Jogo();
	};
}

#endif