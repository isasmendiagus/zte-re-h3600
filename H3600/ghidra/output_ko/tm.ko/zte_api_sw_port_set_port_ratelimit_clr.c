// module: tm.ko
// function: zte_api_sw_port_set_port_ratelimit_clr @ 0x6bd2c
// size: 88 bytes
//

void zte_api_sw_port_set_port_ratelimit_clr(void)

{
  uint uVar1;
  undefined4 in_r3;
  undefined4 extraout_r3;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  uVar2 = 0;
  iVar3 = 1;
  do {
    bVar4 = uVar2 != 5;
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    if (bVar4) {
      zte_api_sw_port_set_port_ratelimit(uVar1,2,0,in_r3,0,0,0);
      in_r3 = extraout_r3;
      if (iVar3 == 8) {
        return;
      }
    }
    iVar3 = iVar3 + 1;
  } while( true );
}

