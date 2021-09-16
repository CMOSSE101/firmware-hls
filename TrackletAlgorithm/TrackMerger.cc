#include "TrackMerger.h"
#include <bitset>

void TrackMergerHelper(const BXType bx,
  const TrackFit::TrackWord trackWord [kMaxProc],
  const TrackFit::BarrelStubWord barrelStubWords[4][kMaxProc],
  const TrackFit::DiskStubWord diskStubWords[4][kMaxProc],
  BXType &bx_o,
  TrackFit::TrackWord trackWord_o [kMaxProc],
  TrackFit::BarrelStubWord barrelStubWords_o[4][kMaxProc],
  TrackFit::DiskStubWord diskStubWords_o[4][kMaxProc]){ 

    #pragma HLS array_partition variable=barrelStubWords complete dim=1
    #pragma HLS array_partition variable=diskStubWords complete dim=1
    #pragma HLS stream variable=trackWord depth=1 dim=1
    #pragma HLS stream variable=barrelStubWords depth=1 dim=2
    #pragma HLS stream variable=diskStubWords depth=1 dim=2

    // reading in tracks
    
    for (unsigned int i = 0; i < kMaxProc; i++){
        TrackFit trkFit;
        trkFit.setTrackWord(trackWord[i]);
        ap_uint<TrackFitBase::kTFHitMapSize> trackStubMap = trkFit.getHitMap();
        std::cout << "Track Stub Map: " << std::bitset<TrackFitBase::kTFHitMapSize>(trackStubMap) << std::endl;
        
        TrackFit::BarrelStubWord barrelStubWord;   
        for (unsigned int j = 0; j < TrackFit::kNBarrelStubs; j++){ 
            switch (j){
              case 0:
                trkFit.setBarrelStubWord<0>(barrelStubWords[0][i]);
                barrelStubWord = trkFit.getBarrelStubWord<0>();
                break;
              case 1:
                trkFit.setBarrelStubWord<1>(barrelStubWords[1][i]);
                barrelStubWord = trkFit.getBarrelStubWord<1>();
                break;
              case 2:
                trkFit.setBarrelStubWord<2>(barrelStubWords[2][i]);
                barrelStubWord = trkFit.getBarrelStubWord<2>();
                break;
              case 3:
                trkFit.setBarrelStubWord<3>(barrelStubWords[3][i]);
                barrelStubWord = trkFit.getBarrelStubWord<3>();
                break;

            }
            std::cout << "barrelStub: " << std::bitset <TrackFitBase::kBarrelStubSize> (barrelStubWord) << std::endl;
        }  
        TrackFit::DiskStubWord diskStubWord;    
        for (unsigned int k = TrackFit::kNDiskStubs; k < TrackFit::kNStubs; k++){
            switch (k){
              case 4:
                trkFit.setDiskStubWord<4>(diskStubWords[0][i]);
                diskStubWord = trkFit.getDiskStubWord<4>();
                break;
              case 5:
                trkFit.setDiskStubWord<5>(diskStubWords[1][i]);
                diskStubWord = trkFit.getDiskStubWord<5>();
                break;
              case 6:
                trkFit.setDiskStubWord<6>(diskStubWords[2][i]);
                diskStubWord = trkFit.getDiskStubWord<6>();
                break;
              case 7:
                trkFit.setDiskStubWord<7>(diskStubWords[3][i]);
                diskStubWord = trkFit.getDiskStubWord<7>();
                break;
            }
            std::cout << "diskStubWord: " << std::bitset<TrackFitBase::kDiskStubSize> (diskStubWord) << std::endl;
        }

        // getting stub index
        ap_uint<TrackFitBase::kTFStubIndexSize> stubIndex;
        for (unsigned int l = 0; l < TrackFit::kNStubs; l++){
          switch (l) {
            case 0:
              stubIndex = trkFit.getStubIndex<0>();
              break;
            case 1:
              stubIndex = trkFit.getStubIndex<1>();
              break;
            case 2:
              stubIndex = trkFit.getStubIndex<2>();
              break;
            case 3: 
              stubIndex = trkFit.getStubIndex<3>();
              break;
            case 4:
              stubIndex = trkFit.getStubIndex<4>();
              break;
            case 5:
              stubIndex = trkFit.getStubIndex<5>();
              break;
            case 6:
              stubIndex = trkFit.getStubIndex<6>();
              break;
            case 7:
              stubIndex = trkFit.getStubIndex<7>();
              break;
          }
          std::cout << "StubIndex: " << stubIndex << std::endl;
        }
    }
  
  
    bx_o = bx;
  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isMatch = false; 
int trackIndex = 0;
int numberCandidates = 0;

bool ComparisonModule::CompareTracks(masterTrack, trk, &isMatch){
  #pragma HLS inline

  //compare the two tracks, masterTrack and trk
  // if they have > 3 stubs in common, update isMatch, else isMatch = false
  //now compare two tracks - the master track and the second input track

  if (isMatch){
    duplicateCandidate.setTrackWord(trackWord[i]);
    numberCandidates++;
    trackIndex = i;
    return true;
  } else {
      return false;
    }
}

void ComparisonModule::MergeTrack(TrackFit &masterTrack, const TrackFit trk){
  #pragma HLS inline
  //Will merge both tracks to produce the merged track word - update masterTrack
  //and its barrel/disk stubs
  // UPDATE just change the master track - the output stub words will then become a 2D array, up to 7 hits per layer

  if (ComparisonModule::CompareTracks(masterTrack, trk, isMatch) == true) //merge
}

void ComparisonModule::InputTrack(TrackFit trk){
  //put track into buffer

  TrackFit nextTrack = //next track from buffer
  //if (masterTrack is null){
    //set masterTrack = nextTrack
  //}
    //else {
      //if CompareTracks(masterTrack, nextTrack){
        //nextComparisonModule.InputTrack(nextTrack)
      //}
    //}
  //}
}

//overall module should only read in a track and pass it to the comparison module
void TrackMergerModule(const BXType bx,
  const TrackFit::TrackWord trackWord [kMaxProc],
  const TrackFit::BarrelStubWord barrelStubWords[4][kMaxProc],
  const TrackFit::DiskStubWord diskStubWords[4][kMaxProc],
  BXType &bx_o,
  TrackFit::TrackWord trackWord_o,
  TrackFit::BarrelStubWord barrelStubWords_o[4],
  TrackFit::DiskStubWord diskStubWords_o[4]){


    for (int i = 0; i < kMaxProc; i++){
      TrackFit trk = TrackFit //(all the information from the track and stub words);
      ComparisonModule[0].InputTrack(trk);
    }
    

    


  }