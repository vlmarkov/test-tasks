# producer-consumer

## 1. Description

Needs to implement a multithreaded program on C language.

* First thread - producer
* Other `N` threads - consumers
* Producer will generate a message in a random amount of time and assign it to the available consumer
* Consumer after receiving has to show the message, process the message, increment internal counter and sleep (let the other consumers work)
* Program has to handle `SIGUSR1` signal to show statistic

## 2. Features

* Pure C (without additional libraries)
* C11 standard
* Cmake

## 3. How to

1. `make`
2. `./producer-consumer [N] (where is N - number of consumers)`
