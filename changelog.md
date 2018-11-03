# Changelog
All notable changes to this project will be documented in this file.


## [0.1.0] - 15-10-2018 - Sprint1
### Closed PBI's
- Database Schema #34
- Database SQL #32
- Setup a Unit Test framework for FEUP-8 #39
- Deploy laravel framewok and structure the website #38
- Standardize an exercise format #41
- Database migrations #53
- Study of the TIC-80 App #37

### Increment description
We started by studying the TIC-80 app in order to understand the architecture so that we could integrate our code to expand the app and make it more suitable for education.
Before starting the development of the code, we got a framework for unit testing it.
On server side, we started by architecturing the app, setting up the framework to be used (laravel) and developing the database schema and sql code.
We started the development of the API responsible by the communication between the app and the server.
In the end of this sprint it was only possible to list the exercises in the database using the app. However, communication and server backend was mostly developed for getExericiseDetails although not finished and therefore not possible for the user to see happening.



## [0.2.0] - 30-10-2018 - Sprint2
### Closed PBI's
- Execute lua scripts on server #51
- Update Docker image #63
- Run test on exercise as a Student #16
- FEUP-8 API #36
- List existent exercises as a Student #7
- Solve exercise as a Student #25
- Docker and Gitlab CI #46
- Create lua exercises #54
- Gitlab CI #57
- Docker Application FEUP-8 #61
- Create Gitlab templates #60
- Server tests parsing #52
- Application Unit Tests #49
- Prototype a "see exercise" interface in FEUP-8 #40
- Website API #35
- Open exercise as a Student #13

### Increment description
We started by setting up the Gitlab CI so we could have testing feedback on our code on each commit. We also set up the docker images for the client app and server. We enabled the server to be able to run lua code in order to run the tests on an exercise.
In the end of this sprint the user was able to list the details of an exercise on the client app. Was also implemented the backend to run tests on an exercise (which implied sending the code to the server, running the tests on it and sending the results back to the client) and save their progress on an exercise to the server so that they can start from the point they finished at, the next time they login in on the same account, on any device, allowing synchronization.
