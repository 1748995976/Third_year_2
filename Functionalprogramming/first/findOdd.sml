fun findOdd([]:int list):int option = NONE
    | findOdd(x::L) = if((x mod 2) = 1)
        then SOME x
        else findOdd(L);
findOdd([2,4,6,8,5,1,3]);