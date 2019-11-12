//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
	/*!
		\BT.h
		\Luis Alfonso
		\08/08/19
		\This BT.h works to configurate a BT module (HC-05)
	*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#ifndef BT_H_
#define BT_H_

		//--------------------------------------------------------------------------
	    // Functions
	    //--------------------------------------------------------------------------
/*!
 \fn void fnCheck(void)
 \brief This function works sending AT to the bluetooth and reciving a OK or ERROR depending if you are in the bluethooth commands or not.
 */
	void fnCheck(void);
/*!
 \fn void fnName_BT(void)
 \brief This function send AT+NAME=<newname> to the bluetooth and this one sends back a OK or ERROR depending if you can change it or not
 */
	void fnName_BT(void);
/*!
 \fn void fnPswd_BT(void)
 \brief This function send AT+PSWD=<newpasword> to the bluetooth and this one sends back a OK or ERROR depending if you can change it or not
*/
	void fnPswd_BT(void);
/*!
 \fn void fnAskAddress_BT(void)
 \brief This function send AT+ADDR? to the bluetooth and this one sends back the address of the bluetooth.
*/
	void fnAskAddress_BT(void);
/*!
 \fn void fnMaster_BT(void)
 \brief This function send AT+ROLE=1 to the bluetooth to make it master or a 0 if you want to be slave
*/
	void fnMaster_BT(void);
/*!
 \fn void fnMaster_BT(void)
 \brief This function send AT+CMODE=0 to the bluetooth to make the master conect to a specific bluetooth device and if it is a 0 you will configurate to any bluetooth available
*/
	void fnMode_BT(void);
/*!
 \fn void fnAddress_BT(void)
 \brief This function send AT+BIND=<Address> to the bluetooth and this will only connect to the bluetooth address that you want
*/
	void fnAddress_BT(void);

#endif /* 3_HAL_BT_H_ */
