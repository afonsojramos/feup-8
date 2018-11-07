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
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (4,"Min Number",
"Is 1<2?",
"4.png",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (5,"iaculis quis, pede.","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam vestibulum","5.png",1,1);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (6,"Fusce mi lorem,","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper.","6.png",1,1);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (7,"ridiculus mus. Proin","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida","7.png",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (8,"nec enim. Nunc","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec","8.png",1,1);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (9,"lectus quis massa.","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut","9.png",2,1);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (10,"auctor ullamcorper, nisl","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a,","10.png",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (11,"egestas. Fusce aliquet","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque","11.png",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (12,"feugiat. Lorem ipsum","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu","12.png",2,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (13,"sapien, gravida non,","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat.","13.png",2,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (14,"quis arcu vel","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam vestibulum massa rutrum magna. Cras convallis convallis dolor. Quisque tincidunt pede ac","14.png",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (15,"eros turpis non","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam vestibulum massa rutrum magna. Cras convallis convallis dolor. Quisque tincidunt pede ac urna. Ut","15.png",1,1);


INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (1,"Isaiah","Ferdinand T. Butler","FRE48IOE7HT","urna.nec.luctus@enim.co.uk",1);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (2,"Orson","Eugenia Dudley","JMG12PLA8YG","amet.risus.Donec@dapibusrutrum.ca",1);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (3,"Tatum","Sophia Cervantes","CMW89DLL3PF","rutrum.urna.nec@adlitoratorquent.ca",0);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (4,"Hammett","Jael D. Howell","XSV76UZJ5WY","quam.quis@ultriciessem.co.uk",0);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (5,"Sonya","Christine A. Hawkins","YDE67XDJ6UC","eu.elit@Duissit.ca",0);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (6,"Katelyn","Winifred R. Hammond","IPN10RJD8FC","hendrerit.consectetuer@Nulla.com",0);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (7,"Chaney","Coby F. Bruce","QCD29VUZ9NX","mi.tempor.lorem@lectusrutrum.edu",0);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (8,"Wing","Justina L. Bradshaw","OBQ29NIK1XE","nunc.ac.mattis@lacinia.com",0);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (9,"Courtney","Shana H. Christensen","FGL38GRM9BX","nibh.Aliquam@gravida.ca",0);
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (10,"Kevin","Lucius G. Higgins","EFQ31AAC4BT","Cras.convallis@acipsum.org",0);






INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (1,"
function test1_sum()
    luaunit.assertEquals(sum(3,4) == 7)
    luaunit.assertEquals(sum(4,3) == 7)
    luaunit.assertEquals(sum(3,-4) == -1)
    luaunit.assertEquals(sum(-4,3) == -1)
    luaunit.assertEquals(sum(-4,-3) == -7)
    luaunit.assertEquals(sum(-3,-4) == -7)
end
","Can you add?","Function must be called sum",1);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (2,"
function test2_sub()
    luaunit.assertEquals(sub(3,4) == -1)
    luaunit.assertEquals(sub(4,3) == 1)
    luaunit.assertEquals(sub(3,-4) == 7)
    luaunit.assertEquals(sub(-4,3) == -7)
    luaunit.assertEquals(sub(-4,-3) == -1)
    luaunit.assertEquals(sub(-3,-4) == 1)
end
","Can you subtract?","Function must be called sub",2);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (3,"
function test3_max()
    luaunit.assertIsFunction( max )
    luaunit.assertEquals(max(3,4) == 4)
    luaunit.assertEquals(max(4,3) == 4)
    luaunit.assertEquals(max(3,-4) == 3)
    luaunit.assertEquals(max(-4,3) == 3)
    luaunit.assertEquals(max(-4,-3) == -3)
    luaunit.assertEquals(max(-3,-4) == -3)
end
","Can you get the max?","Function must be called max",3);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (4,"
function test3_min()
    luaunit.assertIsFunction( min )
    luaunit.assertEquals(min(3,4) == 3)
    luaunit.assertEquals(min(4,3) == 3)
    luaunit.assertEquals(min(3,-4) == -4)
    luaunit.assertEquals(min(-4,3) == -4)
    luaunit.assertEquals(min(-4,-3) == -4)
    luaunit.assertEquals(min(-3,-4) == -4)
end
","Can you get the min?","min",4);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (5,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","quis, pede. Suspendisse","lobortis quam a felis ullamcorper viverra. Maecenas",5);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (6,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","eu, eleifend","Donec vitae erat vel pede blandit congue.",6);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (7,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","ante bibendum","non quam. Pellentesque habitant morbi tristique",7);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (8,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","metus facilisis","Proin ultrices. Duis volutpat nunc sit amet metus.",8);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (9,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","sociis natoque penatibus","Duis cursus, diam at pretium aliquet, metus urna convallis erat,",9);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (10,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","convallis convallis dolor.","Sed eu nibh vulputate mauris sagittis placerat. Cras dictum",10);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (11,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","nonummy ac, feugiat","sit amet, consectetuer adipiscing elit. Etiam laoreet,",11);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (12,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","eu sem.","gravida sit amet, dapibus id, blandit",12);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (13,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","mollis dui,","libero. Donec consectetuer mauris id sapien. Cras",13);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (14,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","eget, ipsum. Donec","quis lectus. Nullam suscipit, est",14);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (15,"Z2RmZ2Rmc2twb2V3aXAwb3RvaTM0MGk0ZW9yZmdsa2Rqa2dmZGo5MzM0NDkwdDM0NDU2OQ==","est mauris,","semper pretium neque. Morbi quis",15);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (16,"
function test1_sum()
    luaunit.assertEquals(sum(3,4) == 7)
    luaunit.assertEquals(sum(4,3) == 7)
    luaunit.assertEquals(sum(3,-4) == -1)
    luaunit.assertEquals(sum(-4,3) == -1)
    luaunit.assertEquals(sum(-4,-3) == -7)
    luaunit.assertEquals(sum(-3,-4) == -7)
end
","can you add ? 2","semper pretium neque. Morbi quis",1);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES
(17,"
function test1_sum()
    luaunit.assertEquals(sum(3,4) == 7)
    luaunit.assertEquals(sum(4,3) == 7)
    luaunit.assertEquals(sum(3,-4) == -1)
    luaunit.assertEquals(sum(-4,3) == -1)
    luaunit.assertEquals(sum(-4,-3) == -7)
    luaunit.assertEquals(sum(-3,-4) == -7)
end
","can you add ? 3","semper pretium neque. Morbi quis",1);




INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (3,3,44,"dfjldsjulkgjfdglkj");
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (4,4,42,"dfjldsjulkgjfdglkj");
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (5,5,32,"dfjldsjulkgjfdglkj");
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (6,6,98,"dfjldsjulkgjfdglkj");
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`, 'feup8_file') VALUES (7,7,24,"dfjldsjulkgjfdglkj");




INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (1,3);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (2,4);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (3,5);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (4,6);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (5,7);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (6,8);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (7,9);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (8,10);



COMMIT TRANSACTION;
