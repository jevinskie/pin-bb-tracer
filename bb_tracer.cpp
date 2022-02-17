#include "pin.H"

UINT32 count_trace = 0; // current trace number

INT32 Usage() {
  cerr << "bb_tracer\n";

  cerr << KNOB_BASE::StringKnobSummary();

  cerr << endl;

  return -1;
}

VOID docount(const string *s) { (void); }

VOID Trace(TRACE trace, VOID *v) {
  for (BBL bbl = TRACE_BblHead(trace); BBL_Valid(bbl); bbl = BBL_Next(bbl)) {
    for (INS ins = BBL_InsHead(bbl); INS_Valid(ins); ins = INS_Next(ins)) {
      (void);
    }

    // Identify traces with an id
    count_trace++;

    // at run time, just print the id
    string *s = new string;
    INS_InsertCall(BBL_InsTail(bbl), IPOINT_BEFORE, AFUNPTR(docount), IARG_PTR,
                   s, IARG_END);
  }
}

VOID Fini(INT32 code, VOID *v) {}

int main(int argc, char *argv[]) {
  if (PIN_Init(argc, argv)) {
    return Usage();
  }

  // TRACE_AddInstrumentFunction(Trace, 0);
  IMG_AddInstrumentFunction(Image, 0);
  PIN_AddFiniFunction(Fini, 0);

  PIN_StartProgram();

  return 0;
}
