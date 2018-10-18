BEGIN TRANSACTION;

-- Table: User
DROP TABLE IF EXISTS users;
CREATE TABLE users (
    id        INTEGER PRIMARY KEY
                      UNIQUE
                      NOT NULL,
    username  STRING  UNIQUE
                      NOT NULL,
	name 	  STRING  NOT NULL,
    password  STRING  NOT NULL,
    email     STRING  NOT NULL,
    isTeacher BOOLEAN NOT NULL
);


-- Table: Exercise
DROP TABLE IF EXISTS Exercise;
CREATE TABLE Exercise (
    id          INTEGER PRIMARY KEY
                        UNIQUE
                        NOT NULL,
    title       STRING  NOT NULL,
    description STRING  NOT NULL,
    image_path  STRING  UNIQUE
                        NOT NULL,
    creator_id  INTEGER REFERENCES users (id) 
                        NOT NULL,
    isPrivate   BOOLEAN NOT NULL
);


-- Table: Test
DROP TABLE IF EXISTS Test;
CREATE TABLE Test (
    correct_code STRING  NOT NULL,
    tests_code   STRING  NOT NULL,
    exercise_id  INTEGER REFERENCES Exercise (id) 
                         NOT NULL
                         PRIMARY KEY
);


-- Table: ExerciseStudent
DROP TABLE IF EXISTS ExerciseStudent;
CREATE TABLE ExerciseStudent (
    exercise_id 	INTEGER  NOT NULL,
    student_id  	INTEGER  NOT NULL,
    progress    	INTEGER  NOT NULL,
	feup8_file		BLOB,
	PRIMARY KEY (exercise_id, student_id)
);


-- Table: ExerciseStudentPermissions
DROP TABLE IF EXISTS ExerciseStudentPermissions;
CREATE TABLE ExerciseStudentPermissions (
    exercise_id INTEGER REFERENCES Exercise (id) 
                        NOT NULL,
    student_id  INTEGER REFERENCES users (id) 
                        NOT NULL,
    PRIMARY KEY (exercise_id, student_id)
);

COMMIT TRANSACTION;
