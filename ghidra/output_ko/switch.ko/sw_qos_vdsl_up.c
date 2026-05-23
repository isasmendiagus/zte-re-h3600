// module: switch.ko
// function: sw_qos_vdsl_up @ 0x189fc
// size: 84 bytes
//

uint sw_qos_vdsl_up(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = dev_get_by_name(&init_net,&_LC0,param_3,param_4,param_4);
  if (iVar1 != 0) {
    uVar2 = *(uint *)(iVar1 + 0x138);
    disableIRQinterrupts();
    iVar3 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
    *(int *)(iVar3 + *(int *)(iVar1 + 0x280)) = *(int *)(iVar3 + *(int *)(iVar1 + 0x280)) + -1;
    return uVar2 & 1;
  }
  return 0;
}

