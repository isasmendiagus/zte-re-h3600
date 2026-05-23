// module: mt7915.ko
// function: sta_media_state_connected @ 0x6880c
// size: 36 bytes
//

uint sta_media_state_connected(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = GetStaCfgByWdev(*(undefined4 *)(param_1 + 8),param_1,param_3,param_4,param_4);
  return (uint)(*(int *)(iVar1 + 0x212464) << 0x18) >> 0x1f;
}

