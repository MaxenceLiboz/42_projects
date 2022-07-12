# Philosopher
> Re-create the [dining philosopher problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) 

## Table of Contents
* [General Info](#general-information)
* [Technologies Used](#technologies-used)
* [Examples](#examples)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [Room for Improvement](#room-for-improvement)
* [Contact](#contact)

## General Information
- The purpose of this project is to learn the basics of threads.
- We will have to use mutex and semaphore in order to protect our program form data-raise
- This program will take 4 to 5 different variable:
  - The number of philospher
  - The time to die in ms
  - The time to eat in ms
  - The time to sleep in ms
  - The number of time a philosopher must eat before leaving the table (optional)

Terefore, the philospher have a certain amount of time before diying, and this time is reset each time they eat. Each philopher <br/>
will have to first eat, then sleep and finally think, over and over until one die or the number of the fifth variable is hit. <br/>
Of course, it is not that easy. Indeed, each philosopher need 2 forks to eat, but there are only as many forks as many philosopher, <br/>
which means that when one philosopher is eating another need to wait his turn to take the fork. <br/>
All of this project is about making a program that will make the philosopher survive as much as possible, for example, <br/>
when there are 4 philosopher that have 410 ms to die, 200 to it and 200 to sleep, the program should run infinitly.

## Technologies Used
- C
- Makefile

## Examples
ADD EXAMPLES OF THE PROGRAM

## Setup

First of all clone you will have to clone the all 42 repository:
```
https://github.com/MaxenceLiboz/42_projects.git 42
```

Then move into the wanted forlder:
```
cd 42/philosopher
```
Lastly chose either the philos or philo_bonus folder and make the project
```
cd pilo
make
```
or 
```
cd pilo_bonus
make
```

## Usage
After the setup you will be able to use the executable created name philo or philo_bonus with 4 or 5 different variables.
```
./philo [NB OF PHILOSOPHER] [TIME TO DIE] [TIME TO EAT] [TIME TO SLEEP] [(OPTIONAL)NB OF TIME TO EAT BEFORE STOP]
```
Example that will run an infinite loop as none of the philosopher die
```
./philo 4 410 200 200
```

## Project Status
The project is complete and turned in.

## Room for Improvement
Room for improvement:
- The mandatory part:
The way that was the most efficient for the cpu was to make the fork the mutex, like that we just had to make it lock when a philosopher use it.<br/>
Indeed, it minimize the number of check you have to do. The subject was that clear about it but there was antoher way that might be the one actually asked to do <br/>
We had the possibility to create a variable by fork that would hold a value and a mutex to protect that value (which is normally how the mutex should be use) <br/>
However, the check for this method are far more demanding on the CPU. Indeed, you had to create for each check an inifinite loop to lock the variable, read it and unlock it. <br/>
That is why I privileged the most efficient way.

- The bonus part:
For this part I made a mistake that I found after all my corrections, and because I did myslef a correction of one of my peer on this project. <br/>
In fact, I read that the semaphore could, contrary to the mutex, hold a value themselves, and therefore, I thought that I would be able to create one semaphore <br/>
for all the fork, but I missread the subject and interpret that we actually had to create one semaphore for each fork like the mutex. This bonus was then just <br/>
re-writing the mandatory part and changing each mutex by a semaphore, or that was not the goal.

## Contact
Created by [@mliboz](https://github.com/MaxenceLiboz)
