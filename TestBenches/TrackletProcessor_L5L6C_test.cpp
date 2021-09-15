// Test bench for TrackletProcessor
#include "TrackletProcessor.h"

#include <algorithm>
#include <iterator>
#include <cstring>

#include "FileReadUtility.h"
#include "Constants.h"

const int nevents = 100;  //number of events to ru

using namespace std;

int main()
{
  // error counts
  int err = 0;

  ap_uint<10> innervmtable[2048] =
#include "../emData/TP/tables/TP_L5L6.tab"

  ap_uint<8> useregion[4096] =
#include "../emData/TP/tables/TP_L5L6C_usereg.tab"

  ///////////////////////////
  // input memories
  static AllStubInnerMemory<BARREL2S> innerStubs[3];
  static AllStubMemory<BARREL2S> outerStubs;
  static VMStubTEOuterMemoryCM<BARREL2S, kNbitsrzbin, kNbitsphibin, 3> outervmStubs;


  // output memories
  static TrackletParameterMemory tpar;
  static TrackletProjectionMemory<BARRELPS> tproj_barrel_ps[TC::N_PROJOUT_BARRELPS];
  static TrackletProjectionMemory<BARREL2S> tproj_barrel_2s[TC::N_PROJOUT_BARREL2S];
  static TrackletProjectionMemory<DISK> tproj_disk[TC::N_PROJOUT_DISK];

  ///////////////////////////
  // open input files
  cout << "Open files..." << endl;

  const string dir = "TP_L5L6C";

  ifstream fin_innerStubs0;
  if (not openDataFile(fin_innerStubs0, dir + "/AllInnerStubs_AS_L5PHID_BL_04.dat")) return -1;

  ifstream fin_innerStubs1;
  if (not openDataFile(fin_innerStubs1, dir + "/AllInnerStubs_AS_L5PHIB_BR_04.dat")) return -1;

  ifstream fin_innerStubs2;
  if (not openDataFile(fin_innerStubs2, dir + "/AllInnerStubs_AS_L5PHIC_BM_04.dat")) return -1;

  ifstream fin_outerStubs;
  if (not openDataFile(fin_outerStubs, dir + "/AllStubs_AS_L6PHIC_B_L5C_04.dat")) return -1;

  ifstream fin_outervmstubs;
  if (not openDataFile(fin_outervmstubs, dir + "/VMStubs_VMSTE_L6PHICn1_04.dat")) return -1;

  ///////////////////////////
  // open output files
  ifstream fout_tpar;
  if (not openDataFile(fout_tpar, dir + "/TrackletParameters_TPAR_L5L6C_04.dat")) return -1;

  ifstream fout_tproj0;
  if (not openDataFile(fout_tproj0, dir + "/TrackletProjections_TPROJ_L5L6C_L1PHIC_04.dat")) return -1;

  ifstream fout_tproj1;
  if (not openDataFile(fout_tproj1, dir + "/TrackletProjections_TPROJ_L5L6C_L1PHID_04.dat")) return -1;

  ifstream fout_tproj2;
  if (not openDataFile(fout_tproj2, dir + "/TrackletProjections_TPROJ_L5L6C_L1PHIE_04.dat")) return -1;

  ifstream fout_tproj3;
  if (not openDataFile(fout_tproj3, dir + "/TrackletProjections_TPROJ_L5L6C_L1PHIF_04.dat")) return -1;

  ifstream fout_tproj4;
  if (not openDataFile(fout_tproj4, dir + "/TrackletProjections_TPROJ_L5L6C_L1PHIG_04.dat")) return -1;

  ifstream fout_tproj5;
  if (not openDataFile(fout_tproj5, dir + "/TrackletProjections_TPROJ_L5L6C_L2PHIB_04.dat")) return -1;


  ifstream fout_tproj6;
  if (not openDataFile(fout_tproj6, dir + "/TrackletProjections_TPROJ_L5L6C_L2PHIC_04.dat")) return -1;

  ifstream fout_tproj7;
  if (not openDataFile(fout_tproj7, dir + "/TrackletProjections_TPROJ_L5L6C_L2PHID_04.dat")) return -1;

  ifstream fout_tproj8;
  if (not openDataFile(fout_tproj8, dir + "/TrackletProjections_TPROJ_L5L6C_L3PHIB_04.dat")) return -1;

  ifstream fout_tproj9;
  if (not openDataFile(fout_tproj9, dir + "/TrackletProjections_TPROJ_L5L6C_L3PHIC_04.dat")) return -1;

  ifstream fout_tproj10;
  if (not openDataFile(fout_tproj10, dir + "/TrackletProjections_TPROJ_L5L6C_L3PHID_04.dat")) return -1;

  ifstream fout_tproj11;
  if (not openDataFile(fout_tproj11, dir + "/TrackletProjections_TPROJ_L5L6C_L4PHIB_04.dat")) return -1;

  ifstream fout_tproj12;
  if (not openDataFile(fout_tproj12, dir + "/TrackletProjections_TPROJ_L5L6C_L4PHIC_04.dat")) return -1;

  ifstream fout_tproj13;
  if (not openDataFile(fout_tproj13, dir + "/TrackletProjections_TPROJ_L5L6C_L4PHID_04.dat")) return -1;


  ///////////////////////////
  // loop over events
  cout << "Start event loop ..." << endl;
  for (unsigned int ievt = 0; ievt < nevents; ++ievt) {
    cout << "Event: " << dec << ievt << endl;

    tpar.clear();
    for (unsigned i = 0; i < TC::N_PROJOUT_BARRELPS; i++)
      tproj_barrel_ps[i].clear();
    for (unsigned i = 0; i < TC::N_PROJOUT_BARREL2S; i++)
      tproj_barrel_2s[i].clear();
    for (unsigned i = 0; i < TC::N_PROJOUT_DISK; i++)
      tproj_disk[i].clear();    

    // read event and write to memories
    writeMemFromFile<AllStubInnerMemory<BARREL2S> >(innerStubs[0], fin_innerStubs0, ievt);
    writeMemFromFile<AllStubInnerMemory<BARREL2S> >(innerStubs[1], fin_innerStubs1, ievt);
    writeMemFromFile<AllStubInnerMemory<BARREL2S> >(innerStubs[2], fin_innerStubs2, ievt);

    writeMemFromFile<AllStubMemory<BARREL2S> >(outerStubs, fin_outerStubs, ievt);
    cout << "Will read vmstubs"<<endl;
    writeMemFromFile<VMStubTEOuterMemoryCM<BARREL2S, kNbitsrzbin, kNbitsphibin, 3> >(outervmStubs, fin_outervmstubs, ievt);

    // bx
    BXType bx = ievt;

    // Unit Under Test
    TrackletProcessor_L5L6C(bx, 
			    innervmtable, 
			    useregion, 
			    innerStubs, 
			    &outerStubs, 
			    outervmStubs,
			    &tpar,
			    tproj_barrel_ps,
			    tproj_barrel_2s,
			    tproj_disk
			    );

    bool truncate = false;

    cout << "Start compare" << endl;

    // compare the computed outputs with the expected ones
    err += compareMemWithFile<TrackletParameterMemory>(tpar, fout_tpar, ievt,
                                                   "\nTrackletParameter", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L1PHIC], fout_tproj0, ievt,
                                                   "\nTrackletProjection (L1PHIC)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L1PHID], fout_tproj1, ievt,
                                                   "\nTrackletProjection (L1PHID)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L1PHIE], fout_tproj2, ievt,
                                                   "\nTrackletProjection (L1PHIE)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L1PHIF], fout_tproj3, ievt,
                                                   "\nTrackletProjection (L1PHI)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L1PHIG], fout_tproj4, ievt,
                                                   "\nTrackletProjection (L1PHIG)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L2PHIB], fout_tproj5, ievt,
                                                   "\nTrackletProjection (L2PHIB)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L2PHIC], fout_tproj6, ievt,
                                                   "\nTrackletProjection (L2PHIC)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L2PHID], fout_tproj7, ievt,
                                                   "\nTrackletProjection (L2PHID)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L3PHIB], fout_tproj8, ievt,
                                                   "\nTrackletProjection (L3PHIB)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L3PHIC], fout_tproj9, ievt,
                                                   "\nTrackletProjection (L3PHIC)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARRELPS> >(tproj_barrel_ps[TC::L3PHID], fout_tproj10, ievt,
                                                   "\nTrackletProjection (L3PHID)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARREL2S> >(tproj_barrel_2s[TC::L4PHIB], fout_tproj11, ievt,
                                                   "\nTrackletProjection (L4PHIC)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARREL2S> >(tproj_barrel_2s[TC::L4PHIC], fout_tproj12, ievt,
                                                   "\nTrackletProjection (L4PHID)", truncate);
    err += compareMemWithFile<TrackletProjectionMemory<BARREL2S> >(tproj_barrel_2s[TC::L4PHID], fout_tproj13, ievt,
                                                   "\nTrackletProjection (L4PHIB)", truncate);
    cout << endl;

  } // end of event loop

  cout << "Number of errors : "<<err<<endl;
  //return err;
  return 0;

}