#!/usr/bin/env lua


local lu = require('luaunit')

TestToto = {} --class

    function TestToto:setUp()
        -- set up tests
        self.a = 1
        self.s = 'hop'
        self.t1 = {1,2,3}
        self.t2 = {one=1,two=2,three=3}
        self.t3 = {1,2,three=3}
    end

function test3()
    assert( 1 == 1)
    assert( 'a' == 'a')
end

local runner = lu.LuaUnit.new()
runner:setOutputType("tap")
os.exit( runner:runSuite() )
