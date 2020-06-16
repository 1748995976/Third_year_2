fun reverse [] = []
    | reverse (x::L) = reverse(L)@[x];

fun reverse' (L:int list):int list =
    let 
        fun helper(L:int list,R:int list):int list =
            case L of
                [] => R
            | x::L1 => helper (L1,x::R)
    in
        helper(L,[])
    end;
reverse' [3,2,1,0];