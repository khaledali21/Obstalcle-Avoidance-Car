/*
 * LCD_cfg.h
 *
 * Created: 1/17/2022 1:00:23 PM
 *  Author: Khaled Ali
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_
#define  RS_PORT PORTA
#define RS_PIN PIN1
#define  RW_PORT PORTA
#define RW_PIN PIN2
#define  E_PORT PORTA
#define E_PIN PIN3
#define  D4_PORT PORTA
#define D4_PIN PIN4
#define  D5_PORT PORTA
#define D5_PIN PIN5
#define  D6_PORT PORTA
#define D6_PIN PIN6
#define  D7_PORT PORTA
#define D7_PIN PIN7


#define LCD_CLEAR 0x01
#define LCD_4BIT_MODE 0x28
#define LCD_8BIT_MODE 0x38
#define LCD_DISPLAY_ON 0x0C
#define LCD_SHIFT_CURSOR_RIGHT 0x06

#endif /* LCD_CFG_H_ */

