<h1 align="center"> 🐶  Princesa Catches  🐶</h1>

</h1>
Projeto final criado para a disciplina de Linguagem de Programação I (2023.1), com o desenvolvimento de um jogo básico, utilizando a biblioteca OpenCV, feito para avaliar, na prática, os conhecimentos ensinados sobre Programação Orientada a Objetos e o uso do algoritmo da OpenCV de detecção de objetos, em C++.

<p>&nbsp;</p>

Professor: Derzu Omaia.

<p>&nbsp;</p>

## Especificações gerais

-  Fazer a modelagem das classes que serão utilizadas no sistema utilizando diagrama UML de classe.

- O programa deve rodar indefinidamente, até que o usuário escolha sair. Exiba um menu (modo texto ou tela).

-  Exibir pontuação final, e salvar em arquivo a maior pontuação (record).

- Usar a biblioteca OpenCV, Yolo ou OpenPose para detectar algum objeto ou jogador.

- Tocar um som quando uma pontuação for feita.

<p>&nbsp;</p>

## Diagrama de classes

![Diagrama](https://github.com/ana-londres/OpenCV-Princesa/blob/main/imgs/uml-OpenCV.jpg?raw=true)

<p>&nbsp;</p>

## Objetivo do jogo
- O usuário deve mexer o rosto até o petisco para pontuar. O petisco aparecerá de maneira aleatória na tela.

- O jogo tem duração de 35 segundos. O usuário, depois da partida, pode escolher jogar novamente ou sair do jogo.

- O objetivo principal é bater o recorde no tempo proposto.

<p>&nbsp;</p>

## Como rodar o jogo?
- As bibliotecas [OpenCV](https://sites.google.com/site/derzuomaia/tutoriais/instala%C3%A7%C3%A3o-opencv-no-linux-ubuntu), [Chrono](https://api.projectchrono.org/tutorial_install_chrono.html) e [MPlayer](https://howtoinstall.co/package/mplayer) devem ser instaladas antes de rodar o jogo.

- Rodando no Linux Ubuntu:
    - A linha de comando para compilar o código é: ```g++ main.cpp Petisco.cpp GerenciaArquivo.cpp `pkg-config --cflags opencv4` `pkg-config --libs --static opencv4` ```
    - Depois de compilado, basta rodar o arquivo executável. (ex: ```./a.out```)

<p>&nbsp;</p>

## Conhecendo Princesa
- Princesa é uma cadela com deficiência visual que tivemos o prazer de conhecer durante nosso trabalho da disciplina de Introdução a Engenharia da Computação (2022.2), no qual fizemos um dispositivo com arduino chamado SIRIUS para ajudá-la a evitar colidir com objetos.

<p align="center">
  <img src="https://github.com/ana-londres/OpenCV-Princesa/blob/main/imgs/SIRIUSday.jpeg?raw=true" alt="Foto com Princesa">
</p>

<p>&nbsp;</p>

## Contribuidores

| <a href="https://www.linkedin.com/in/analondres/" target="_blank">**Ana Luisa Londres**</a> | <a href="https://www.linkedin.com/in/jo%C3%A3o-leonardo-vilar-ferreira-163730291/" target="_blank">**João Leonardo Vilar**</a> | <a href="https://www.linkedin.com/in/nicolle-cerqueira-086578291/" target="_blank">**Nicolle Cerqueira**</a> |
| :---------------------------------------------------------------------------------------: | :-----------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------: |
| <img src="https://avatars.githubusercontent.com/u/125302336?v=4" width="200px">          | <img src="https://avatars.githubusercontent.com/u/130939869?v=4" width="200px">          | <img src="https://avatars.githubusercontent.com/u/125302668?v=4" width="200px">          |
| <a href="https://github.com/ana-londres" target="_blank">`github.com/ana-londres`</a>  | <a href="https://github.com/joaoleonardovf" target="_blank">`github.com/joaoleonardovf`</a> | <a href="https://github.com/nicollecerqueira" target="_blank">`github.com/nicollecerqueira`</a> |
