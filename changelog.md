# Changelog
All notable changes to this project will be documented in this file.


## [0.1.0] - 15-10-2018 - Sprint 1
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



## [0.2.0] - 30-10-2018 - Sprint 2
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



## [0.3.0] - 14-11-2018 - Sprint 3
### Closed PBI's
- Open-API Documentation #74
- Fix bugs on tests output #75
- Decide which FEUP-8 files should be part of the coverage #59
- Laravel unit tests #50
- Fix the problems left from previous sprint #73
- Add the xdebug install options to Dockerfile #69
- Add descriptive acceptance tests to sprint 3 PBIs #67
- Add linter to application (C) #55
- Add clang-format linter to C files #68 
- API unit tests #48
- Show test output result on interface #71
- Read test output as a student #18
- Unit tests on client API #64
- Website-API new functionalities #62
- Coverage tests for laravel #58

### Increment description
This sprint was more focused in fixes and new  related to the SCRUM process that is being followed. We have finished all unit tests to the code developed so far, as well as tested it for coverage.
The code is now also verified by a linter in each push.
The API developed in previous sprints is now fully documented using the Open-API swagger hub platform.
However, we have also finished the development of the functionalities that allows a student (user of the program) to test student code on server and show tests results.


## [0.4.0] - 26-11-2018 - Sprint 4
### Closed PBI's
- Added automated deployment #66
- List existent exercises as a Teacher #10
- Create exercise as a Teacher #9
- Add tips to unit tests as a Teacher #17
- Edit exercise as a Teacher #8
- Login as a Teacher on the Website #22
- List the exercise I've created #24

### Increment description
This sprint was dedicated to the website, allowing a teacher to add exercises that can later be used in the FEUP-8. A teacher can now, using the website, login, create an exercise and respective tests, as well as edit them. The teacher can also list all the exercises available in the platform, as well as his own exercises (i.e. the exercises developed by him).
The continuous deployment, started in the last sprint, was also finished.


## [1.0.0] - 12-12-2018 - Sprint 5
### Closed PBI's
- Add right permissions to Actions on Website #94
- Improve interoperability between the two components #95
- Login as a Student on FEUP-8 #11
- Register on Website as a Visitor #20
- Logout as a Student #12
- Register on the FEUP-8 application as a Visitor #21
- Change Database Management System #90
- Delete an exercise as a Teacher #26
- Open a saved exercise as a Student #15
- Website Tuning #23
- Save an exercise progress as a Student #14
- Convert TIC-80 into FEUP-8 #47

### Increment description
This sprint focused on finishing the implementation of important features such as support for saving and loading progress feature on client-side (on server side it was already implemented). Using the FEUP-8 app, a student can now login, logout and register.

On the Website, it is now possible to delete an exercise when logged in as a Teacher. The Website aesthetics and navbar were also improved.

As final fixes, we improved the client and server interoperability for final release:
* fixed FEUP-8 client not working with production server
* the FEUP-8 app is now more configurable as the server Domain/IP address can be changed by editing a config file (conf.ini)
* FEUP-8 error messages related to communication between the client and the server were improved

#### Bug Fixes:
	FEUP-8:
		* Segmentation fault on trying to load an exercise with id non positive
		* Segmentation fault on load tests from an exercise that has none
		* Segmentation fault on sending student code to be tested in the server from an exercise that has no tests
		* Duplicated registering when registering on FEUP-8. Register already does the user authentication automatically
		* String errors caused by wrong or missing null terminators on see test description from an exercise
		* Segmentation fault caused by aliasing in server responses. This caused fro example to seg fault when list exercises after showing an exercise(because of the higher number of bytes of the second)
	Website:
		* When a exercise has no tests, the progress calculation must return 0, which caused the save progress feature (that calculates current progress) to fail for permission denied.
		* The creator of an exercise (i.e. a teacher) not having permissions to see his own exercise on FEUP-8