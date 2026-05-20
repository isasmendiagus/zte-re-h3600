// module: mt7915.ko
// function: HwCtrlSetClientMACEntry @ 0xaf7a8
// size: 48 bytes
//

undefined4 HwCtrlSetClientMACEntry(undefined4 param_1,int param_2)

{
  undefined2 *puVar1;
  
  puVar1 = *(undefined2 **)(param_2 + 8);
  AsicUpdateRxWCIDTable
            (param_1,*puVar1,puVar1 + 6,*(undefined1 *)((int)puVar1 + 0x1d),
             *(undefined1 *)(puVar1 + 0xf));
  return 0;
}

