
fun toInt (b:int)([]:int list):int = 0
    | toInt (b)(x::L) = x + b * (toInt(b)(L));
(* toInt(2)([1,1,1]); *)

fun toBase(b:int)(0:int):int list = []
    | toBase(b)(n) = (n mod b)::(toBase(b)(n div b));
(* toBase(2)(6); *)

fun convert(b1:int,b2:int)([]:int list):int list = []
    | convert(b1,b2)(L) = toBase(b2)(toInt(b1)(L));
convert(10,5)([2,4]);