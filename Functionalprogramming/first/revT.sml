fun revT (Empty:tree):tree = Empty
  | revT (Node(LN,x,RN)) = Node (revT (RN),x,revT (LN));