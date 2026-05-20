// Ghidra postScript (Java) — para vmlinux.bin del ZX279128S
// Para cada string "compatible" (zte,*, snps,*, denali,*) localiza la xref,
// sube al inicio de la función contenedora, decompila y vuelca a un .c
//
// Uso:
//   analyzeHeadless ... -postScript ExtractCompatibles.java <output_dir>
//
// @category ZXIC
// @runtime Java

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressIterator;
import ghidra.program.model.data.StringDataType;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.SymbolTable;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class ExtractCompatibles extends GhidraScript {

    private static final String[] PREFIXES = {
        "zte,", "snps,", "denali,", "zxic,", "arm,zx", "rohm,"
    };

    private static final int CONTEXT_FUNCS_PER_STRING = 3;

    @Override
    public void run() throws Exception {

        String[] args = getScriptArgs();
        File outDir;
        if (args.length >= 1) {
            outDir = new File(args[0]);
        } else {
            outDir = new File("/home/ubuntu/Projects/MYSELF/ZTE/ghidra/output");
        }
        outDir.mkdirs();
        println("ExtractCompatibles: output -> " + outDir.getAbsolutePath());

        DecompInterface decomp = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        decomp.setOptions(opts);
        decomp.openProgram(currentProgram);

        Listing listing = currentProgram.getListing();
        DataIterator dataIter = listing.getDefinedData(true);

        File indexFile = new File(outDir, "INDEX.md");
        PrintWriter index = new PrintWriter(new FileWriter(indexFile));
        index.println("# Compatible-string xref index");
        index.println();
        index.println("| Compatible | String addr | Xref count | Functions extracted |");
        index.println("|---|---|---|---|");

        Set<Function> dumped = new HashSet<>();
        int hits = 0;

        while (dataIter.hasNext() && !monitor.isCancelled()) {
            Data d = dataIter.next();
            if (d == null) continue;
            if (!(d.getDataType() instanceof StringDataType)) continue;

            Object val = d.getValue();
            if (!(val instanceof String)) continue;
            String s = (String) val;

            boolean match = false;
            for (String p : PREFIXES) {
                if (s.startsWith(p)) { match = true; break; }
            }
            if (!match) continue;

            hits++;
            Address strAddr = d.getAddress();

            ReferenceIterator refs = listing.getReferenceIterator(strAddr);
            List<Reference> refList = new ArrayList<>();
            while (refs.hasNext()) refList.add(refs.next());

            // also search references TO this address
            Reference[] inRefs = currentProgram.getReferenceManager()
                .getReferencesTo(strAddr);
            for (Reference r : inRefs) refList.add(r);

            List<String> extractedNames = new ArrayList<>();

            int funcCount = 0;
            for (Reference r : refList) {
                if (funcCount >= CONTEXT_FUNCS_PER_STRING) break;
                Address from = r.getFromAddress();
                Function f = currentProgram.getFunctionManager()
                    .getFunctionContaining(from);
                if (f == null) continue;
                if (dumped.contains(f)) continue;
                dumped.add(f);
                funcCount++;

                String safeStr = s.replaceAll("[^a-zA-Z0-9]", "_");
                String fname = String.format("%s__%s.c",
                    safeStr, f.getName());
                File out = new File(outDir, fname);

                DecompileResults dr = decomp.decompileFunction(f, 60, monitor);
                if (dr == null || !dr.decompileCompleted()) {
                    println("  decompile failed: " + f.getName());
                    continue;
                }
                String c = dr.getDecompiledFunction().getC();

                PrintWriter pw = new PrintWriter(new FileWriter(out));
                pw.println("// compatible: " + s);
                pw.println("// string @ " + strAddr);
                pw.println("// xref from: " + from);
                pw.println("// function:  " + f.getName() + " @ " + f.getEntryPoint());
                pw.println("//");
                pw.println(c);
                pw.close();

                extractedNames.add(f.getName());
            }

            if (!extractedNames.isEmpty()) {
                index.printf("| `%s` | %s | %d | %s |%n",
                    s, strAddr, refList.size(),
                    String.join(", ", extractedNames));
            } else {
                index.printf("| `%s` | %s | %d | (no function context) |%n",
                    s, strAddr, refList.size());
            }
        }

        index.close();
        decomp.closeProgram();
        println("ExtractCompatibles: " + hits + " strings, "
            + dumped.size() + " functions written to " + outDir);
    }
}
