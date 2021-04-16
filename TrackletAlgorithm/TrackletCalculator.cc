#include "TrackletCalculator.h"

// Returns a unique identifier assigned to each TC.
const TrackletProjection<BARRELPS>::TProjTCID
TC::ID(const TF::seed Seed, const TC::itc iTC)
{
  return ((TrackletProjection<BARRELPS>::TProjTCID(Seed) << TrackletProjection<BARRELPS>::kTProjITCSize) + iTC);
}
// Determine the correct stub-pair memory and stub-pair index given the global
// index initially stored in iSP.
void
TC::getIndices(
    const uint8_t NSPMem,
    const BXType bx,
    const StubPairMemory stubPairs[],
    TC::Types::nSPMem &iSPMem,
    TC::Types::nSP &iSP,
    bool &done
)
{
  bool set = false;

  iSPMem = 0;
  done = false;

  index: for (TC::Types::nSPMem j = 0; j < NSPMem; j++) {
    if (!set && iSP >= stubPairs[j].getEntries(bx))
      iSP -= stubPairs[j].getEntries(bx), iSPMem++;
    else
      set = true;
  }

  done = !set || iSPMem >= NSPMem;
}

void
TrackletCalculator(
    const TF::seed Seed,
    const TC::itc iTC,
    const uint8_t NSPMem,

    const BXType bx,
    const AllStubMemory<BARRELPS> innerStubs[],
    const AllStubMemory<BARRELPS> outerStubs[],
    const StubPairMemory stubPairs[],
    BXType& bx_o,
    TrackletParameterMemory * const trackletParameters,
    TrackletProjectionMemory<BARRELPS> projout_barrel_ps[],
    TrackletProjectionMemory<BARREL2S> projout_barrel_2s[],
    TrackletProjectionMemory<DISK> projout_disk[]
) {
  TrackletCalculator_<BARRELPS, BARRELPS>(
    Seed,
    iTC,
    NSPMem,

    bx,
    innerStubs,
    outerStubs,
    stubPairs,
    bx_o,
    trackletParameters,
    projout_barrel_ps,
    projout_barrel_2s,
    projout_disk
  );
}

void
TrackletCalculator(
    const TF::seed Seed,
    const TC::itc iTC,
    const uint8_t NSPMem,

    const BXType bx,
    const AllStubMemory<BARRELPS> innerStubs[],
    const AllStubMemory<BARREL2S> outerStubs[],
    const StubPairMemory stubPairs[],
    BXType& bx_o,
    TrackletParameterMemory * const trackletParameters,
    TrackletProjectionMemory<BARRELPS> projout_barrel_ps[],
    TrackletProjectionMemory<BARREL2S> projout_barrel_2s[],
    TrackletProjectionMemory<DISK> projout_disk[]
) {
  TrackletCalculator_<BARRELPS, BARREL2S>(
    Seed,
    iTC,
    NSPMem,

    bx,
    innerStubs,
    outerStubs,
    stubPairs,
    bx_o,
    trackletParameters,
    projout_barrel_ps,
    projout_barrel_2s,
    projout_disk
  );
}

void
TrackletCalculator(
    const TF::seed Seed,
    const TC::itc iTC,
    const uint8_t NSPMem,

    const BXType bx,
    const AllStubMemory<BARREL2S> innerStubs[],
    const AllStubMemory<BARREL2S> outerStubs[],
    const StubPairMemory stubPairs[],
    BXType& bx_o,
    TrackletParameterMemory * const trackletParameters,
    TrackletProjectionMemory<BARRELPS> projout_barrel_ps[],
    TrackletProjectionMemory<BARREL2S> projout_barrel_2s[],
    TrackletProjectionMemory<DISK> projout_disk[]
) {
  TrackletCalculator_<BARREL2S, BARREL2S>(
    Seed,
    iTC,
    NSPMem,

    bx,
    innerStubs,
    outerStubs,
    stubPairs,
    bx_o,
    trackletParameters,
    projout_barrel_ps,
    projout_barrel_2s,
    projout_disk
  );
}

// This file contains numbers of memories and bit masks that are specific to
// each TrackletCalculator and that come directly from the wiring.
//
// The specific inner all-stub memory that the indices in a given stub-pair
// memory correspond to is determined by ASInnerMask. The bits of this mask,
// from least significant to most significant, represent the stub-pair memories
// in the order they are passed to TrackletCalculator; e.g., the LSB
// corresponds to stubPairs[0]. The bit for a given stub-pair memory is the
// index (0 or 1) of the inner all-stub memory that should be used. Likewise,
// the specific outer all-stub memories are determined by ASOuterMask.
//
// The validity of each of the barrel TPROJ memories is determined by
// TPROJMaskBarrel. The bits of this mask, from least significant to most
// significant, represent the memories in the order they are passed to
// TrackletCalculator; e.g., the LSB corresponds to
// projout_barrel_ps[TC::L1PHIA]. If a bit is set, the corresponding memory is
// valid, if it is not, the corresponding memory is not valid. Likewise, the
// validity of each of the disk TPROJ memories is determined by TPROJMaskDisk
// in the same way.

uint8_t NASMemInner(const TF::seed Seed, const TC::itc iTC) {
  if (Seed == TF::L1L2 && iTC == TC::A)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::B)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::C)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::D)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::E)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::F)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::G)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::H)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::I)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::J)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::K)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::L)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::A)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::B)
    return 2;
  else if (Seed == TF::L3L4 && iTC == TC::C)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::D)
    return 2;
  else if (Seed == TF::L3L4 && iTC == TC::E)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::F)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::G)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::H)
    return 1;
  else if (Seed == TF::L5L6 && iTC == TC::A)
    return 2;
  else if (Seed == TF::L5L6 && iTC == TC::D)
    return 2;
  return 0;
}

uint8_t NASMemOuter(const TF::seed Seed, const TC::itc iTC) {
  if (Seed == TF::L1L2 && iTC == TC::A)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::B)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::C)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::D)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::E)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::F)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::G)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::H)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::I)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::J)
    return 2;
  else if (Seed == TF::L1L2 && iTC == TC::K)
    return 1;
  else if (Seed == TF::L1L2 && iTC == TC::L)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::A)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::B)
    return 2;
  else if (Seed == TF::L3L4 && iTC == TC::C)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::D)
    return 2;
  else if (Seed == TF::L3L4 && iTC == TC::E)
    return 1;
  else if (Seed == TF::L3L4 && iTC == TC::F)
    return 2;
  else if (Seed == TF::L3L4 && iTC == TC::G)
    return 2;
  else if (Seed == TF::L3L4 && iTC == TC::H)
    return 1;
  else if (Seed == TF::L5L6 && iTC == TC::A)
    return 2;
  else if (Seed == TF::L5L6 && iTC == TC::D)
    return 2;
  return 0;
}

uint8_t NSPMem(const TF::seed Seed, const TC::itc iTC) {
  if (Seed == TF::L1L2 && iTC == TC::A)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::B)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::C)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::D)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::E)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::F)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::G)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::H)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::I)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::J)
    return 13;
  else if (Seed == TF::L1L2 && iTC == TC::K)
    return 12;
  else if (Seed == TF::L1L2 && iTC == TC::L)
    return 12;
  else if (Seed == TF::L3L4 && iTC == TC::A)
    return 12;
  else if (Seed == TF::L3L4 && iTC == TC::B)
    return 12;
  else if (Seed == TF::L3L4 && iTC == TC::C)
    return 12;
  else if (Seed == TF::L3L4 && iTC == TC::D)
    return 12;
  else if (Seed == TF::L3L4 && iTC == TC::E)
    return 11;
  else if (Seed == TF::L3L4 && iTC == TC::F)
    return 11;
  else if (Seed == TF::L3L4 && iTC == TC::G)
    return 11;
  else if (Seed == TF::L3L4 && iTC == TC::H)
    return 11;
  else if (Seed == TF::L5L6 && iTC == TC::A)
    return 30;
  else if (Seed == TF::L5L6 && iTC == TC::D)
    return 30;
  return 0;
}

uint32_t ASInnerMask(const TF::seed Seed, const TC::itc iTC) {
  if (Seed == TF::L1L2 && iTC == TC::A)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::B)
    return 0x1FF0;
  else if (Seed == TF::L1L2 && iTC == TC::C)
    return 0x1800;
  else if (Seed == TF::L1L2 && iTC == TC::D)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::E)
    return 0x1FE0;
  else if (Seed == TF::L1L2 && iTC == TC::F)
    return 0x1000;
  else if (Seed == TF::L1L2 && iTC == TC::G)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::H)
    return 0x1FC0;
  else if (Seed == TF::L1L2 && iTC == TC::I)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::J)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::K)
    return 0xF80;
  else if (Seed == TF::L1L2 && iTC == TC::L)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::A)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::B)
    return 0xC00;
  else if (Seed == TF::L3L4 && iTC == TC::C)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::D)
    return 0xC00;
  else if (Seed == TF::L3L4 && iTC == TC::E)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::F)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::G)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::H)
    return 0x0;
  else if (Seed == TF::L5L6 && iTC == TC::A)
    return 0x30000000;
  else if (Seed == TF::L5L6 && iTC == TC::D)
    return 0x3FFFFFFC;
  return 0;
}

uint32_t ASOuterMask(const TF::seed Seed, const TC::itc iTC) {
  if (Seed == TF::L1L2 && iTC == TC::A)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::B)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::C)
    return 0x620;
  else if (Seed == TF::L1L2 && iTC == TC::D)
    return 0x8;
  else if (Seed == TF::L1L2 && iTC == TC::E)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::F)
    return 0xC40;
  else if (Seed == TF::L1L2 && iTC == TC::G)
    return 0x1FEE;
  else if (Seed == TF::L1L2 && iTC == TC::H)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::I)
    return 0x1880;
  else if (Seed == TF::L1L2 && iTC == TC::J)
    return 0x1FDC;
  else if (Seed == TF::L1L2 && iTC == TC::K)
    return 0x0;
  else if (Seed == TF::L1L2 && iTC == TC::L)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::A)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::B)
    return 0x300;
  else if (Seed == TF::L3L4 && iTC == TC::C)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::D)
    return 0x300;
  else if (Seed == TF::L3L4 && iTC == TC::E)
    return 0x0;
  else if (Seed == TF::L3L4 && iTC == TC::F)
    return 0x600;
  else if (Seed == TF::L3L4 && iTC == TC::G)
    return 0x7FC;
  else if (Seed == TF::L3L4 && iTC == TC::H)
    return 0x0;
  else if (Seed == TF::L5L6 && iTC == TC::A)
    return 0xE080000;
  else if (Seed == TF::L5L6 && iTC == TC::D)
    return 0x41C;
  return 0;
}

uint32_t TPROJMaskBarrel(const TF::seed Seed, const TC::itc iTC) {
  if (Seed == TF::L1L2 && iTC == TC::A)
    return 0x3333000;
  else if (Seed == TF::L1L2 && iTC == TC::B)
    return 0x7333000;
  else if (Seed == TF::L1L2 && iTC == TC::C)
    return 0x7733000;
  else if (Seed == TF::L1L2 && iTC == TC::D)
    return 0x7777000;
  else if (Seed == TF::L1L2 && iTC == TC::E)
    return 0xF777000;
  else if (Seed == TF::L1L2 && iTC == TC::F)
    return 0xFF66000;
  else if (Seed == TF::L1L2 && iTC == TC::G)
    return 0xFEE6000;
  else if (Seed == TF::L1L2 && iTC == TC::H)
    return 0xEEEE000;
  else if (Seed == TF::L1L2 && iTC == TC::I)
    return 0xEECC000;
  else if (Seed == TF::L1L2 && iTC == TC::J)
    return 0xECCC000;
  else if (Seed == TF::L1L2 && iTC == TC::K)
    return 0xCCCC000;
  else if (Seed == TF::L1L2 && iTC == TC::L)
    return 0xCCC8000;
  else if (Seed == TF::L3L4 && iTC == TC::A)
    return 0x330030E;
  else if (Seed == TF::L3L4 && iTC == TC::B)
    return 0x730031E;
  else if (Seed == TF::L3L4 && iTC == TC::C)
    return 0x770063C;
  else if (Seed == TF::L3L4 && iTC == TC::D)
    return 0xF600678;
  else if (Seed == TF::L3L4 && iTC == TC::E)
    return 0xEE00CF0;
  else if (Seed == TF::L3L4 && iTC == TC::F)
    return 0xEC00CE0;
  else if (Seed == TF::L3L4 && iTC == TC::G)
    return 0xCC008C0;
  else if (Seed == TF::L3L4 && iTC == TC::H)
    return 0xC8008C0;
  else if (Seed == TF::L5L6 && iTC == TC::A)
    return 0x3771E;
  else if (Seed == TF::L5L6 && iTC == TC::D)
    return 0xCCCE0;
  return 0;
}

uint32_t TPROJMaskDisk(const TF::seed Seed, const TC::itc iTC) {
  if (Seed == TF::L1L2 && iTC == TC::A)
    return 0x3333;
  else if (Seed == TF::L1L2 && iTC == TC::B)
    return 0x7777;
  else if (Seed == TF::L1L2 && iTC == TC::C)
    return 0x7777;
  else if (Seed == TF::L1L2 && iTC == TC::D)
    return 0x7777;
  else if (Seed == TF::L1L2 && iTC == TC::E)
    return 0xFFFF;
  else if (Seed == TF::L1L2 && iTC == TC::F)
    return 0xFFFF;
  else if (Seed == TF::L1L2 && iTC == TC::G)
    return 0xFFFF;
  else if (Seed == TF::L1L2 && iTC == TC::H)
    return 0xEEEE;
  else if (Seed == TF::L1L2 && iTC == TC::I)
    return 0xEEEE;
  else if (Seed == TF::L1L2 && iTC == TC::J)
    return 0xEEEE;
  else if (Seed == TF::L1L2 && iTC == TC::K)
    return 0xCCCC;
  else if (Seed == TF::L1L2 && iTC == TC::L)
    return 0xCCCC;
  else if (Seed == TF::L3L4 && iTC == TC::A)
    return 0x33;
  else if (Seed == TF::L3L4 && iTC == TC::B)
    return 0x77;
  else if (Seed == TF::L3L4 && iTC == TC::C)
    return 0x77;
  else if (Seed == TF::L3L4 && iTC == TC::D)
    return 0xFF;
  else if (Seed == TF::L3L4 && iTC == TC::E)
    return 0xEE;
  else if (Seed == TF::L3L4 && iTC == TC::F)
    return 0xEE;
  else if (Seed == TF::L3L4 && iTC == TC::G)
    return 0xCC;
  else if (Seed == TF::L3L4 && iTC == TC::H)
    return 0xCC;
  else if (Seed == TF::L5L6 && iTC == TC::A)
    return 0x0;
  else if (Seed == TF::L5L6 && iTC == TC::D)
    return 0x0;
  return 0;
}