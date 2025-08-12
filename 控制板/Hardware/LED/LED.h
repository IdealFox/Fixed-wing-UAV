#ifndef __LED_H
#define __LED_H

#define  ON  1
#define	 OFF 0


void LED_Init(void);				//LED初始化

void RunLED_State(u8 state);
void EALED_State(u8 state);
void EN_AA_LED_State(u8 state);

#endif
