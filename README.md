# Taquin

### Un simple jeu de puzzle écrit en c++/SFML
Gameplay: déplacez les pièces avec les flêches ou la souris, espace ou clic droit pour afficher l'image d'aide.


### A Simple Puzzle game writed in c++/SFML
Gameplay: arrow keys(up,down,left,right) or mouse, space or right mouse button to display help image.

### Compilation
You must install SFML(2.5) -dev to compil, and lib depends to launch (libsfml-system2.5 libsfml-graphics2.5 libsfml-window2.5 libsfml-audio2.5).


Vous devez installer les librairies SFML(2.5) -dev pour compiler et ses dépendances pour lancer (libsfml-system2.5 libsfml-graphics2.5 libsfml-window2.5 libsfml-audio2.5).

### install
```sh
sudo apt-get install libsfml-dev
```

### Clone & compile
```sh
$ git clone https://github.com/Crabman77/taquin.git
$ cd taquin
$ g++ -o taquin Main.cpp Anim.cpp Button.cpp Card.cpp Engine.cpp Hud.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++14
```
### Launch
```sh
./taquin
```

![taquin](images/screen1.png)

![taquin](images/screen2.png)

