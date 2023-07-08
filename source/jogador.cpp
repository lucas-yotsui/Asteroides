#include <jogador.h>

trabalho::Jogador::Jogador(float limX, float limY):Entidade(300.f, 600.f, 200, limX, limY), cima(false), baixo(false), direita(false), esquerda(false), atirando(false), overheat(false), tempoAtirando(0), tempoCooldown(0)	{

	textura.loadFromFile("assets/textures/jato.png");

	barraDeVida.setOrigin(0.f, 2.f);
	barraDeVida.setFillColor(sf::Color::Green);

	barraCooldown.setOrigin(0.f, 2.f);
	barraCooldown.setFillColor(sf::Color::Yellow);

	barraOverheat.setOrigin(0.f, 2.f);
	barraOverheat.setFillColor(sf::Color::Red);

	setTexture(textura);
	setScale(0.125, 0.125);
	setPosition(860, 540);

	float tamX = float(textura.getSize().x), tamY = float(textura.getSize().y);
	setOrigin(tamX/ 2, tamY / 2);
	setHitbox({0.f, 0.f, tamX, tamY});
}

void trabalho::Jogador::processaInputsDoUsuario(sf::Keyboard::Key tecla, bool pressionada)	{
	switch(tecla)	{
		case sf::Keyboard::W:
			cima = pressionada;
			break;
		case sf::Keyboard::S:
			baixo = pressionada;
			break;
		case sf::Keyboard::D:
			direita = pressionada;
			break;
		case sf::Keyboard::A:
			esquerda = pressionada;
			break;
		default:
			break;
	}
}

void trabalho::Jogador::processaInputsDoUsuario(sf::Mouse::Button botao, bool pressionada)	{
	if(botao == sf::Mouse::Button::Left)	{
		atirando = pressionada;
	}
}

void trabalho::Jogador::atualiza(float deltaTempo)	{
	if(cima)	{
		if(getPosition().y <= 40)	{
			velocidadeAtual.y = 0;
		} else if(velocidadeAtual.y > -maxVelocidade)	{
			velocidadeAtual.y -= aceleracao * deltaTempo;
		}
	}

	if(baixo)	{
		if(getPosition().y >= limJanelaY)	{
			velocidadeAtual.y = 0;
		} else if(velocidadeAtual.y < maxVelocidade)	{
			velocidadeAtual.y += aceleracao * deltaTempo;
		}
	}

	if(esquerda)	{
		if(getPosition().x <= 40)	{
			velocidadeAtual.x = 0;
		} else if(velocidadeAtual.x > -maxVelocidade)	{
			velocidadeAtual.x -= aceleracao * deltaTempo;
		}
	}

	if(direita)	{
		if(getPosition().x >= limJanelaX)	{
			velocidadeAtual.x = 0;
		} else if(velocidadeAtual.x < maxVelocidade)	{
			velocidadeAtual.x += aceleracao * deltaTempo;
		}
	}

	if(!cima && velocidadeAtual.y < 0)	{
		if(getPosition().y <= 40)	{
			velocidadeAtual.y = 0;
		} else {
			velocidadeAtual.y *= atrito;
		}
	}

	if(!baixo && velocidadeAtual.y > 0)	{
		if(getPosition().y >= limJanelaY)	{
			velocidadeAtual.y = 0;
		} else {
			velocidadeAtual.y *= atrito;
		}
	}

	if(!esquerda && velocidadeAtual.x < 0)	{
		if(getPosition().x <= 40)	{
			velocidadeAtual.x = 0;
		} else {
			velocidadeAtual.x *= atrito;
		}
	}

	if(!direita && velocidadeAtual.x > 0)	{
		if(getPosition().x >= limJanelaX)	{
			velocidadeAtual.x = 0;
		} else {
			velocidadeAtual.x *= atrito;
		}
	}

	if(atirando && !overheat)	{
		tempoAtirando += deltaTempo;

		if(tempoAtirando >= 10)	{
			overheat = true;
		}
	} else if(tempoAtirando >= 0)	{
		tempoAtirando -= deltaTempo;
	}

	

	if(overheat)	{
		tempoCooldown += deltaTempo;

		if(tempoCooldown >= 15)	{
			overheat = false;
			tempoCooldown = 0;
		}
	}

	move(velocidadeAtual * deltaTempo);
	setRotation(90 + (180 / float(std::acos(-1))) * std::atan2(direcao.y, direcao.x));
	barraDeVida.setSize(sf::Vector2f((float(getVida())/2.f), 2.f));
	barraDeVida.setPosition(getHitbox().left, getHitbox().top);
	
	barraCooldown.setSize(sf::Vector2f((tempoCooldown * 100.f /15.f), 2.f));
	barraCooldown.setPosition(barraDeVida.getPosition().x, barraDeVida.getPosition().y - 4.f);
	
	barraOverheat.setSize(sf::Vector2f((tempoAtirando * 10.f), 2.f));
	barraOverheat.setPosition(barraDeVida.getPosition().x, barraDeVida.getPosition().y - 8.f);
}

void trabalho::Jogador::setDirecao(const sf::Vector2f& d)	{
	direcao = d;
}

float trabalho::Jogador::falaTempo()	{
	return tempoDesdeUltimoHit.getElapsedTime().asSeconds();
}

void trabalho::Jogador::zeraTimer()	{
	tempoDesdeUltimoHit.restart();
}

bool trabalho::Jogador::getAtirando()	{
	return atirando;
}

bool trabalho::Jogador::getOverheated()	{
	return overheat;
}

sf::RectangleShape trabalho::Jogador::getBarraCooldown()	{
	return barraCooldown;
}

sf::RectangleShape trabalho::Jogador::getBarraOverheat()	{
	return barraOverheat;
}