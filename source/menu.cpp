#include <menu.h>

trabalho::Menu::Menu():janela{sf::VideoMode(850, 470), "Escolhe tua dificuldade ai ze"}, qtdAtualAsteroides(0)	{
	fonte.loadFromFile("assets/fonts/OpenSans-Bold.ttf");

	nome.setFont(fonte);
	nome.setString("ASTEROIDES");
	nome.setOrigin(nome.getGlobalBounds().left + (nome.getGlobalBounds().width / 2), nome.getGlobalBounds().top + (nome.getGlobalBounds().height/ 2));
	nome.setPosition(427, 120);
	nome.setScale(2,2);

	facil.setFont(fonte);
	facil.setString("FACIL");
	facil.setOrigin(facil.getGlobalBounds().left + (facil.getGlobalBounds().width / 2), facil.getGlobalBounds().top + (facil.getGlobalBounds().height / 2));
	facil.setPosition(427, 240);
	facil.setScale(1.5, 1.5);

	medio.setFont(fonte);
	medio.setString("MEDIO");
	medio.setOrigin(medio.getGlobalBounds().left + (medio.getGlobalBounds().width / 2), medio.getGlobalBounds().top + (medio.getGlobalBounds().height / 2));
	medio.setPosition(427, 260 + facil.getGlobalBounds().height);
	medio.setScale(1.5, 1.5);

	dificil.setFont(fonte);
	dificil.setString("DIFICIL");
	dificil.setOrigin(dificil.getGlobalBounds().left + (dificil.getGlobalBounds().width / 2), dificil.getGlobalBounds().top + (dificil.getGlobalBounds().height / 2));
	dificil.setPosition(427, 280 + 2 * medio.getGlobalBounds().height);
	dificil.setScale(1.5, 1.5);

	for(unsigned int i = 0; i < 7; i++)	{
		asteroidesFundo.push_back(new Asteroide{800, 420});

		for(unsigned int j = 0; j < i; j++)	{
			if(asteroidesFundo.back()->getHitbox().intersects(asteroidesFundo[j]->getHitbox()))	{
				delete asteroidesFundo.back();
				asteroidesFundo.erase(asteroidesFundo.end() - 1);
				i--;
				qtdAtualAsteroides--;

				break;
			}
		}

		qtdAtualAsteroides++;
	}
}

int trabalho::Menu::rodaMenu()	{
	sf::Clock clock;
	sf::Time tempoDesdeUltimaAtualizacao = sf::Time::Zero;
	int retorno = 0;
	
	while(janela.isOpen())	{
		clock.restart();

		retorno = processaEventos();

		if(retorno)	{
			break;
		}

		atualiza();

		renderiza();

		tempoDesdeUltimaAtualizacao = clock.getElapsedTime();

		if(tempoDesdeUltimaAtualizacao.asSeconds() < tempoPorFrame.asSeconds())	{
			sf::sleep(tempoPorFrame - tempoDesdeUltimaAtualizacao);
		}
	}

	return retorno;
}

trabalho::Menu::~Menu()	{
	asteroidesFundo.clear();
}

int trabalho::Menu::processaEventos()	{
	sf::Event evento;

	while(janela.pollEvent(evento))	{
		if(evento.type == sf::Event::MouseButtonPressed)	{
			return processaInputs(evento.mouseButton.button);
		}

		if(evento.type == sf::Event::Closed)	{
			janela.close();
			return -1;
		}
	}

	return 0;
}

int trabalho::Menu::processaInputs(sf::Mouse::Button botao)	{
	if(botao == sf::Mouse::Button::Left)	{
		if(facil.getFillColor() == sf::Color::Yellow)	{
			return 1;
		}

		if(medio.getFillColor() == sf::Color::Yellow)	{
			return 2;
		}
		
		if(dificil.getFillColor() == sf::Color::Yellow)	{
			return 3;
		}
	}

	return 0;
}

void trabalho::Menu::atualiza()	{
	for(unsigned int i = 0; i < qtdAtualAsteroides; i++)	{
		for(unsigned int j = i + 1; j < qtdAtualAsteroides; j++)	{
			if(asteroidesFundo[i]->getHitbox().intersects(asteroidesFundo[j]->getHitbox()))	{
				asteroidesFundo[i]->trocaDirecao(*asteroidesFundo[j]);
			}
		}
	}

	for(unsigned int i = 0; i < qtdAtualAsteroides; i++)	{
		asteroidesFundo[i]->atualiza(tempoPorFrame.asSeconds());
	}

	float mouseX = float(mouse.getPosition(janela).x);
	float mouseY = float(mouse.getPosition(janela).y);
	float esquerda = facil.getGlobalBounds().left;
	float direita = esquerda + facil.getGlobalBounds().width;
	float cima = facil.getGlobalBounds().top;
	float baixo = cima + facil.getGlobalBounds().height;
	
	if(mouseX > esquerda &&	mouseX < direita &&	mouseY > cima && mouseY < baixo)	{
		facil.setFillColor(sf::Color::Yellow);
	} else {
		facil.setFillColor(sf::Color::White);
	}

	esquerda = medio.getGlobalBounds().left;
	direita = esquerda + medio.getGlobalBounds().width;
	cima = medio.getGlobalBounds().top;
	baixo = cima + medio.getGlobalBounds().height;

	if(mouseX > esquerda &&	mouseX < direita &&	mouseY > cima && mouseY < baixo)	{
		medio.setFillColor(sf::Color::Yellow);
	} else {
		medio.setFillColor(sf::Color::White);
	}

	esquerda = dificil.getGlobalBounds().left;
	direita = esquerda + dificil.getGlobalBounds().width;
	cima = dificil.getGlobalBounds().top;
	baixo = cima + dificil.getGlobalBounds().height;

	if(mouseX > esquerda &&	mouseX < direita &&	mouseY > cima && mouseY < baixo)	{
		dificil.setFillColor(sf::Color::Yellow);
	} else {
		dificil.setFillColor(sf::Color::White);
	}

}

void trabalho::Menu::renderiza()	{
	janela.clear();

	janela.draw(nome);

	janela.draw(facil);
	janela.draw(medio);
	janela.draw(dificil);

	for(unsigned int i = 0; i < qtdAtualAsteroides; i++)	{
		janela.draw(*asteroidesFundo[i]);
	}

	janela.display();
}