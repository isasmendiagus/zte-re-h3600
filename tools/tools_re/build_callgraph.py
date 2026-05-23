#!/usr/bin/env python3
"""
Build a call-graph from cspd disassembly and trace UPWARD from a suspicious sink
(e.g. IPIFSetOverridedDNS) to find reachable entry points (webd handlers, IPC dispatchers, etc).

Usage: python3 build_callgraph.py <target_function_name> [max_depth]
"""
import re, sys
from collections import defaultdict, deque

DIS = "/tmp/cspd.dis"
RE_FUNC_HEAD = re.compile(r'^([0-9a-f]+) <([^>]+)>:\s*$')
RE_BL        = re.compile(r'\bbl\s+([0-9a-f]+)\s+<([^>]+)>')

def parse_callgraph():
    """Returns: {callee_name: set(caller_names)}"""
    callers = defaultdict(set)
    cur_fn = None
    with open(DIS) as f:
        for ln in f:
            m = RE_FUNC_HEAD.match(ln)
            if m: cur_fn = m.group(2); continue
            if cur_fn is None or "@plt" in cur_fn: continue
            m = RE_BL.search(ln)
            if m:
                callee = m.group(2)
                # Strip +0xN suffix (intra-function jumps)
                if "+0x" in callee: callee = callee.split("+0x")[0]
                callers[callee].add(cur_fn)
    return callers

def trace_up(callers, target, max_depth=6):
    """BFS upward from target. Returns dict of name -> shortest distance."""
    dist = {target: 0}
    queue = deque([(target, 0)])
    while queue:
        fn, d = queue.popleft()
        if d >= max_depth: continue
        for caller in callers.get(fn, ()):
            if caller in dist: continue
            dist[caller] = d + 1
            queue.append((caller, d + 1))
    return dist

def main():
    if len(sys.argv) < 2:
        print("Usage: build_callgraph.py <target_function> [max_depth=6]"); sys.exit(1)
    target = sys.argv[1]
    max_depth = int(sys.argv[2]) if len(sys.argv) > 2 else 6

    print(f"Parsing {DIS}...", file=sys.stderr)
    callers = parse_callgraph()
    print(f"  {sum(len(v) for v in callers.values())} caller→callee edges", file=sys.stderr)
    print(f"  {len(callers)} unique callees", file=sys.stderr)

    if target not in callers:
        print(f"\n⚠ '{target}' has no recorded callers. Check function name.")
        # show fuzzy matches
        like = [c for c in callers if target.lower() in c.lower()][:10]
        print(f"  similar names found: {like}")
        sys.exit(1)

    dist = trace_up(callers, target, max_depth)
    print(f"\n=== Reverse call-graph from '{target}' (depth ≤ {max_depth}) ===")
    print(f"Total callers reachable: {len(dist) - 1}\n")

    # Group by depth
    by_depth = defaultdict(list)
    for fn, d in dist.items():
        if d > 0: by_depth[d].append(fn)

    for d in sorted(by_depth):
        print(f"\nDEPTH {d}:")
        for fn in sorted(by_depth[d])[:50]:
            interest = ""
            for kw in ("webd","Webd","Cmapi","cmapi","Set","Recv","Handle","DB"):
                if kw in fn: interest += " ["+kw+"]"
            print(f"  {fn}{interest}")
        if len(by_depth[d]) > 50:
            print(f"  ... +{len(by_depth[d])-50} more")

    # Highlight roots (functions with no callers — likely top-level entry points)
    print(f"\n=== ROOTS (no recorded callers — possible entry points) ===")
    roots = [fn for fn in dist if fn not in callers or not callers[fn]]
    for r in sorted(roots)[:20]:
        print(f"  {r}  (depth {dist[r]})")

if __name__ == "__main__":
    main()
