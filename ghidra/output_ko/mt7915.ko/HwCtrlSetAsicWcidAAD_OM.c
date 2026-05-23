// module: mt7915.ko
// function: HwCtrlSetAsicWcidAAD_OM @ 0xaef80
// size: 28 bytes
//

undefined4
HwCtrlSetAsicWcidAAD_OM(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 *puVar1;
  
  puVar1 = *(undefined2 **)(param_2 + 8);
  AsicSetWcidAAD_OM(param_1,*puVar1,(int)*(char *)(puVar1 + 2),puVar1,param_4);
  return 0;
}

