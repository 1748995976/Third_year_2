#############################################################
#�ж���ʾ���򣬼������Ʋ��ԣ�����1�ż�������1ѭ����λ����
#�ж���ʾ���򣬼������Ʋ��ԣ�����2�ż�������2ѭ����λ����
#���Ҳ���ʾ������ѭ������
#��ֻ���жϷ��������ʾ���򣬷����Ҽ���ж�Ƕ�ף�
#���ʱ��Ҫ���ǿ��жϣ����жϣ������ж����������������ָ��ʵ�֣���α����ֳ����ж���ָ����Ҫ��������
#############################################################
.text
j BenchmarkStart	#��ת��benchmark��
addi $sp,$sp,-4   #1~6�żĴ�����ջ
sw $1,0($sp)
addi $sp,$sp,-4
sw $2,0($sp)
addi $sp,$sp,-4
sw $3,0($sp)
addi $sp,$sp,-4
sw $4,0($sp)
addi $sp,$sp,-4
sw $5,0($sp)
addi $sp,$sp,-4
sw $6,0($sp)
addi $sp,$sp,-4	#16��17��19��20��21��22�żĴ�����ջ
sw $16,0($sp)	
addi $sp,$sp,-4
sw $17,0($sp)
addi $sp,$sp,-4
sw $19,0($sp)
addi $sp,$sp,-4
sw $20,0($sp)
addi $sp,$sp,-4
sw $21,0($sp)
addi $sp,$sp,-4
sw $22,0($sp)

#MFC0 $1,$1	#�����ֵ��Ĵ���$1
#$1��������ѹջ
addi $sp,$sp,-4
sw $1,0($sp)

#MFC0 $2,$2	#EPC���Ĵ���$2
#$2��EPCѹջ
addi $sp,$sp,-4
sw $2,0($sp)
#ջ��-EPC-������-$31-$0

addi $1,$0,0x3	#1���жϵ������֣�4λ
#MTC0 $1,$1	#����������Ϊ0011	# 3��2�ſɴ�ϣ�1��0�Ų��ɴ�ϣ�����0���ڴ�ʵ������

addi $3,$0,0x1	#IE���Ĵ���$3��Ϊ1
#MTC0 $3,$3	#���ж�

addi $s6,$zero,1       #�жϺ�1,2,3   ��ͬ�жϺ���ʾֵ��һ��
addi $s4,$zero,6      #ѭ��������ʼֵ  
addi $s5,$zero,1       #�������ۼ�ֵ
###################################################################
#                �߼����ƣ�ÿ����λ4λ 
# ��ʾ����������ʾ0x00000016 0x00000106 0x00001006 0x00010006 ... 10000006  00000006 ����ѭ��6��
###################################################################
IntLoop1:
add $s0,$zero,$s6   
IntLeftShift1:       
sll $s0, $s0, 4  
or $s3,$s0,$s4
add    $a0,$0,$s3       #display $s0
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.   

bne $s0, $zero, IntLeftShift1
sub $s4,$s4,$s5      #ѭ�������ݼ�
bne $s4, $zero, IntLoop1

#MTC0 $0,$3	#���ж� ֱ����0�żĴ���ֵ��IE
#EPC��ջ$2
lw $2,0($sp)
addi $sp,$sp,4
#MTC0 $2,$2	#$2�ָ�EPC
#�����ֳ�ջ$1
lw $1,0($sp)
addi $sp,$sp,4
#MTC0 $1,$1	#$1�ָ�������

# 22��21��20��19��17��16�żĴ�����ջ
lw $22,0($sp)
addi $sp,$sp,4
lw $21,0($sp)
addi $sp,$sp,4
lw $20,0($sp)
addi $sp,$sp,4
lw $19,0($sp)
addi $sp,$sp,4
lw $17,0($sp)
addi $sp,$sp,4
lw $16,0($sp)
addi $sp,$sp,4
#1~6�żĴ�����ջ
lw $6,0($sp)
addi $sp,$sp,4
lw $5,0($sp)
addi $sp,$sp,4
lw $4,0($sp)
addi $sp,$sp,4
lw $3,0($sp)
addi $sp,$sp,4
lw $2,0($sp)
addi $sp,$sp,4
lw $1,0($sp)
addi $sp,$sp,4

eret



addi $sp,$sp,-4   #1~6�żĴ�����ջ
sw $1,0($sp)
addi $sp,$sp,-4
sw $2,0($sp)
addi $sp,$sp,-4
sw $3,0($sp)
addi $sp,$sp,-4
sw $4,0($sp)
addi $sp,$sp,-4
sw $5,0($sp)
addi $sp,$sp,-4
sw $6,0($sp)
addi $sp,$sp,-4	#16��17��19��20��21��22�żĴ�����ջ
sw $16,0($sp)	
addi $sp,$sp,-4
sw $17,0($sp)
addi $sp,$sp,-4
sw $19,0($sp)
addi $sp,$sp,-4
sw $20,0($sp)
addi $sp,$sp,-4
sw $21,0($sp)
addi $sp,$sp,-4
sw $22,0($sp)

#MFC0 $1,$1	#�����ֵ��Ĵ���$1
#$1��������ѹջ
addi $sp,$sp,-4
sw $1,0($sp)

#MFC0 $2,$2	#EPC���Ĵ���$2
#$2��EPCѹջ
addi $sp,$sp,-4
sw $2,0($sp)
#ջ��-EPC-������-$31-$0

addi $1,$0,0x7	#2���жϵ������֣�4λ
#MTC0 $1,$1	#����������Ϊ0111

addi $3,$0,0x1	#IE��Ϊ1
#MTC0 $3,$3	#���ж�

addi $s6,$zero,2       #�жϺ�1,2,3   ��ͬ�жϺ���ʾֵ��һ��
addi $s4,$zero,6      #ѭ��������ʼֵ  
addi $s5,$zero,1       #�������ۼ�ֵ
###################################################################
#                �߼����ƣ�ÿ����λ4λ 
# ��ʾ����������ʾ0x00000026 0x00000206 0x00002006 0x00020006 ... 20000006  00000006 ����ѭ��6��
###################################################################
IntLoop2:
add $s0,$zero,$s6   
IntLeftShift2:       
sll $s0, $s0, 4  
or $s3,$s0,$s4
add    $a0,$0,$s3       #display $s0
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.   

bne $s0, $zero, IntLeftShift2
sub $s4,$s4,$s5      #ѭ�������ݼ�
bne $s4, $zero, IntLoop2

#MTC0 $0,$3	#���ж�
#EPC��ջ$2
lw $2,0($sp)
addi $sp,$sp,4
#MTC0 $2,$2	#$2�ָ�EPC
#�����ֳ�ջ$1
lw $1,0($sp)
addi $sp,$sp,4
#MTC0 $1,$1	#$1�ָ�������

# 22��21��20��19��17��16�żĴ�����ջ
lw $22,0($sp)
addi $sp,$sp,4
lw $21,0($sp)
addi $sp,$sp,4
lw $20,0($sp)
addi $sp,$sp,4
lw $19,0($sp)
addi $sp,$sp,4
lw $17,0($sp)
addi $sp,$sp,4
lw $16,0($sp)
addi $sp,$sp,4
#1~6�żĴ�����ջ
lw $6,0($sp)
addi $sp,$sp,4
lw $5,0($sp)
addi $sp,$sp,4
lw $4,0($sp)
addi $sp,$sp,4
lw $3,0($sp)
addi $sp,$sp,4
lw $2,0($sp)
addi $sp,$sp,4
lw $1,0($sp)
addi $sp,$sp,4

eret



addi $sp,$sp,-4   #1~6�żĴ�����ջ
sw $1,0($sp)
addi $sp,$sp,-4
sw $2,0($sp)
addi $sp,$sp,-4
sw $3,0($sp)
addi $sp,$sp,-4
sw $4,0($sp)
addi $sp,$sp,-4
sw $5,0($sp)
addi $sp,$sp,-4
sw $6,0($sp)
addi $sp,$sp,-4	#16��17��19��20��21��22�żĴ�����ջ
sw $16,0($sp)	
addi $sp,$sp,-4
sw $17,0($sp)
addi $sp,$sp,-4
sw $19,0($sp)
addi $sp,$sp,-4
sw $20,0($sp)
addi $sp,$sp,-4
sw $21,0($sp)
addi $sp,$sp,-4
sw $22,0($sp)

#MFC0 $1,$1	#�����ֵ��Ĵ���$1
#$1��������ѹջ
addi $sp,$sp,-4
sw $1,0($sp)

#MFC0 $2,$2	#EPC���Ĵ���$2
#$2��EPCѹջ
addi $sp,$sp,-4
sw $2,0($sp)
#ջ��-EPC-������-$31-$0

addi $1,$0,0xf	#3���жϵ������֣�4λ
#MTC0 $1,$1	#����������Ϊ1111

addi $3,$0,0x1	#IE��Ϊ1
#MTC0 $3,$3	#���ж�

addi $s6,$zero,3       #�жϺ�1,2,3   ��ͬ�жϺ���ʾֵ��һ��
addi $s4,$zero,6      #ѭ��������ʼֵ  
addi $s5,$zero,1       #�������ۼ�ֵ
###################################################################
#                �߼����ƣ�ÿ����λ4λ 
# ��ʾ����������ʾ0x00000036 0x00000306 0x00003006 0x00030006 ... 30000006  00000006 ����ѭ��6��
###################################################################
IntLoop3:
add $s0,$zero,$s6   
IntLeftShift3:       
sll $s0, $s0, 4  
or $s3,$s0,$s4
add    $a0,$0,$s3       #display $s0
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.   

bne $s0, $zero, IntLeftShift3
sub $s4,$s4,$s5      #ѭ�������ݼ�
bne $s4, $zero, IntLoop3

#MTC0 $0,$3	#���ж�
#EPC��ջ$2
lw $2,0($sp)
addi $sp,$sp,4
#MTC0 $2,$2	#$2�ָ�EPC
#�����ֳ�ջ$1
lw $1,0($sp)
addi $sp,$sp,4
#MTC0 $1,$1	#$1�ָ�������

# 22��21��20��19��17��16�żĴ�����ջ
lw $22,0($sp)
addi $sp,$sp,4
lw $21,0($sp)
addi $sp,$sp,4
lw $20,0($sp)
addi $sp,$sp,4
lw $19,0($sp)
addi $sp,$sp,4
lw $17,0($sp)
addi $sp,$sp,4
lw $16,0($sp)
addi $sp,$sp,4
#1~6�żĴ�����ջ
lw $6,0($sp)
addi $sp,$sp,4
lw $5,0($sp)
addi $sp,$sp,4
lw $4,0($sp)
addi $sp,$sp,4
lw $3,0($sp)
addi $sp,$sp,4
lw $2,0($sp)
addi $sp,$sp,4
lw $1,0($sp)
addi $sp,$sp,4

eret

#interupt demo  main program 
#1st section, auto decrement counter and display
#2nd section: ccmb instruction test
BenchmarkStart:
addi $s1,$zero,0x200      #initial nubmer
addi $v0,$zero,34    
counter_branch:
add $a0,$0,$s1          
syscall                 #display number
addi $s1,$s1,-1         #decrement
bne $s1,$zero,counter_branch
nop
nop
nop
nop
addi $v0,$zero,10
syscall                 #pause
############################################
# insert your ccmb benchmark program here!!!
#C1 instruction



#C2 instruction



#Mem instruction




#Branch instruction




addi $v0,$zero,10
syscall                 #pause











