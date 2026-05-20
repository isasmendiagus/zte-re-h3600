// module: mt7915.ko
// function: ZTE_Set_Enable_Air_Monitor_Proc @ 0x40018
// size: 128 bytes
//

undefined4
ZTE_Set_Enable_Air_Monitor_Proc
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  
  if (0 < DebugLevel) {
    printk("--> %s()\n","ZTE_Set_Enable_Air_Monitor_Proc",param_3,DebugLevel,param_4);
  }
  uVar1 = simple_strtol(param_2,0,10);
  asic_set_air_mon_enable(param_1,uVar1,param_3);
  if (0 < DebugLevel) {
    printk("<-- %s()\n","ZTE_Set_Enable_Air_Monitor_Proc");
  }
  return 1;
}

