fun interleave (L1:int list,L2:int list):int list =
    case (L1,L2) of
       ([],_) => L2
     | (_,[]) => L1
     | (x::L_1,y::L_2) => x::(y::interleave(L_1,L_2));
interleave ([1,3,5],[2,4,6,7,8,9]);