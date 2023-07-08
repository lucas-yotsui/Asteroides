#ifndef _MENU_
#define _MENU_

#include <SFML/Graphics.hpp>
#include <asteroide.h>

namespace trabalho	{
	class Menu	{
		private:
			sf::RenderWindow		janela;
			std::vector<Asteroide*>	asteroidesFundo;
			unsigned int			qtdAtualAsteroides;
			sf::Mouse				mouse;
			sf::Font				fonte;
			sf::Text				nome;
			sf::Text				facil;
			sf::Text				medio;
			sf::Text				dificil;

			int		processaEventos();
			int		processaInputs(sf::Mouse::Button botao);
			void	atualiza();
			void	renderiza();

		public:
			Menu();
			int	rodaMenu();
			~Menu();
	};
}

#endif