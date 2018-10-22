<?php

namespace Tests\Unit;

use Tests\TestCase;
use App\LuaUnitParser;

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
}
