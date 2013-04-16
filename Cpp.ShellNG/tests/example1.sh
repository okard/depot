#!/usr/bin/env shellng

/*
Comment
*/

def foo : object
{
    def a : number = 5;

    def test : function($pre)
    {
        echo $pre $a
    }

}

def bar : $foo //copy of foo
{
}


def calc : function($a)
{
    return $a + 5;
}

$bar.test("Hello:");


$result = $calc(6);

echo $result

ls -alh $env["HOME"]


