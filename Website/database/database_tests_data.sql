BEGIN TRANSACTION;

INSERT INTO `users` (`id`, `username`, `name`, `password`, `email`, `isTeacher`) VALUES (1,"user_already_in_db","name", "password_already_in_db", "email_already_in_db", 0);
INSERT INTO `users` (`id`, `username`, `name`, `password`, `email`, `isTeacher`) VALUES (2,"user_already_in_db2","name2", "password_already_in_db2", "email_already_in_db2", 0);


INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (1,"Exercise1Title","Exercise1Description","Exercise1ImageBase64",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (2,"Exercise2Title","Exercise2Description","Exercise2ImageBase64",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (3,"Exercise3Title","Exercise3Description","Exercise3ImageBase64",1,1);


INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (1,"Test1TestCodeExercise1","Test1TitleExercise1","Test1HintExercise1",1);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (2,"Test2TestCodeExercise1","Test2TitleExercise1","Test2HintExercise1",1);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (3,"Test1TestCodeExercise2","Test1TitleExercise2","Test1HintExercise2",2);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (4,"Test2TestCodeExercise2","Test2TitleExercise2","Test2HintExercise2",2);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (5,"Test1TestCodeExercise3","Test1TitleExercise3","Test1HintExercise3",3);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (6,"Test2TestCodeExercise3","Test2TitleExercise3","Test2HintExercise3",3);



INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (1,1,50,"Exercise1User1Feup8File");




INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (3,1);


COMMIT TRANSACTION;
