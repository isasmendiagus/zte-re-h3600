# Live-vs-live register diff — mainline (with all fixes thru broadcast-flood) vs stock

Method: added debugfs `regdump` (hex-text `<phys> <value>` per u32) to the driver,
cat over socket 9999 TWICE, kept only regs where both captures agreed (768/768
agreed — hex-text is fully reliable over the glitchy UART, unlike raw binary).
Diffed against `regs/stock_eth_2mib.txt`. Date 2026-05-28.

phys = 0x921c0000 + e->base offset. 53 divergences:

## MAC port blocks (MAC[i] @ e->base+(i+1)*0x40000) — PRIME egress-gate suspect
MAC2 (phys 0x92280000) = host port (LAN3 / PHY[2], link UP, RX works).
```
0x92200000 MAC0 ctrl  stock=00ba6003 main=00000000
0x92200004 MAC0 mask  stock=00003fff main=00000000
0x92200008 MAC0 en    stock=80000001 main=00000000
0x92240000 MAC1 ctrl  stock=00bae000 main=00000000
0x92240004 MAC1 mask  stock=00003fff main=00000000
0x92240008 MAC1 en    stock=80000001 main=00000000
0x92280000 MAC2 ctrl  stock=00bae000 main=00ba6003   <- host port; bit15 (0x8000) stock-only
0x92280004 MAC2 mask  stock=00003fff main=00000000   <- unset in mainline
0x92280008 MAC2 en    stock=80000001 main=00000000   <- EGRESS ENABLE = 0 in mainline (bit31)
0x922c0000 MAC3 ctrl  stock=00bae000 main=00000000
0x922c0004 MAC3 mask  stock=00003fff main=00000000
0x922c0008 MAC3 en    stock=80000001 main=00000000
```
Hypothesis: MAC[2] egress disabled (en=0, mask=0; ctrl missing bit15) → switch routes
the reply to MAC2 but it never reaches the wire. RX works via a separate gate.

## TM QMG block (e->base+0xc000) — egress scheduler / queues
```
0x921cc004 stock=00060000 main=00020000
0x921cc008 stock=00000add main=00eee311
0x921cc018 stock=0000000d main=00000200
0x921cc01c stock=00000003 main=00000200
0x921cc020 stock=00000003 main=00000200
0x921cc044 stock=00000000 main=00000011
0x921cc0e4 stock=00300000 main=00240000
0x921cc100 stock=00054d08 main=00000980
0x921cc104 stock=00aa00aa main=0e130e13
0x921cc108 stock=0000054d main=000e0001
0x921cc114 stock=0000054d main=00000001
0x921cc118 stock=02800080 main=00000000
0x921cc11c stock=1e010000 main=00000000
```

## TM DMA / per-queue block (e->base+0x10000)
```
0x921d0004 stock=0000000b main=0000000a
0x921d0040 stock=00000000 main=0000d3d3
0x921d0048 stock=00000000 main=00000403
0x921d004c stock=00000000 main=000000d3
0x921d0080 stock=00000000 main=00000003
0x921d0084 stock=00000000 main=00000003
0x921d00d4 stock=00009700 main=00003400
0x921d00e8 stock=00ed0000 main=00000000
0x921d00ec stock=b3b30000 main=00000000
0x921d00f8 stock=00aa0000 main=000e0000
0x921d00fc stock=00004d4d main=00000e0e
0x921d0114 stock=ededaaaa main=00000e0e
0x921d0118 stock=00009797 main=0000230e
```

## TM BMU block (e->base+0x8000) — mostly pointers, likely benign
```
0x921c8004 stock=4daec000 main=48044000   (desc base pointer — different carved layout)
0x921c8008 stock=4dae8000 main=48040000   (pointer)
0x921c8024 stock=0000001b main=0000001f
0x921c8088 stock=00290544 main=00290504
0x921c808c stock=00290544 main=00290504
0x921c8090 stock=00290544 main=00290504
```

## PP_BRG block (e->base+0x1c8000) — mostly expected (FDB shadow, our writes)
```
0x92388008 stock=0000dfdf main=0000ff00   (PP[0x8008])
0x92388014 stock=01000fff main=000001c8   (BRG RAM cmd — transient)
0x9238801c stock=0001ffff main=0064420f   (BRG RAM data — transient/FDB)
0x92388020 stock=00000000 main=000000f0
0x92388024 stock=00000000 main=47f6f401   (FDB data — our MAC)
0x923880b0 stock=00000102 main=00000108   (FDB-A host slot port bitmap — learned)
0x92388204 stock=00000001 main=00000000
0x9238820c stock=00000000 main=00000001
0x9238863c stock=00000000 main=aaaaaaaa   (we write 0xaaaaaaaa at 0x863c)
```
