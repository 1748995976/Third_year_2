fun split (L:int list) = 
    let
      val mid = (length L) div 2
      val left = (List.take (L,mid))
      val x :: right = (List.drop (L,mid))
    in
      (left,x,right)
    end;

(* datatype tree = Empty | Node of tree*int*tree; *)


fun listToTree ([]:int list):tree = Empty
     | listToTree(L) = 
     let
        val (LN,x,RN) = split(L)
     in
        Node (listToTree(LN),x,listToTree(RN))
     end;

listToTree [1,2,3,4,5,6,7,8,9];