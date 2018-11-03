BEGIN TRANSACTION;

INSERT INTO `users` (`id`, `username`, `name`, `password`, `email`, `isTeacher`) VALUES (1,"user_already_in_db","name", "$2y$10$CIMNPzE21s7KpyAoRuPL6OVnSq.4UE5XVJxvUsaExxpRCZJO3s8Iy", "email_already_in_db", 0);
INSERT INTO `users` (`id`, `username`, `name`, `password`, `email`, `isTeacher`) VALUES (2,"user_already_in_db2","name2", "$2y$10$JoTJGO0oLxjSixsuEFhU7uP/yMBfb0O3BerkiFl9.R/f873kXMxE.", "email_already_in_db2", 0);


INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (1,"Exercise1Title","Exercise1Description","Exercise1ImageBase64",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (2,"Exercise2Title","Exercise2Description","Exercise2ImageBase64",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (3,"Exercise3Title","Exercise3Description","Exercise3ImageBase64",1,1);


INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (1,"function sum_correct()
luaunit.assertEquals(sum(3,4) , 7)
luaunit.assertEquals(sum(4,3) , 7)
luaunit.assertEquals(sum(3,-4) , -1)
end","sum_correct","Test1HintExercise1",1);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (2,"function sum_failing()
luaunit.assertEquals(sum(3,4) , 8)
luaunit.assertEquals(sum(4,3) , 9)
luaunit.assertEquals(sum(3,-4) , -7)
end","sum_failing","Test2HintExercise1",1);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (3,"function sum_failing()
luaunit.assertEquals(sum(3,4) , 8)
luaunit.assertEquals(sum(4,3) , 9)
luaunit.assertEquals(sum(3,-4) , -7)
end","sum_failing","Test1HintExercise2",2);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (4,"function sum_failing2()
luaunit.assertEquals(sum(3,4) , 8)
luaunit.assertEquals(sum(4,3) , 9)
luaunit.assertEquals(sum(3,-4) , -7)
end","sum_failing2","Test2HintExercise2",2);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (5,"function sum_correct()
luaunit.assertEquals(sum(3,4) , 7)
luaunit.assertEquals(sum(4,3) , 7)
luaunit.assertEquals(sum(3,-4) , -1)
end","sum_correct","Test1HintExercise3",3);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (6,"function sum_correct2()
luaunit.assertEquals(sum(3,4) , 7)
luaunit.assertEquals(sum(4,3) , 7)
luaunit.assertEquals(sum(3,-4) , -1)
end","sum_correct2","Test2HintExercise3",3);



INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (1,1,50,"Exercise1User1Feup8File");




INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (3,1);


COMMIT TRANSACTION;
