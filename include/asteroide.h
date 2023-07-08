#ifndef _ASTEROIDE_
#define _ASTEROIDE_

#include <entidade.h>
#include <jogador.h>
#include <random>
#include <memory>
#include <vector>

namespace trabalho {
	class Asteroide:public Entidade	{
		private:
			float tempoDesdeUltimaColisao;
		public:
			Asteroide(float limX, float limY);
			void			trocaDirecao(Asteroide& a2);
			void			trocaDirecao(Jogador& j);
			void			atualiza(float deltaTempo);
	};
}

#endif