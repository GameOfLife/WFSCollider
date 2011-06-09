
// SuperCollider 3 BSampleUGens
// blackrain dot sc at gmail dot com - 11 2008

#include "SC_PlugIn.h"

static InterfaceTable *ft;

extern "C"
{
    void load(InterfaceTable *inTable);
}

//--------------------------------------------------------------------------------------------------
//	OneImpulse.ar(freq, phase)

struct OneImpulse : public Unit 
{
	double mPhase, mPhaseOffset;
};

extern "C"
{
	void OneImpulse_Ctor(OneImpulse *unit);
	void OneImpulse_next(OneImpulse *unit, int inNumSamples);
};

void OneImpulse_Ctor(OneImpulse *unit)
{
	
	SETCALC(OneImpulse_next);

	unit->mPhaseOffset = 0.f;
	unit->mPhase = 1.f;
	
	ZOUT0(0) = 0.f;
}

void OneImpulse_next(OneImpulse *unit, int inNumSamples)
{
	float *out = ZOUT(0);
	
	float freqmul = unit->mRate->mSampleDur;
	double phase = unit->mPhase;
	LOOP(inNumSamples, 
		float z;
		if (phase >= 1.f) {
			phase -= 1.f;
			z = 1.f;
		} else {
			z = 0.f;
		}
		phase += freqmul;
		ZXP(out) = z;
	);
	
	NodeEnd( &unit->mParent->mNode ); // die after one cycle

	unit->mPhase = phase;
}

//--------------------------------------------------------------------------------------------------
//	ImpulseDriver.ar(samples)

struct ImpulseDriver : public Unit 
{
	int mSampleCounter;
	int mTargetCount;
};

extern "C"
{
	void ImpulseDriver_Ctor(ImpulseDriver *unit);
	void ImpulseDriver_next(ImpulseDriver *unit, int inNumSamples);
};

void ImpulseDriver_Ctor(ImpulseDriver *unit)
{
	
	SETCALC(ImpulseDriver_next);

	unit->mSampleCounter = 0;
	unit->mTargetCount = (uint32)IN0(0);
	ZOUT0(0) = 0.f;
}

void ImpulseDriver_next(ImpulseDriver *unit, int inNumSamples)
{
	float *out = OUT(0);		

	int SampleCounter = unit->mSampleCounter;
	int TargetCount = unit->mTargetCount;
	LOOP(inNumSamples, 
		float z;
		if (SampleCounter >= TargetCount) {
			SampleCounter = 0;
			z = 1.f;
		} else {
			z = 0.f;
		}
		SampleCounter += 1;
		ZXP(out) = z;
	);
	unit->mSampleCounter = SampleCounter;
}

//--------------------------------------------------------------------------------------------------
//	BlockCount

struct BlockCount : public Unit { };

extern "C"
{
	void BlockCount_Ctor(BlockCount *unit);
	void BlockCount_next_k(BlockCount *unit, int inNumSamples);
};

void BlockCount_Ctor(BlockCount *unit)
{
	SETCALC(BlockCount_next_k);
	BlockCount_next_k(unit, 1);
}

void BlockCount_next_k(BlockCount *unit, int inNumSamples)
{
	ZOUT0(0) = unit->mWorld->mBufCounter;
}

//--------------------------------------------------------------------------------------------------
//	BlockOffset

struct BlockOffset : public Unit { };

extern "C"
{
	void BlockOffset_Ctor(BlockOffset *unit);
	void BlockOffset_next_a(BlockOffset *unit, int inNumSamples);
};

void BlockOffset_Ctor(BlockOffset *unit)
{
	SETCALC(BlockOffset_next_a);
	BlockOffset_next_a(unit, 1);
}

void BlockOffset_next_a(BlockOffset *unit, int inNumSamples)
{
	float *out = OUT(0);
	for (int i=0; i < inNumSamples; ++i)
		out[i] = i;
}

//--------------------------------------------------------------------------------------------------
// SpawnBlock - ir
extern "C"
{
	void SpawnBlock_Ctor(Unit *unit, int inNumSamples);
}

void SpawnBlock_Ctor(Unit *unit, int inNumSamples)
{
	ZOUT0(0) = unit->mWorld->mBufCounter;
}

//--------------------------------------------------------------------------------------------------
// SpawnOffset - ir
extern "C"
{
	void SpawnOffset_Ctor(Unit *unit, int inNumSamples);
}

void SpawnOffset_Ctor(Unit *unit, int inNumSamples)
{
	ZOUT0(0) = unit->mParent->mSampleOffset;
}

//--------------------------------------------------------------------------------------------------

void load(InterfaceTable *inTable)
{
	ft = inTable;

	DefineSimpleUnit(OneImpulse);
	DefineSimpleUnit(ImpulseDriver);

	DefineSimpleUnit(BlockCount);
	DefineSimpleUnit(BlockOffset);

#define DefineInfoUnit(name) \
	(*ft->fDefineUnit)(#name, sizeof(Unit), (UnitCtorFunc)&name##_Ctor, 0, 0);
	DefineInfoUnit(SpawnBlock);
	DefineInfoUnit(SpawnOffset);
}

// EOF
