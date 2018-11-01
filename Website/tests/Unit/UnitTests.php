<?php

namespace Tests\Unit;

use Tests\TestCase;
use App\LuaUnitParser;
use App\LuaUnitExecutor;

/**
  * All unit tests should go here
  * To write to console with phpunit, use
  *             fwrite(STDERR, print_r($my_string, TRUE));
  */
class UnitTests extends TestCase
{
    public function testParser()
    {
        $parser = new LuaUnitParser;
        $this->assertNotEquals($parser, NULL);

        //check if the parser is working with a small input
        $input =
'1..15
# Started on Sat Oct 20 16:50:54 2018
# Starting class: TestTiti
not ok 1	TestTiti.test1_withFailure
#   lua_unit_example.lua:104: expected: 2, actual: 1
not ok 2	TestTiti.test2_withFailure
#   lua_unit_example.lua:113: expected: "bof"
#   actual: "hop"
ok     3	TestTiti.test3
# Ran 15 tests in 0.001 seconds, 3 successes, 8 failures, 4 errors';
        $expectedOutput = [
            "TestTiti.test1_withFailure" => false,
            "TestTiti.test2_withFailure" => false,
            "TestTiti.test3" => true
        ];
        $actualOutput = $parser->parseInternal($input);
        $this->assertEquals($actualOutput, $expectedOutput);

        //check if the result is convertible into JSON
        $actualEncoded = $parser->parse($input);
        $expectedEncoded = '{"TestTiti.test1_withFailure":false,"TestTiti.test2_withFailure":false,"TestTiti.test3":true}';
        $this->assertEquals($actualEncoded, $expectedEncoded);

        //try this with a full input
        $input = file_get_contents("tests/Unit/parser_test_input.txt");
        $expectedOutput = file_get_contents("tests/Unit/parser_test_output.txt");
        $expectedOutput = str_replace("\n", "", $expectedOutput);
        $actualOutput = $parser->parse($input);
        $this->assertEquals($actualOutput, $expectedOutput);
    }

    public function testExec()
    {
        include "tests/Unit/students_tests.php";

        $studentCode = file_get_contents("tests/Unit/student_res.lua");
        $testCases = $testsArray;
        $thread = new LuaUnitExecutor($studentCode, $testCases);

        //tests for exec
        $actualRes = $thread->execute("tests/Unit/lua_example_syntax.lua", false)[0];
        $this->assertEquals($actualRes, -1);
 
        $actualRes = $thread->execute("tests/Unit/lua_example_pass.lua", false)[0];
        $this->assertEquals($actualRes, 0);

        $actualRes = $thread->execute("tests/Unit/lua_example_fail.lua", false)[0];
        $this->assertTrue($actualRes > 0);

        $actualRes = $thread->execute("tests/Unit/lua_example_cycle.lua", false)[0];
        $this->assertEquals($actualRes, -2);

        //tests for the whole class (building file + execution)
        $res = $thread->run();
        $this->assertEquals($res[0], 0);

        //test with infinite cycle
        $studentCode = file_get_contents("tests/Unit/student_res_cycle.lua");
        $testCases = $testsArray;
        $thread = new LuaUnitExecutor($studentCode, $testCases);
        $res = $thread->run();
        $this->assertEquals($res[0], -2);

    }
}
