# OIM Simulation

A multi-processing application that simulates the daily operation of the occupation interior ministry offices (OIM for short) at Sheikh Jarrah neighborhood, written in C & OpenGL, using Linux IPC techniques for synchronization. 

> this project is a part of the **Real Time Applications & Embedded Systems (ENCS4330)** course at [BZU](https://www.birzeit.edu).

## Demo


<!-- TODO Demo Video -->


## Authors
* Ibraheem Alyan: 1201180
* Mohammad Mualla: 1180546

## Installation

to make the project portable, [Docker](https://www.docker.com) containers were used as a runtime enviroment.

### Prerequisites ✅
* Docker : to make the project portable, [Docker](https://www.docker.com) containers were used as a runtime enviroment.

* VNC client

### Setup ⚙️

> the folowing commands are intended to be run in a bash shell

1. clone the repository
    ```bash
    git clone https://github.com/ibraheemalayan/first_project_the_big_race.git real_time_project
    cd real_time_project
    mkdir src/bin
    ```


2. setup the container
    * windows
        ```bash
        bash windows_setup.sh
        ```
    * unix/linux
        ```bash
        bash setup_container.sh
        ```
3. connect the VNC client to the url shown in the output of the setup script (password is `headless`)


4. inside the container shell, run the intended make command.


> Note: before running the gui from an ssh session
> 
> ```
> export DISPLAY=:0
> ```

### Usage ▶️

> makeFile is inside the `src` directory

Available make commands:

* `make run <num_of_rounds>` - run the project in gui mode
* `make run_gui` - run the standalone gui code with default number of rounds and random speeds **(for testing)**
* `make run_cli <num_of_rounds>` - run the project in cli mode without gui **(for testing)**

Debugging (GDB)

* `make debug <num_of_rounds>` - run the project inside gdb
* `make debug_cli <num_of_rounds>` - run the project in cli mode without gui inside gdb **(for testing)**
* `make debug_gui` - run the project in gui mode inside gdb **(for testing)**


> there other make commands, but they are not intended to be used directly.

#### Debugging in gdb 🐞

* to follow child in forks
```
set follow-fork-mode child
```


* to follow new process after exec 
```
set follow-exec-mode new
```


### TODOs

#### Project

* [X] solve ui slowness issue in ubuntu
* [ ] document make available commands
* [X] add contributors names/ids
* [ ] add a demo GIF in this README

#### Backend

* [ ] create the message queues ( and delete on exit )
* [ ] message struct & message types
* [ ] configs file and its loading function (.env maybe)

#### UI

* [ ] function to draw male
* [ ] function to draw female
* [ ] draw background
* [ ] draw the center queues
* [ ] draw the ticket label for each person
* [ ] draw tellers
* [ ] draw metal detector
* [ ] draw officers
* [ ] update styling (colors & fonts)
* [ ] function to move all people in a queue
* [ ] function to organize people in waiting areas
* [ ] function for impatient people to leave ( just let them go up until the end of the screen )




