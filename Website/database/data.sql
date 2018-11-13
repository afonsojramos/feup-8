BEGIN TRANSACTION;


INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (1,"Add Numbers",
"I think you can add you to what you need to do."
,"1.png",2,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (2,"Sub Numbers",
"You can add, but can you subtract?",
"2.png",2,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (3,"Max Number",
"Is 4>1?",
"3.png",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (4,"Max Number 2",
"Is 4>1? 2",
"4.png",1,0);




INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (1,"Isaiah","Ferdinand T. Butler","FRE48IOE7HT","urna.nec.luctus@enim.co.uk",1);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (2,"Orson","Eugenia Dudley","JMG12PLA8YG","amet.risus.Donec@dapibusrutrum.ca",1);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (3,"Tatum","Sophia Cervantes","CMW89DLL3PF","rutrum.urna.nec@adlitoratorquent.ca",0);





INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (1,"function test_sum_correct()
luaunit.assertEquals(sum(3,4) , 7)
luaunit.assertEquals(sum(4,3) , 7)
luaunit.assertEquals(sum(3,-4) , -1)
end","test_sum_correct","Test1HintExercise1",1);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (2,"function test_sum_failing()
luaunit.assertEquals(sum(3,4) , 8)
luaunit.assertEquals(sum(4,3) , 9)
luaunit.assertEquals(sum(3,-4) , -7)
end","test_sum_failing","Test2HintExercise1",1);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (3,"function test_sum_failing()
luaunit.assertEquals(sum(3,4) , 8)
luaunit.assertEquals(sum(4,3) , 9)
luaunit.assertEquals(sum(3,-4) , -7)
end","test_sum_failing","Test1HintExercise2",2);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (4,"function test_sum_failing2()
luaunit.assertEquals(sum(3,4) , 8)
luaunit.assertEquals(sum(4,3) , 9)
luaunit.assertEquals(sum(3,-4) , -7)
end","test_sum_failing2","Test2HintExercise2",2);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (5,"function test_sum_correct()
luaunit.assertEquals(sum(3,4) , 7)
luaunit.assertEquals(sum(4,3) , 7)
luaunit.assertEquals(sum(3,-4) , -1)
end","test_sum_correct","Test1HintExercise3",3);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (6,"function test_sum_correct2()
luaunit.assertEquals(sum(3,4) , 7)
luaunit.assertEquals(sum(4,3) , 7)
luaunit.assertEquals(sum(3,-4) , -1)
end","test_sum_correct2","Test2HintExercise3",3);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (7,"function test_sum_correct()
luaunit.assertEquals(sum(3,4) , 7)
luaunit.assertEquals(sum(4,3) , 7)
luaunit.assertEquals(sum(3,-4) , -1)
end","test_sum_correct","Test1HintExercise3",4);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (8,"function test_sum_correct2()
luaunit.assertEquals(sum(3,4) , 7)
luaunit.assertEquals(sum(4,3) , 7)
luaunit.assertEquals(sum(3,-4) , -1)
end","test_sum_correct2","Test2HintExercise3",4);





INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (1,3,44,"dfjldsjulkgjfdglkj");
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (2,2,42,"dfjldsjulkgjfdglkj");
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (3,1,32,"dfjldsjulkgjfdglkj");
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (1,2,98,"dfjldsjulkgjfdglkj");
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (2,3,24,"dfjldsjulkgjfdglkj");




INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (4,1);



COMMIT TRANSACTION;
