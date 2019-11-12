/*
 * PIT.h
 *
 *  Created on: 17/07/2019
 *      Author: Poncho
 */

#ifndef PIT_H_
#define PIT_H_

#define PIT_IRQ   PIT_DriverIRQHandler

   void PIT_vfnDriverInit(void);
   void PIT_vfnTimerEnable(void);
   void PIT_vfnTimerDisable(void);
   void PIT_IRQ(void);


#endif /* 1_APP_PIT_H_ */
