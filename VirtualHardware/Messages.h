#ifndef __ACROSS_LINKPROTOCOL__
#define __ACROSS_LINKPROTOCOL__
#include "../ACross.h"
#include "../ACLinkProtocol.h"

static const uint8_t AH_IN = 0x01;
static const uint8_t AH_REF = 0x4;
static const uint8_t AH_INREF = AH_IN | AH_REF;
static const uint8_t AH_OUT = 0x02 | AH_REF;
static const uint8_t AH_INOUT = AH_OUT | AH_IN;



union rpc_msg
{
	struct
	{
		uint8_t b0;
		uint8_t b1;
		uint8_t b2;
		uint8_t b3;
	};
	struct
	{
		uint16_t u0;
		uint16_t u1;
	};
	struct
	{
		int16_t i0;
		int16_t i1;
	};
	uint8_t raw[ACLINK_BUFFER_SIZE];

	template <class T>
	T& getValue(uint16_t offset)
	{
		return *((T*)(raw + offset));
	}
};


#define RPC_SIZES(...) { __VA_ARGS__ }
#define RPC_Q(...) { __VA_ARGS__ }


#define DEFINE_RPC(funcId,funcName,numParms,sizes,qualifiers) \
	static const uint16_t RPC_LEN_##funcName [ numParms ] = sizes  ;\
	static const uint8_t RPC_Q_##funcName [ numParms ] = qualifiers;\
	static const uint8_t RPC_NUMP_##funcName = (numParms);\
	static const uint16_t RPC_MSG_##funcName = (funcId); \
	void RPC_##funcName(rpc_msg&);

#define DEFINE_RPC_NO_PARMS(funcId,funcName) \
	static const uint8_t RPC_NUMP_##funcName = 0;\
	static const uint16_t RPC_MSG_##funcName = (funcId); \
	void RPC_##funcName (rpc_msg&);


#define DYNAMIC_SIZE 0

DEFINE_RPC(0, pinMode, 2, RPC_SIZES(sizeof(uint8_t), sizeof(uint8_t)), RPC_Q( AH_IN, AH_IN ));
DEFINE_RPC(1, digitalWrite, 2, RPC_SIZES(sizeof(uint8_t), sizeof(uint8_t)), RPC_Q(AH_IN, AH_IN));
DEFINE_RPC(2, analogWrite, 2, RPC_SIZES(sizeof(uint8_t), sizeof(int16_t)), RPC_Q(AH_IN, AH_IN));
DEFINE_RPC(3, digitalRead, 2, RPC_SIZES(sizeof(uint8_t), sizeof(int16_t)), RPC_Q(AH_IN, AH_OUT));
DEFINE_RPC(4, analogRead, 2, RPC_SIZES(sizeof(uint8_t), sizeof(int16_t)), RPC_Q(AH_IN, AH_OUT));
DEFINE_RPC_NO_PARMS(5, ACross_initSPI);
DEFINE_RPC(6, ACRoss_SPISendReceive, 5, RPC_SIZES(sizeof(uint8_t), sizeof(uint16_t), DYNAMIC_SIZE, sizeof(uint16_t), DYNAMIC_SIZE), RPC_Q(AH_IN, AH_IN, AH_INREF, AH_IN, AH_OUT))

#define invoke_RPC(func, ...) ACRPCCLient::invoke(RPC_MSG_##func , RPC_NUMP_##func , RPC_LEN_##func, RPC_Q_##func, __VA_ARGS__ )
#define invoke_RPC_NO_PARMS(func) ACRPCCLient::invoke(RPC_MSG_##func , 0 , NULL, NULL)


typedef void(*FunctionHandler)(rpc_msg& msg);
const FunctionHandler PROGMEM functionHandlers[] = { RPC_pinMode, RPC_digitalWrite, 
	RPC_analogWrite, RPC_digitalRead, RPC_analogRead,RPC_ACross_initSPI, RPC_ACRoss_SPISendReceive};



#endif