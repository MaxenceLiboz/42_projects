# Minishell
> Create a simple shell, our own little bash 

## Table of Contents
* [Technologies Used](#technologies-used)
* [General Info](#general-information)
* [Our workflow](#our-workflow)
* [The parsing](#the-parsing)
* [The built-ins](#the-built-ins)
* [The execution](#the-execution)
* [The redirection](#the-redirections)
* [Examples](#examples)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [Room for Improvement](#room-for-improvement)
* [Contact](#contact)

## Technologies Used
- C
- Makefile

## General Information
This project is the first project in group, I personally made this project with my friend [Tarchimb](https://github.com/Tarchimb)

More than just the first project in duo, it was also the very **first big project** of my time at **42**. Indeed, we took about **three months** to complete it.

The main goal of this project is to **create a small bash** with the execution of **one or several command** (pipes) and with several built-in commands.

First of all we thought that we could separate this project in several pieces: <br/>
**Primary**, we had the **parsing** that was a really big part, it could have been done in several different way (we will explain it to you latter in the doc [here](the-parsing)).<br/>
**Secondary**, we had the *built-in commands**, those needed to really understand how the standard command worked in order to replicate as perfectly as we could.<br/>
**Tertiary**, we had the **execution** to handle. Indeed, all the other command needed to be executed by our minishell, a part of this execution is to handle the pipes [ ls | ls ].<br/>
**Finaly**, we had to take care of the different types of redirection: infile, outfile, outfile appended and heredocs

**All those part will be detail in this doc, find the like [above here](#table-of-contents)**

After all that being said, we decided to firsly separate our work, [Tarchimb](https://github.com/Tarchimb) decided to take the built-ins part and I took the parsing one. Check about our [workflow below](#our-workflow)

## Our workflow
You need to know that it was the first time we worked as a team with the same git repository. So, we started by working on the same branch, that made a lot of mess. We then decided to proprely document ourself on how to use git as a team. Hence, we started to puts tickets for each feature we wanted to make, and create a branch acrodingly.
![Example workflow](./img/git-workflow.png)


## The parsing
WRITE ABOUT THE PARSING

## The built-ins
WRITE ABOUT THE BUILT-INS

## The execution
WRITE ABOUT THE EXECUTION

## The redirections
WRITE ABOUT THE REDIRECTIONS

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
