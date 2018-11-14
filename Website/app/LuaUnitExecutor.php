<?php

namespace App;

class LuaUnitExecutor
{
    private $executionTimeout = 2;

    public function __construct($code, $testCases)
    {
        $this->code = $code;
        $this->testCases = $testCases;
    }

    public function run()
    {
        $filename = $this->buildFile($this->code, $this->testCases);

        return $this->execute($filename, true);
    }

    public function buildFile($code, $testCases)
    {
        //include LuaUnit library
        $filetext = "\nlocal luaunit = require('luaunit')\n\n";

        //add user code
        $filetext .= $code."\n\n";

        //add each test case
        foreach ($testCases as $case)
        {
            $filetext .= $case."\n";
        }

        //add the test suite start-up code
        $filetext .= "local runner = luaunit.LuaUnit.new()\n";
        $filetext .= "runner:setOutputType('tap')\n";
        $filetext .= "os.exit( runner:runSuite() )\n";

        //save in unique file
        $filename = md5(uniqid(rand(), true)).'.lua';
        $file = fopen($filename, 'w');
        fwrite($file, $filetext);

        return $filename;
    }

    public function execute($file, $delete)
    {
        if ($this->hasSyntacticErrors($file))
        {
            return [-1, 'Student code has one or more syntactic errors'];
        }

        $cmd = 'timeout '.$this->executionTimeout.' lua '.$file;
        $output = [];
        $ret;
        exec($cmd, $output, $ret);

        if ($delete)
        {
            unlink($file);
        }

        if (empty($output))
        {
            $ret = -2;
            $output = 'Execution timed out before finishing';
        }

        return [$ret, $output];
    }

    private function hasSyntacticErrors($file)
    {
        $cmd = 'luajit -bl '.$file.' > /dev/null';
        $output = [];
        $ret;
        exec($cmd, $output, $ret);

        return 0 != $ret;
    }
}
