fun zip ([],[]): (string*int)list = []
    | zip([],y::L2) = []
    | zip(x::L1,[]) = []
    | zip(x::L1,y::L2) = (x,y)