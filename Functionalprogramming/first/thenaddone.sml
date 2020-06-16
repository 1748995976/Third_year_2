fun square(x:int):int = x*x;
fun thenAddone((square:int->int),(x:int)) = square(x)+1;

thenAddone(square,2);