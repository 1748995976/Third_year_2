fun binarySearch(Empty:tree,i:int):bool = false 
     | binarySearch(Node(LN,x,RN), i) =
    case Int.compare(x,i) of
	    GREATER => binarySearch(LN,i)      
     | EQUAL => true 
     | LESS => binarySearch(RN,i);