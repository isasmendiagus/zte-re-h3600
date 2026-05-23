// module: mt7915.ko
// function: mt7915_iBFPhaseComp @ 0x892dc
// size: 64 bytes
//

void mt7915_iBFPhaseComp(int param_1,int param_2,void *param_3)

{
  if (param_2 != 0) {
    os_move_mem(param_3,(void *)(*(int *)(param_1 + 0xa78688) + (param_2 + -1) * 0x28),0x28);
    return;
  }
  os_move_mem(param_3,*(void **)(param_1 + 0xa78684),0x28);
  return;
}

