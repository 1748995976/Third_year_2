fun divisibleByThree (n:int) : bool =
if n = 0 then true else
if n < 3 then false else
divisibleByThree(n-3);
