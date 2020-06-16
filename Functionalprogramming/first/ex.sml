fun exists (f : 'a -> bool) (l : 'a list) : bool =
    foldr (fn (a,b) => f a orelse b) false l;
fun forall (f : 'a -> bool) (l : 'a list) : bool =
    foldr (fn (a,b) => f a andalso b) true l;