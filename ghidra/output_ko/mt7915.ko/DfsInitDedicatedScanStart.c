// module: mt7915.ko
// function: DfsInitDedicatedScanStart @ 0x236424
// size: 32 bytes
//

void DfsInitDedicatedScanStart(int param_1)

{
  if (*(char *)(param_1 + 0x795405) != '\x01') {
    return;
  }
  *(undefined1 *)(param_1 + 0x795405) = 0;
  DfsDedicatedScanStart();
  return;
}

