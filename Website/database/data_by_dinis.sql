BEGIN TRANSACTION;

INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (1,"sit amet metus.","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat.","1.png",2,"false");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (2,"ac mattis semper,","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam","2.png",2,"true");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (3,"magnis dis parturient","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam vestibulum massa","3.png",1,"false");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (4,"penatibus et magnis","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien,","4.png",1,"false");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (5,"iaculis quis, pede.","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam vestibulum","5.png",1,"true");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (6,"Fusce mi lorem,","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper.","6.png",1,"true");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (7,"ridiculus mus. Proin","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida","7.png",1,"false");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (8,"nec enim. Nunc","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec","8.png",1,"true");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (9,"lectus quis massa.","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut","9.png",2,"true");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (10,"auctor ullamcorper, nisl","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a,","10.png",1,"false");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (11,"egestas. Fusce aliquet","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque","11.png",1,"false");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (12,"feugiat. Lorem ipsum","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu","12.png",2,"false");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (13,"sapien, gravida non,","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat.","13.png",2,"false");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (14,"quis arcu vel","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam vestibulum massa rutrum magna. Cras convallis convallis dolor. Quisque tincidunt pede ac","14.png",1,"false");
INSERT INTO `Exercise` (`id`,`title`,`description`,`image_path`,`creator_id`,`isPrivate`) VALUES (15,"eros turpis non","Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam vestibulum massa rutrum magna. Cras convallis convallis dolor. Quisque tincidunt pede ac urna. Ut","15.png",1,"true");




INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (3,"Tatum","Sophia Cervantes","CMW89DLL3PF","rutrum.urna.nec@adlitoratorquent.ca","false");
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (4,"Hammett","Jael D. Howell","XSV76UZJ5WY","quam.quis@ultriciessem.co.uk","false");
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (5,"Sonya","Christine A. Hawkins","YDE67XDJ6UC","eu.elit@Duissit.ca","false");
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (6,"Katelyn","Winifred R. Hammond","IPN10RJD8FC","hendrerit.consectetuer@Nulla.com","false");
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (7,"Chaney","Coby F. Bruce","QCD29VUZ9NX","mi.tempor.lorem@lectusrutrum.edu","false");
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (8,"Wing","Justina L. Bradshaw","OBQ29NIK1XE","nunc.ac.mattis@lacinia.com","false");
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (9,"Courtney","Shana H. Christensen","FGL38GRM9BX","nibh.Aliquam@gravida.ca","false");
INSERT INTO `users` (`id`,`username`,`name`,`password`,`email`,`isTeacher`) VALUES (10,"Kevin","Lucius G. Higgins","EFQ31AAC4BT","Cras.convallis@acipsum.org","false");





INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`,`feup8_file`) VALUES (3,1,44,'a');
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`,`feup8_file`) VALUES (4,4,42,'a');
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`,`feup8_file`) VALUES (5,5,32,'a');
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`,`feup8_file`) VALUES (6,6,98,'a');
INSERT INTO `ExerciseStudent` (`exercise_id`,`student_id`,`progress`,`feup8_file`) VALUES (7,7,24,'a');




INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (1,2);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (2,4);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (3,5);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (4,6);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (5,7);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (6,8);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (7,9);
INSERT INTO `ExerciseStudentPermissions` (`exercise_id`,`student_id`) VALUES (8,10);



COMMIT TRANSACTION;
