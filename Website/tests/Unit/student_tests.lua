function test1_sum()
    luaunit.assertEquals(sum(3,4) == 7)
    luaunit.assertEquals(sum(4,3) == 7)
    luaunit.assertEquals(sum(3,-4) == -1)
    luaunit.assertEquals(sum(-4,3) == -1)
    luaunit.assertEquals(sum(-4,-3) == -7)
    luaunit.assertEquals(sum(-3,-4) == -7)
end

function test2_sub()
    luaunit.assertEquals(sub(3,4) == -1)
    luaunit.assertEquals(sub(4,3) == 1)
    luaunit.assertEquals(sub(3,-4) == 7)
    luaunit.assertEquals(sub(-4,3) == -7)
    luaunit.assertEquals(sub(-4,-3) == -1)
    luaunit.assertEquals(sub(-3,-4) == 1)
end

function test3_max()
    luaunit.assertIsFunction( max )
    luaunit.assertEquals(max(3,4) == 4)
    luaunit.assertEquals(max(4,3) == 4)
    luaunit.assertEquals(max(3,-4) == 3)
    luaunit.assertEquals(max(-4,3) == 3)
    luaunit.assertEquals(max(-4,-3) == -3)
    luaunit.assertEquals(max(-3,-4) == -3)
end

function test3_min()
    luaunit.assertIsFunction( min )
    luaunit.assertEquals(min(3,4) == 3)
    luaunit.assertEquals(min(4,3) == 3)
    luaunit.assertEquals(min(3,-4) == -4)
    luaunit.assertEquals(min(-4,3) == -4)
    luaunit.assertEquals(min(-4,-3) == -4)
    luaunit.assertEquals(min(-3,-4) == -4)
end