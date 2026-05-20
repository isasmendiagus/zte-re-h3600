// module: mt7915.ko
// function: mt_agent_exit_service @ 0x24fc4c
// size: 28 bytes
//

undefined4 mt_agent_exit_service(int *param_1)

{
  undefined4 uVar1;
  
  if (*param_1 != 1) {
    return 0x100;
  }
  uVar1 = mt_serv_exit_test(param_1[1]);
  return uVar1;
}

