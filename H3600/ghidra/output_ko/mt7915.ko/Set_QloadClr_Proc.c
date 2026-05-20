// module: mt7915.ko
// function: Set_QloadClr_Proc @ 0x27794
// size: 36 bytes
//

undefined4 Set_QloadClr_Proc(undefined4 param_1)

{
  QBSS_LoadStatusClear(param_1,1);
  QBSS_LoadStatusClear(param_1,0x24);
  return 1;
}

