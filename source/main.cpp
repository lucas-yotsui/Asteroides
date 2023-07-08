#include <menu.h>
#include <jogo.h>

auto main() -> int {
	int dificuldade;

	//O menu está dentro de um escopo para ser destruído quando não for mais necessário
	{	trabalho::Menu menuInicial;
		dificuldade = menuInicial.rodaMenu();
	}


	//Se a variável dificuldade for 0, o menu foi fechado sem escolher uma dificuldade.
	//Nesse caso, nem instancia o objeto jogo
	if(dificuldade > 0)	{
		trabalho::Jogo jogo{dificuldade};
		
		jogo.rodaJogo();
	}

    return 0;
}