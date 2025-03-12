<h1 align="center">
 So_Long: Soul Catcher
</h1>

<p align="center"><img src="https://github.com/Luis-Bravo-Dias/3D-Personal-Projects/blob/main/Soul%20Catcher/Soul%20Catcher%20promo.gif"</p>
<p align="center">3D cutscene made in Blender, is not part of the game</p>

<h1 align="center">
 Introduction
</h1>
<p>This project is part of the 42 school curriculum and focuses on creating a simple 2D game using the MinilibX graphics library.
  
  So_Long involves creating a simple 2D game where the player controls a character navigating a maze-like environment. The goal is implementing the game mechanics, graphics rendering, and user interaction using the MinilibX graphics library.</p>

  <h1 align="center">
 Features
</h1>

> Implementation of a simple 2D game using the MinilibX graphics library

> Graphics rendering for sprites, textures, and background elements

> Player character movement and collision detection

> Interactive elements such as collectibles and enemies

  <h1 align="center">
 To Run
</h1>

At the root of the project
<pre>
$> make 
./so_long map/[map_name].ber
</pre> 

The game ends when the player gets all the collectibles and goes to the exit.

 <h1 align="center">
 How to make your own map
</h1>

> Create a rectangular map with 0s and 1s, where 0 is floor and 1 is wall, in a .ber file.

> The map must be closed by walls.

> Place just 1 character P somewhere on the map for the player's starting position.

> Place C characters to create collectibles and E for enemies on the map.
