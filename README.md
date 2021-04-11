# ARCADE

Ce projet à pour but de créer un programme d'arcade permettant de lancer différents jeux avec différentes bibliothèque graphiques.

Les jeux:<br>
- [x] Pacman<br>
- [ ] Nibbler<br>

Les bibliothèques graphiques:<br>
- [x] ncurses<br>
- [ ] SFML<br>
- [ ] SDL2<br>

## Installation

Commencez par cloner le projet sur votre ordinateur
```
git clone https://github.com/EpitechIT2020/B-OOP-400-LIL-4-1-arcade-louis.chopinet.git arcade
cd arcade/
```

Créez ensuite les fichier de compilation via `cmake`
```
cmake .
```

Puis compilez le projet
```
cmake --build .
```

## Utilisation

Pour lancer le programme utilisez
```
./arcade <graphic_libbrary_name>
```

Les bibliothèque graphiques disponible apparaissent dans le dossier `lib`
```
lib
├── arcade_ncurses.so
├── arcade_sdl2.so
└── arcade_sfml.so
```

Pour lancer le programme avec la ncurses tapez
```
./arcade lib/arcade_ncurses.so
```

## Mapping

Vous pouvez créer vos propre carte pour certain jeux.

Pour ce faire vous devez créer un nouveau fichier dans le dossier `mapping`<br>
L'extension de ce fichier doit correspondre au jeu pour le quel la carte est destiné:
- Pacman `.pcm`
- Nibbler `.nbl`

Des exemples de carte sont disponible dans ce même dossier.

Légende des carte:<br>
- `#` est un mur<br>
- `.` est un chemin pour le joueur<br>
- `@` est un bonus<br>
- `M` est un monstre<br>
- tous les autres éléments sont des murs<br>

Les autres élements sont générer de façon aléatoire au lancement du jeu

## Crédits

> Projet développé par _**Louis Chopinet**_ et _**Pierrick Gouerec**_ <br>
> Interface partagé avec _**Marc berthelin**_, _**Arthur Decovemacker**_ et _**Seraphin Perrot**_