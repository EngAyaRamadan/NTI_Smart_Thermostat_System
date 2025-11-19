#ifndef SIM_H
#define SIM_H
#define TINY_GSM_MODEM_SIM800
#define  SIM_BAUDRATE    9600
#define SIM_RX       16  
#define SIM_TX       17
#define SIM_Ready    1


typedef enum
{
  STATE_MODEM_RESTART,
  STATE_CHECK_SIM,
  STATE_WAIT_NETWORK,
  STATE_GPRS_CONNECT,
  STATE_SEND_MASSAGE,
  //STATE_TCP_CONNECT,
  //STATE_TCP_SEND,
  //STATE_TCP_RECEIVE,
  //STATE_TCP_CLOSE,
  STATE_IDLE,
  STATE_ERROR
} sim_state_t;





#endif