# eth-cleanup — driver code cleanup for upstream submission

**ID**: 00.01.02
**Parent**: [00.01 eth-driver](../00.01.eth-driver/)
**Children**: none
**Status**: 🔧 PLANNED — research pending (agent still running)

## Scope

Prepare the ZTE ZX279128S ethernet driver for upstream Linux submission:

### S1 — Must do before upstream
- DT bindings documentation (`Documentation/devicetree/bindings/net/zte,zx279128s-eth.yaml`)
- Coding style: 80-column lines, kernel-doc comments, checkpatch clean
- Dead code removal
- Fix any `// TODO` / `FIXME` items

### S2 — Should do
- Dedup FT/DSA shared code paths
- Split monolith (~9200 lines) into logical modules:
  - TM init (BMU, RED, DMA)
  - PP/CLA init
  - IDM/WiFi dispatch
  - Flow offload (FT)
  - DebugFS
- Remove redundant stock-replay-only sections, convert to named init

### S3 — Nice to have
- Compress/optimize stock replay tables
- Performance improvements

## Driver stats (pre-cleanup)
- `zx-eth-main.c`: ~9200 lines
- Stock replay tables: embedded via `zx_stock_table.h`, `zx_cla_table.h`, `zx_pm_table.h`
- Debug hooks to strip: BPDUMP (~20 lines), phaseC hex dump, NOPARSE dev_info, TM RX deliver

## Plan

See `research/cleanup_plan.md` (pending agent completion). Based on agent research 2026-08-01.
