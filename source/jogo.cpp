#include <jogo.h>
#include <iostream>

trabalho::Jogo::Jogo(int dificuldade):janela(sf::VideoMode(1920,1080), "Slk olha a pedra ai hein ze kkkkk", sf::Style::Fullscreen), jogador{1880, 1030}, qtdInicialAsteroides(15 * unsigned(dificuldade)), qtdAtualAsteroides(0), qtdAtualTiros(0), level(1), score(0), highScore(0), pausado(false)	{
	criaAsteroides(qtdInicialAsteroides);

	std::ifstream arqRecordes{"assets/recordes.txt"};
	arqRecordes >> highScore;
	arqRecordes.close();

	fonte.loadFromFile("assets/fonts/OpenSans-Bold.ttf");

	fase.setFont(fonte);
	fase.setPosition(0.f, 0.f);
	fase.setScale(0.5, 0.5);
	fase.setFillColor(sf::Color::White);
	
	pontuacao.setFont(fonte);
	pontuacao.setPosition(1800.f, 0.f);
	pontuacao.setScale(0.5, 0.5);
	pontuacao.setFillColor(sf::Color::White);

	recorde.setFont(fonte);
	recorde.setString("Recorde " + std::to_string(highScore));
	recorde.setPosition(1800.f, 20.f);
	recorde.setScale(0.5, 0.5);
	recorde.setFillColor(sf::Color::Yellow);
}

void trabalho::Jogo::rodaJogo()	{
	sf::Clock clock;
	sf::Time tempoDesdeUltimaAtualizacao = sf::Time::Zero;

	while(janela.isOpen())	{
		clock.restart();

		processaEventos();
		
		if(!pausado)	{
			if(atualizaJogo())	{
				break;
			}
		}

		renderiza();

		tempoDesdeUltimaAtualizacao = clock.getElapsedTime();

		if(tempoDesdeUltimaAtualizacao < tempoPorFrame)	{
			sf::sleep(tempoPorFrame - tempoDesdeUltimaAtualizacao);
		}
	}
}

trabalho::Jogo::~Jogo()	{
	if(score > highScore)	{
		std::ofstream arqRecordes{"recordes.txt"};
		arqRecordes << score;
		arqRecordes.close();
	}

	asteroides.clear();
	tiros.clear();
}

void trabalho::Jogo::processaEventos()	{
	sf::Event eventoTemp;

	while(janela.pollEvent(eventoTemp))	{
		switch(eventoTemp.type)	{
			case sf::Event::KeyPressed:
				if(eventoTemp.key.code == sf::Keyboard::Key::Escape)	{
					pausado = !pausado;
				}

				jogador.processaInputsDoUsuario(eventoTemp.key.code, true);
				break;
			case sf::Event::KeyReleased:
				jogador.processaInputsDoUsuario(eventoTemp.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				jogador.processaInputsDoUsuario(eventoTemp.mouseButton.button, true);
				break;
			case sf::Event::MouseButtonReleased:
				jogador.processaInputsDoUsuario(eventoTemp.mouseButton.button, false);
				break;
			case sf::Event::Closed:
				fimDeJogo();
				janela.close();
				break;
			default:
				break;
		}
	}
}

bool trabalho::Jogo::atualizaJogo()	{
	fase.setString("Fase " + std::to_string(level));
	pontuacao.setString("Pontos " + std::to_string(score));
	
	colisaoEntreAsteroides();
	tiroNoAsteroide();
	colisaoJogador();

	if(qtdAtualAsteroides == 0)	{
		trocaFase();
	}

	jogador.atualiza(tempoPorFrame.asSeconds());

	for(unsigned int i = 0; i < qtdAtualAsteroides; i++)	{
		asteroides[i]->atualiza(tempoPorFrame.asSeconds());
	}

	sf::Vector2f direcao(sf::Vector2f(mouse.getPosition(janela)) - jogador.getPosition());
	direcao = direcao / std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
	jogador.setDirecao(direcao);

	if(jogador.getAtirando() && !jogador.getOverheated() && (tempoDesdeUltimoTiro.getElapsedTime().asSeconds() > 0.25f))	{
		tiros.push_back(std::shared_ptr<Tiro>(new Tiro(jogador.getPosition(), sf::Vector2f(mouse.getPosition(janela)))));
		qtdAtualTiros++;
		tempoDesdeUltimoTiro.restart();
	}

	for(unsigned int i = 0; i < qtdAtualTiros; i++)	{
		tiros[i]->atualiza(tempoPorFrame.asSeconds());
		if(tiros[i]->getCorpo().getPosition().x > 1920 || tiros[i]->getCorpo().getPosition().x < -50 || tiros[i]->getCorpo().getPosition().y > 1080 || tiros[i]->getCorpo().getPosition().y < -50)	{
			tiros.erase(tiros.begin() + i);
			qtdAtualTiros--;
		}
	}

	if(jogador.getVida() <= 0)	{
		fimDeJogo();
		return true;
	}

	return false;
}

void trabalho::Jogo::renderiza()	{
	janela.clear();

	janela.draw(jogador);
	janela.draw(jogador.getBarraDeVida());
	janela.draw(jogador.getBarraCooldown());
	janela.draw(jogador.getBarraOverheat());

	for(unsigned int i = 0; i < qtdAtualAsteroides; i++)	{
		janela.draw(*asteroides[i]);
		janela.draw(asteroides[i]->getBarraDeVida());
	}

	for(unsigned int i = 0; i < qtdAtualTiros; i++)	{
		janela.draw(tiros[i]->getCorpo());
	}
	
	janela.draw(recorde);
	janela.draw(fase);
	janela.draw(pontuacao);
	

	janela.display();
}

void trabalho::Jogo::criaAsteroides(unsigned int qtd)	{
	for(unsigned int i = 0; i < qtd; i++)	{
		asteroides.push_back(std::shared_ptr<Asteroide>(new Asteroide{1880, 1030}));

		for(unsigned int j = 0; j < i; j++)	{
			if((*asteroides.back() == *asteroides[j]) || (*asteroides.back() == jogador))	{
				asteroides.erase(asteroides.end() - 1);
				i--;
				qtdAtualAsteroides--;

				break;
			}
		}

		qtdAtualAsteroides++;
	}
}

void trabalho::Jogo::colisaoEntreAsteroides()	{
	for(unsigned int i = 0; i < qtdAtualAsteroides; i++)	{
		for(unsigned int j = i + 1; j < qtdAtualAsteroides; j++)	{
			if(*asteroides[i] == *asteroides[j])	{
				asteroides[i]->trocaDirecao(*asteroides[j]);
			}
		}
	}
}

void trabalho::Jogo::tiroNoAsteroide()	{
	for(unsigned int i = 0; i < qtdAtualAsteroides; i++)	{
		for(unsigned int j = 0; j < qtdAtualTiros; j++)	{
			if(asteroides[i]->getHitbox().intersects(tiros[j]->getHitbox()))	{
				(*asteroides[i])--;

				tiros.erase(tiros.begin() + j);
				qtdAtualTiros--;
				
				if(asteroides[i]->getVida() <= 0)	{
					score += 10 * level;
					
					asteroides.erase(asteroides.begin() + i);
					qtdAtualAsteroides--;
				}

				if(jogador.getVida() < 200)	{
					jogador.ganhaVida();
				}
			}
		}
	}
}

void trabalho::Jogo::colisaoJogador()	{
	for(unsigned int i = 0; i < qtdAtualAsteroides; i++)	{
		if(*asteroides[i] == jogador && jogador.falaTempo() > 0.5f)	{
			asteroides[i]->trocaDirecao(jogador);
			(*asteroides[i])--;
			if(asteroides[i]->getVida() <= 0)	{
				asteroides.erase(asteroides.begin() + i);
				qtdAtualAsteroides--;
			}

			jogador--;
			jogador.zeraTimer();
		}
	}
}

void trabalho::Jogo::trocaFase()	{
	level++;
	criaAsteroides(qtdInicialAsteroides + level);
}

void trabalho::Jogo::fimDeJogo()	{
	sf::Text mensagemFinal;
	
	mensagemFinal.setFont(fonte);
	mensagemFinal.setPosition(840.f, 460.f);

	if(score > highScore)	{
		mensagemFinal.setFillColor(sf::Color::Yellow);
		mensagemFinal.setString("Novo Recorde!\n\t" + std::to_string(score));
	} else {
		mensagemFinal.setFillColor(sf::Color::White);
		mensagemFinal.setString("Pontuacao Final " + std::to_string(score));
	}

	janela.draw(mensagemFinal);
	janela.display();
	sf::sleep(tempoPorFrame * 180.f);
}