fun square(x:int):int = x*x;
fun mapList' (f:'a->'b)([]:'a list):'b list = []
    | mapList' (f)(x::L) = f(x)::mapList' (f)(L);
mapList'(square)([1,2,3,4]);