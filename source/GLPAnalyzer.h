#ifndef GLP_ANALYZER_H
#define GLP_ANALYZER_H

#include <Analyzer.h>
#include "GLPAnalyzerResults.h"
#include "GLPSimulationDataGenerator.h"

class GLPAnalyzerSettings;
class ANALYZER_EXPORT GLPAnalyzer : public Analyzer2
{
public:
	GLPAnalyzer();
	virtual ~GLPAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

	virtual void NewFrame(U64 data, U64 start, U64 end, AnalyzerChannelData* serial, AnalyzerResults* results);

protected: //vars
	std::auto_ptr< GLPAnalyzerSettings > mSettings;
	std::auto_ptr< GLPAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	GLPSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //GLP_ANALYZER_H
