// module: mt7915.ko
// function: MAP_InsertMapWscAttr @ 0x15ffd8
// size: 152 bytes
//

undefined4 MAP_InsertMapWscAttr(undefined4 param_1,int param_2,undefined4 *param_3)

{
  undefined4 local_26;
  undefined2 local_22;
  
  local_22 = CONCAT11(*(undefined1 *)(param_2 + 0x3f5d),MAP_ATTRI_LEN);
  local_26 = CONCAT13(MAP_EXT_ATTRI,0x2a3700);
  *param_3 = 0x6004910;
  param_3[1] = local_26;
  *(undefined2 *)(param_3 + 2) = local_22;
  return 10;
}

