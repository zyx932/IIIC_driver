#ifndef __IIC_UTIL_H__
#define __IIC_UTIL_H__

#include <STC15F104E.H>
typedef unsigned char u8;

sbit scl = P3^3;
sbit sda = P3^2;

void Setup_IIC(bit cl,bit da){
		scl=cl;
		sda=da;
		scl=1;
		sda=1;
}

void IIC_start(){
	sda=1;
	scl=1;
	sda=0;
	scl=0;
}

void IIC_send(u8 bytes){
		int i;
		for(i=0;i<8;i++){
			sda=((0x80>>i) & bytes)==0? 0 : 1;
			scl=1;
			scl=0;
		}
}

void IIC_send_ack(){
		sda=1;
		scl=1;
		scl=0;
		sda=0;
}

void IIC_stop(){
		sda=0;
		scl=1;
		sda=1;
}

bit IIC_get_ack(){
		bit tmp;
		sda=1;
		scl=1;
		tmp=sda;
		scl=0;
		sda=1;
		return tmp;
}

unsigned int IIC_receive(){
		u8 tmp=0;
		int i;
		sda=1;
		for (i=0;i<8;i++){
				scl=1;
				tmp=(tmp<<1) | sda;
				scl=0;
		}
		return tmp;
}
#endif // __IIC_UTIL_H__