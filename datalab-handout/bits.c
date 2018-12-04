/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  	return ~(~x | ~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	//return (x >> n) & 0xFF; ">>" is moving bits, not bytes.
	return (x >> (n << 3)) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	int mask = (~1)<<(32 + (~n));
	return (x >> n)&(~mask);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	int result = 0;

	int mask1_tmp = (0x55)|(0x55<<8);
	int mask1 = mask1_tmp|(mask1_tmp<<16);

	int mask2_tmp = (0x33)|(0x33<<8);
	int mask2 = mask2_tmp|(mask2_tmp<<16);

	int mask3_tmp = (0x0F)|(0x0F<<8);
	int mask3 = mask3_tmp|(mask3_tmp<<16);
	
	int mask4 = (0xFF)|(0xFF<<16);

	int mask5 = (0xFF)|(0xFF<<8);
	
	result = (x&mask1) + ((x>>1)&mask1);
	result = (result&mask2) + ((result>>2)&mask2);
	result = (result + (result>>4))&mask3;
	result = (result + (result>>8))&mask4;
	result = (result + (result>>16))&mask5;
	return result;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	int tmp = ~x + 1; //-x
	tmp = tmp|x; //when x == 0, results highest bit equals 0. when x == 0x80000000, we have tmp equals x. (when in 8-bit form, ~(-128)=127, then 127+1 = 128, which results 0x80).
	return (tmp>>31) + 1;//We are not allowed to use "if - else". We have to represent 1 or 0 in one expression.
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	int tmp1 = x<<(32 + (~n + 1));
	return !((tmp1>>(32 + (~n + 1)))^x);// tmp xor x. When they are the same, x can be represented as an n-bit, two's complement integer.
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	int sign = x>>31;
	int shift = (1<<n) + (~0);
	int bias = sign&shift;
	return (x + bias)>>n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	return !((x>>31)|(!x));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int signx = x>>31;
	int signy = y>>31;
	int signNotEqual = signx&(!signy);
	int signEqual = (!(signx^signy))&((x + ((~y) + 1))>>31);
	int Equal = (!(x^y));
	//We can also combine "signEqual" and "Equal" by "signEqual = (!(signx^signy))&((x + ((~y)))>>31);".
	//When we have x equals y, we get x + (~y) equals 11111111, where ~y = -y-1. Considering the condition that x and y have the same sign, The extreme condition of this change is that, x = INT_MIN, while y = -1. This extreme condition will not cause overflow :)
	return (signNotEqual|signEqual|Equal);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4

	* ilog2 is equivlance of finding the index of first 1 from left, the method is as following:
	* check whether x's left half bits are all 0's, if so then throw them away, 
	* else right shift to reject the right half(remember the 16 bits thrown from 
	* right), to repeat it until only one "1" remaining and return the remembered
	* number of x having been eliminated. 
	http://codejam.diandian.com/post/2011-04-16/428134

 */
int ilog2(int x) {
	int bitsnumber = (!!(x>>16))<<4;
	bitsnumber = bitsnumber + ((!!(x>>(bitsnumber + 8)))<<3);
	bitsnumber = bitsnumber + ((!!(x>>(bitsnumber + 4)))<<2);
	bitsnumber = bitsnumber + ((!!(x>>(bitsnumber + 2)))<<1);
	bitsnumber = bitsnumber + (!!(x>>(bitsnumber + 1)));
	bitsnumber = bitsnumber + (~0) + (!(!(0^x))); //subtract 1 when x==0.
  	return bitsnumber;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	int tmp = 0;
	int result = 0;
	result = uf^0x80000000;		//change sign bit, save as result.
	tmp = uf&0x7FFFFFFF;  	//get the remaining bits, without sign bit.	
	if(tmp > 0x7F800000)
		result = uf;		//When argument is NaN, return uf passed.
 	return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	unsigned shift_left = 0;
	unsigned after_shift = 0;
	unsigned tmp = 0;
	unsigned flag = 0;
	unsigned absX = x;
	unsigned sign = 0;
	
	if(x==0) 
		return 0;
	if(x < 0){
		sign = 0x80000000;
		absX = -x;	
	}
	after_shift = absX;
	while(1){
		tmp = after_shift;
		after_shift = after_shift<<1;
		shift_left++;
		if(tmp&0x80000000)
			break;
	}
	if((after_shift&0x01FF) > 0x0100)//Considering the sign bit and 8 exponent bits, the last 8+1 bits will be rounded. 
		flag = 1;
	else if((after_shift&0x03FF) == 0x0300)//round to even
		flag = 1;
	else
		flag = 0;

	return sign + (((32-shift_left)+127)<<23) + (after_shift>>9) + flag;//When calculating the exponent, the decimal is at the right of x. So we use 32-shift_left. 127 is the 32-bit float exponent bias.
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	if((uf&0x7F800000)==0){
		uf = ((uf&0x007FFFFF)<<1)|(uf&0x80000000);//Denormalized condition, just "<<" the fraction part.
	}
	else if((uf&(0x7F800000)) != 0x7F800000){
		uf = uf + 0x00800000;					  //Normalized condition, add 1 to exponent number.
	}
	//NaN and infinity condition, just return uf
	return uf;
}
