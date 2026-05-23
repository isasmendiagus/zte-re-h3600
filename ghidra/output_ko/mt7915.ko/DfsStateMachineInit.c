// module: mt7915.ko
// function: DfsStateMachineInit @ 0x230078
// size: 112 bytes
//

void DfsStateMachineInit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  StateMachineInit(param_2,param_3,1,3,Drop,0,0);
  StateMachineSetAction(param_2,0,0,DfsCacEndUpdate);
  StateMachineSetAction(param_2,0,2,dfs_off_cac_end_update);
  return;
}

