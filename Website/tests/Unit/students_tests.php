<?php

$test1_sum = 'function test1_sum()
luaunit.assertEquals(sum(3,4) , 7)
luaunit.assertEquals(sum(4,3) , 7)
luaunit.assertEquals(sum(3,-4) , -1)
luaunit.assertEquals(sum(-4,3) , -1)
luaunit.assertEquals(sum(-4,-3) , -7)
luaunit.assertEquals(sum(-3,-4) , -7)
end';
$test2_sub = 'function test2_sub()
luaunit.assertEquals(sub(3,4) , -1)
luaunit.assertEquals(sub(4,3) , 1)
luaunit.assertEquals(sub(3,-4) , 7)
luaunit.assertEquals(sub(-4,3) , -7)
luaunit.assertEquals(sub(-4,-3) , -1)
luaunit.assertEquals(sub(-3,-4) , 1)
end';
$test3_max = 'function test3_max()
luaunit.assertIsFunction( max )
luaunit.assertEquals(max(3,4) , 4)
luaunit.assertEquals(max(4,3) , 4)
luaunit.assertEquals(max(3,-4) , 3)
luaunit.assertEquals(max(-4,3) , 3)
luaunit.assertEquals(max(-4,-3) , -3)
luaunit.assertEquals(max(-3,-4) , -3)
end';
$test4_min = 'function test3_min()
luaunit.assertIsFunction( min )
luaunit.assertEquals(min(3,4) , 3)
luaunit.assertEquals(min(4,3) , 3)
luaunit.assertEquals(min(3,-4) , -4)
luaunit.assertEquals(min(-4,3) , -4)
luaunit.assertEquals(min(-4,-3) , -4)
luaunit.assertEquals(min(-3,-4) , -4)
end';
$testsArray = array($test1_sum, $test2_sub, $test3_max, $test4_min);
