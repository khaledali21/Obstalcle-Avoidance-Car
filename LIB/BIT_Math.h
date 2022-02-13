#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT) 	 (REG |= (1<<BIT))
#define CLR_BIT(REG,BIT) 	 (REG &=~ (1<<BIT))
#define Toggle_BIT(REG,BIT)  (REG ^= (1<<BIT))
#define GET_BIT(REG,BIT) 	 ((REG >> BIT) & (0X01))
#define abs(x,y)			 (x > y? x - y : y - x)
#define ASSIGN_HIGH_NIB(reg,value)	((reg)=((value<<4)|(reg&0X0F)))
#endif /* BIT_MATH_H_ */
