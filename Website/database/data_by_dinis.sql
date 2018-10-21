BEGIN TRANSACTION;


INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (1,"sit amet metus.","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat.","1.png",2,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (2,"ac mattis semper,","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam","2.png",2,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (3,"magnis dis parturient","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam vestibulum massa","3.png",1,0);
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (4,"penatibus et magnis","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien,","4.png",1,0);
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






INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (1,"Suspendisse sed dolor. Fusce mi lorem, vehicula et, rutrum eu, ultrices sit amet, risus. Donec","Duis elementum,","ac, fermentum vel, mauris. Integer sem elit, pharetra ut,",1);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (2,"velit. Cras lorem lorem, luctus ut, pellentesque eget, dictum placerat, augue. Sed molestie. Sed id risus quis diam","consequat purus. Maecenas","at lacus. Quisque purus sapien,",2);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (3,"gravida molestie arcu. Sed eu nibh vulputate mauris sagittis placerat. Cras dictum ultricies ligula. Nullam enim. Sed nulla ante, iaculis","aliquam eros turpis","montes, nascetur ridiculus mus. Proin vel nisl. Quisque",3);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (4,"nunc sed pede. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Proin vel arcu eu","erat vel pede","quis turpis vitae purus gravida sagittis.",4);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (5,"Fusce aliquet magna a neque. Nullam ut nisi a odio semper cursus. Integer mollis. Integer tincidunt aliquam arcu. Aliquam","quis, pede. Suspendisse","lobortis quam a felis ullamcorper viverra. Maecenas",5);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (6,"dictum cursus. Nunc mauris elit, dictum eu, eleifend nec, malesuada ut, sem. Nulla interdum. Curabitur dictum. Phasellus","eu, eleifend","Donec vitae erat vel pede blandit congue.",6);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (7,"orci quis lectus. Nullam suscipit, est ac facilisis facilisis, magna tellus faucibus leo, in lobortis tellus justo sit","ante bibendum","non quam. Pellentesque habitant morbi tristique",7);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (8,"dui. Fusce aliquam, enim nec tempus scelerisque, lorem ipsum sodales purus, in molestie tortor nibh sit amet","metus facilisis","Proin ultrices. Duis volutpat nunc sit amet metus.",8);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (9,"mauris blandit mattis. Cras eget nisi dictum augue malesuada malesuada. Integer id magna et ipsum cursus","sociis natoque penatibus","Duis cursus, diam at pretium aliquet, metus urna convallis erat,",9);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (10,"odio. Aliquam vulputate ullamcorper magna. Sed eu eros. Nam consequat dolor vitae dolor. Donec fringilla. Donec feugiat metus sit amet","convallis convallis dolor.","Sed eu nibh vulputate mauris sagittis placerat. Cras dictum",10);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (11,"lectus pede, ultrices a, auctor non, feugiat nec, diam. Duis mi enim, condimentum eget, volutpat ornare, facilisis eget,","nonummy ac, feugiat","sit amet, consectetuer adipiscing elit. Etiam laoreet,",11);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (12,"sem, vitae aliquam eros turpis non enim. Mauris quis turpis vitae purus gravida sagittis. Duis gravida. Praesent eu nulla at","eu sem.","gravida sit amet, dapibus id, blandit",12);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (13,"interdum feugiat. Sed nec metus facilisis lorem tristique aliquet. Phasellus fermentum convallis ligula. Donec luctus aliquet odio. Etiam","mollis dui,","libero. Donec consectetuer mauris id sapien. Cras",13);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (14,"nec tellus. Nunc lectus pede, ultrices a, auctor non, feugiat nec, diam. Duis mi enim, condimentum eget, volutpat","eget, ipsum. Donec","quis lectus. Nullam suscipit, est",14);
INSERT INTO `Test` (`id`,`test_code`,`title`,`hint`,`exercise_id`) VALUES (15,"dictum. Phasellus in felis. Nulla tempor augue ac ipsum. Phasellus vitae mauris sit amet lorem","est mauris,","semper pretium neque. Morbi quis",15);






INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`) VALUES (3,3,44);
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`) VALUES (4,4,42);
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`) VALUES (5,5,32);
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`) VALUES (6,6,98);
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`) VALUES (7,7,24);




INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (1,3);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (2,4);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (3,5);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (4,6);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (5,7);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (6,8);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (7,9);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (8,10);



COMMIT TRANSACTION;