// module: switch.ko
// function: Alarm_Msg @ 0x16a48
// size: 180 bytes
//

int Alarm_Msg(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,ushort param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char acStack_30 [16];
  undefined4 local_20;
  undefined4 local_1c;
  
  __memzero(acStack_30,0x18);
  sprintf(acStack_30,"eth%d",(uint)param_5);
  if (param_2 == 1) {
    uVar2 = 0xa401;
  }
  else {
    uVar2 = 0xa402;
  }
  uVar3 = 0;
  uVar4 = 0;
  if (param_2 == 1) {
    local_20 = param_3;
    local_1c = param_4;
  }
  iVar1 = Kernel_ASEND("cspd.cspd.switch_mgr",uVar2);
  if (2 < g_switch_debug_level) {
    printk("Alarm_Msg port_name %s, port_rate(0-1G 1-100M 2-10M 3-Down 4-Error)%d port_mode(0-Half 1-Full)%d !\n"
           ,acStack_30,local_20,local_1c,uVar3,uVar4);
  }
  return iVar1 >> 0x1f;
}

