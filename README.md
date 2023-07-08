# Asteroides

![Tela inicial](https://imgur.com/FG1BHkW.png)

Este é meu primeiro jogo inspirado no clássico jogo de arcade Asteroids. Feito originalmente como um projeto para a disciplina de Programação III que cursei na UFSC Joinville, foi adaptado para o modelo do template que tenho disponível [neste repositório](https://github.com/lucas-yotsui/My-SFML-Template).

![Exemplo de tela comum no jogo](https://imgur.com/Kg3c4Eb.png)

A mecânica é rudimentar e o jogo em geral apresenta alguns bugs e falhas de projeto que evidenciam que este é o primeiro jogo que desenvolvi na vida. Pretendo criar uma nova tentativa desse projeto, corrigindo as falhas que pude perceber neste. Quando o fizer, incluirei aqui um link para o repositório dessa nova versão.

## Jogabilidade

O jogo possui duas entidades básicas: 

1. A nave controlada pelo jogador. 
2. Os asteroides. 

![Elementos do jogo](https://imgur.com/XggTFDb.png)

O funcionamento do jogo é muito simples, o jogador deve evitar ser atingido pelos asteroides enquanto os destrói atirando neles. Quanto mais asteroides o jogador destruir antes de morrer, mais pontos são ganhos. 

Cada asteróide deve ser atingido duas veses para ser destruído.

O jogador possui 4 pontos de vida, perdendo um a cada vez que colide com um asteroide.

Quando um asteroide é destruído por um tiro, o jogador recupera um ponto de vida.

Se o jogador segurar pressionado o botão de atirar por muito tempo, sua arma superaquece e ele fica impossibilitado de usá-la até que ela resfrie novamente.

## Controles

WASD para movimentar a nave.

A nave aponta para o cursor a todo instante, então deve-se usá-lo para mirar.

O botão direito do mouse dispara a arma.

## Considerações Finais

Fique a vontade para clonar esse repositório e compilar o jogo para testá-lo.

Caso deseje desenvolver algo semelhante utilizando SFML, confira o repositório de template desse projeto que criei [neste link](https://github.com/lucas-yotsui/My-SFML-Template). Nele há um guia completo de como criar um projeto baseado nesse template, compilar e executar esse projeto.