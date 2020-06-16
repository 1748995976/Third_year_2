fun square(x:int):int = x*x;
fun mapList(f:'a->'b,[]:'a list):'b list = []
    | mapList(f,L) = map (fn sq(x) => square(x)) L;
mapList(square,[1,2,3,4]);