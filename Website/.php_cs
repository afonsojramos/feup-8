<?php

$finder = PhpCsFixer\Finder::create()
    ->exclude('vendor')
    ->exclude('bootstrap')
    ->in(__DIR__)
;

return PhpCsFixer\Config::create()
    ->setRules([
        '@Symfony' => true,
        'braces' => ['allow_single_line_closure' => false, 'position_after_anonymous_constructs' => 'next', 'position_after_control_structures' => 'next', 'position_after_functions_and_oop_constructs' => 'next',],
    ])
    ->setFinder($finder)
;
