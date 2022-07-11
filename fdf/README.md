# Fdf project at 42 school

### Create a 3D representation of a landscape using minilibx

The first big part of fdf is to parse the map correctly to be able to use data to create your 3D representation.
For this project each point in a map is converted a vector_4 containing x, y, z and its color.
I am then using an isometric convertion on those vector_4, the z varaible is then add or substrac to y to create a 3D effect.

### What I learned:
* Using minilibx (create img, put image, key hooks ...)
* Use of vectors


# FdF
> Representing a loandscape as a 3D object in which all suface are o;utlined in lines. 

## Table of Contents
* [General Info](#general-information)
* [Minilibx library](#minilibx-library)
* [Technologies Used](#technologies-used)
* [Examples](#examples)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [Room for Improvement](#room-for-improvement)
* [Contact](#contact)

## General Information
- For this project we was able to use the minilibx graphical library
- The first purpose of this projet is to understand how to use the minilibx library, because this same library will be use in a bigger project name [cub3D](https://github.com/MaxenceLiboz/42_projects/tree/master/cub3D)
- Moreover I used some vectors and learn about different plan representation such as carthesian and isomethric

## Minilibx library
* What is minilibx  
Minilibx is a library that allow to create a window and draw either pixel or images into it. Each image is a table of pixel represented by char
* How did I used it ?  
In order to learn more about minilibx I used online documentation the biggest one was the one of [harm-smits](https://harm-smits.github.io/42docs/libs/minilibx)

## Technologies Used
- C
- Minilibx
- Makefile

## Examples
ADD EXAMPLES OF THE PROGRAM

## Setup
This project use minilibx that should be by default in the folder after download

First of all clone you will have to clone the all 42 repository:
```
https://github.com/MaxenceLiboz/42_projects.git 42
```

Then move into the wanted forlder:
```
cd 42/fdf
```
Lastly make the porject
```
make
```

## Usage
After the setup you will be able to use the executable created name fdf with the different mapps located in the maps folder.
```
./fdf maps/[MAP_NAME]
```

## Project Status
The project is complete and turned in.

## Room for Improvement
Room for improvement:
- Use of matrix, in order to make the image rotate, move etc..
- Clean the calculus to make the map in the center of the window

## Contact
Created by [@mliboz](https://github.com/MaxenceLiboz)
