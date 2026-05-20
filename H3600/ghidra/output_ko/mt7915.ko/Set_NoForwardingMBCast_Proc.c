// module: mt7915.ko
// function: Set_NoForwardingMBCast_Proc @ 0x295f4
// size: 152 bytes
//

undefined4
Set_NoForwardingMBCast_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *param_1;
  cVar1 = simple_strtol(param_2,0,10,param_4,param_4);
  if ((cVar1 != '\x01') && (cVar1 != '\0')) {
    return 0;
  }
  *(char *)(param_1 + (int)&DAT_000aed9c + *(int *)(iVar2 + 0x3c) * 0x160d) = cVar1;
  if (DebugLevel < 3) {
    return 1;
  }
  iVar2 = *(int *)(iVar2 + 0x3c);
  printk("IF(wlan5g%d) Set_NoForwardingMBCast_Proc::(IsolateInterStaMBCast=%d)\n",iVar2,
         (char)param_1[(int)&DAT_000aed9c + iVar2 * 0x160d]);
  return 1;
}

