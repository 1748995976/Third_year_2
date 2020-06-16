fun subsetSumOption(x:int list,0:int) = SOME []
    | subsetSumOption([],sum) = NONE
    | subsetSumOption(x::L,sum) = 
    if(subsetSumOption(L,sum-x) = NONE)
    then subsetSumOption(L,sum)
    else
    SOME(x::valueOf(subsetSumOption(L,sum-x)));