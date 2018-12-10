BEGIN TRANSACTION;



INSERT INTO "users" (username, name, password, email, "isTeacher") VALUES ('Isaiah','Ferdinand T. Butler','FRE48IOE7HT','urna.nec.luctus@enim.co.uk', TRUE);
INSERT INTO "users" (username, name, password, email, "isTeacher") VALUES ('Orson','Eugenia Dudley','JMG12PLA8YG','amet.risus.Donec@dapibusrutrum.ca', TRUE);
INSERT INTO "users" (username, name, password, email, "isTeacher") VALUES ('Tatum','Sophia Cervantes','CMW89DLL3PF','rutrum.urna.nec@adlitoratorquent.ca', FALSE);



INSERT INTO "Exercise" (title, description, image_path, creator_id, "isPrivate") VALUES ('Add Numbers',
'I think you can add you to what you need to do.',
'1.png',2, FALSE);
INSERT INTO "Exercise" (title, description, image_path, creator_id, "isPrivate") VALUES ('Sub Numbers',
'You can add, but can you subtract?',
'2.png',2, FALSE);
INSERT INTO "Exercise" (title, description, image_path, creator_id, "isPrivate") VALUES ('Max Number',
'Is 4>1?',
'3.png',1, FALSE);
INSERT INTO "Exercise" (title, description, image_path, creator_id, "isPrivate") VALUES ('Max Number 2',
'Is 4>1? 2',
'4.png',1, FALSE);



INSERT INTO "Test" (test_code, title, hint, exercise_id ) VALUES ('function test_sum_correct()
luaunit.assertEquals(sum(3, 4, 7)
luaunit.assertEquals(sum(4, 3, 7)
luaunit.assertEquals(sum(3, 4, -1)
end','test_sum_correct','Test1HintExercise1', 1);
INSERT INTO "Test" (test_code, title, hint, exercise_id ) VALUES ('function test_sum_failing()
luaunit.assertEquals(sum(3, 4 , 8)
luaunit.assertEquals(sum(4, 3, 9)
luaunit.assertEquals(sum(3, 4, -7)
end','test_sum_failing','Test2HintExercise1', 1);
INSERT INTO "Test" (test_code, title, hint, exercise_id ) VALUES ('function test_sum_failing()
luaunit.assertEquals(sum(3, 4, 8)
luaunit.assertEquals(sum(4, 3, 9)
luaunit.assertEquals(sum(3, 4, -7)
end','test_sum_failing','Test1HintExercise2', 2);
INSERT INTO "Test" (test_code, title, hint, exercise_id ) VALUES ('function test_sum_failing2()
luaunit.assertEquals(sum(3, 4, 8)
luaunit.assertEquals(sum(4, 3, 9)
luaunit.assertEquals(sum(3, 4, -7)
end','test_sum_failing2','Test2HintExercise2', 2);
INSERT INTO "Test" (test_code, title, hint, exercise_id ) VALUES ('function test_sum_correct()
luaunit.assertEquals(sum(3, 4, 7)
luaunit.assertEquals(sum(4, 3, 7)
luaunit.assertEquals(sum(3, 4, -1)
end','test_sum_correct','Test1HintExercise3', 3);
INSERT INTO "Test" (test_code, title, hint, exercise_id ) VALUES ('function test_sum_correct2()
luaunit.assertEquals(sum(3, 4, 7)
luaunit.assertEquals(sum(4, 3, 7)
luaunit.assertEquals(sum(3, 4, -1)
end','test_sum_correct2','Test2HintExercise3', 3);
INSERT INTO "Test" (test_code, title, hint, exercise_id ) VALUES ('function test_sum_correct()
luaunit.assertEquals(sum(3, 4, 7)
luaunit.assertEquals(sum(4, 3, 7)
luaunit.assertEquals(sum(3, 4, -1)
end','test_sum_correct','Test1HintExercise3', 4);
INSERT INTO "Test" (test_code, title, hint, exercise_id ) VALUES ('function test_sum_correct2()
luaunit.assertEquals(sum(3, 4, 7)
luaunit.assertEquals(sum(4, 3, 7)
luaunit.assertEquals(sum(3, 4, -1)
end','test_sum_correct2','Test2HintExercise3', 4);





INSERT INTO "ExerciseStudent" (exercise_id, student_id, progress, "feup8_file") VALUES (1,3,44,'dfjldsjulkgjfdglkj');
INSERT INTO "ExerciseStudent" (exercise_id, student_id, progress, "feup8_file") VALUES (2,2,42,'dfjldsjulkgjfdglkj');
INSERT INTO "ExerciseStudent" (exercise_id, student_id, progress, "feup8_file") VALUES (3,1,32,'dfjldsjulkgjfdglkj');
INSERT INTO "ExerciseStudent" (exercise_id, student_id, progress, "feup8_file") VALUES (1,2,98,'dfjldsjulkgjfdglkj');
INSERT INTO "ExerciseStudent" (exercise_id, student_id, progress, "feup8_file") VALUES (2,3,24,'dfjldsjulkgjfdglkj');




INSERT INTO "ExerciseStudentPermissions" (exercise_id, student_id ) VALUES (4, 1);



COMMIT TRANSACTION;
