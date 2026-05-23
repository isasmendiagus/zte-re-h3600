// module: mt7915.ko
// function: sta_mlme_search_wcid @ 0x556f8
// size: 20 bytes
//

undefined1 sta_mlme_search_wcid(void)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = MacTableLookup();
  uVar1 = 0;
  if (iVar2 != 0) {
    uVar1 = *(undefined1 *)(iVar2 + 0xe0);
  }
  return uVar1;
}

