#include <asteroide.h>

trabalho::Asteroide::Asteroide(float limX, float limY):Entidade(200.f, 0.f, 100, limX, limY), tempoDesdeUltimaColisao(0)	{
	std::random_device r;
	std::default_random_engine e1(r()), e2(r());
	std::uniform_real_distribution<float> uniform_dist_x(0, limJanelaX), uniform_dist_y(0, limJanelaY), uniform_dist_vel_x(100, maxVelocidade), uniform_dist_vel_y(100, maxVelocidade);
	float posX = uniform_dist_x(e1);
	float posY = uniform_dist_y(e2);

	barraDeVida.setOrigin(0.f, 2.f);
	barraDeVida.setFillColor(sf::Color::Red);

	switch(int(posX) % 3)	{
		case 0:
			textura.loadFromFile("assets/textures/asteroide.png");
			break;		
		case 1:
			textura.loadFromFile("assets/textures/asteroide2.png");
			break;
		case 2:
			textura.loadFromFile("assets/textures/asteroide3.png");
			break;
	}
	

	setTexture(textura);
	setPosition(int(posX), int(posY));

	velocidadeAtual.x = uniform_dist_vel_x(e1);
	velocidadeAtual.y = uniform_dist_vel_y(e2);
	

	if(int(posX) % 2)	{
		velocidadeAtual.x *= -1;
	}

	if(int(posY) % 2)	{
		velocidadeAtual.y *= -1;
	}

	setHitbox({0.f, 0.f, float(textura.getSize().x), float(textura.getSize().y)});
}

void trabalho::Asteroide::trocaDirecao(Asteroide& a2)	{
	sf::Vector2f temp;

	if(tempoDesdeUltimaColisao > tempoPorFrame.asSeconds())	{
		temp = velocidadeAtual;
		velocidadeAtual = a2.velocidadeAtual;
		a2.velocidadeAtual = temp;

		tempoDesdeUltimaColisao = 0;
	}
}

void trabalho::Asteroide::trocaDirecao(Jogador& j)	{
	if(velocidadeAtual.y < 0 && getPosition().y > j.getPosition().y)	{
		velocidadeAtual.y *= -1;
	} else if(velocidadeAtual.y > 0 && getPosition().y < j.getPosition().y)	{
		velocidadeAtual.y *= -1;
	}

	if(velocidadeAtual.x < 0 && getPosition().x > j.getPosition().x)	{
		velocidadeAtual.x *= -1;
	} else if(velocidadeAtual.x > 0 && getPosition().x < j.getPosition().x)	{
		velocidadeAtual.x *= -1;
	}
}

void trabalho::Asteroide::atualiza(float deltaTempo)	{
	if(velocidadeAtual.y < 0 && getPosition().y < 0)	{
		velocidadeAtual.y *= -1;
	}

	if(velocidadeAtual.y > 0 && getPosition().y > limJanelaY)	{
		velocidadeAtual.y *= -1;
	}

	if(velocidadeAtual.x > 0 && getPosition().x > limJanelaX)	{
		velocidadeAtual.x *= -1;
	}

	if(velocidadeAtual.x < 0 && getPosition().x < 0)	{
		velocidadeAtual.x *= -1;	
	}

	barraDeVida.setSize(sf::Vector2f((float(getVida())/100.f) * float(textura.getSize().x), 2.f));
	barraDeVida.setPosition(getPosition().x, getHitbox().top - 2.f);
	move(velocidadeAtual * deltaTempo);

	tempoDesdeUltimaColisao += deltaTempo;
}