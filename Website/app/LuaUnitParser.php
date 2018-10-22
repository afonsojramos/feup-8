<?php

namespace App;

use Illuminate\Support\Str;

class LuaUnitParser
{
    public function parseInternal($text)
    {
        $parsed = [];

        $lines = explode("\n", $text);

        foreach ($lines as $line)
        {
            if (Str::startsWith($line, "1") || Str::startsWith($line, "#") || strlen($line) < 1)
                continue;

            $line = str_replace("\t", " ", $line);
            $elements = explode(" ", $line);

            $parsed[end($elements)] = (strcmp($elements[0], "ok") == 0);
        }

        return $parsed;
    }

    public function parse($text)
    {
        $parsed = $this->parseInternal($text);
        return json_encode($parsed);
    }
}
