fun mult [] = 1
    | mult(x::L) = x * mult(L);
fun multlist [] = 1
    | multlist(X::L) = mult(X)*multlist(L);
