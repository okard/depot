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

def bar : $foo
{
}


def calc : function($a)
{
    return $a + 5;
}

$bar.test("Hello:");


$result = $calc(6);

echo $result


ls

