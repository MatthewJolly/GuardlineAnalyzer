#include "GLPAnalyzer.h"
#include "GLPAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

GLPAnalyzer::GLPAnalyzer()
:	Analyzer2(),  
	mSettings( new GLPAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

GLPAnalyzer::~GLPAnalyzer()
{
	KillThread();
}

void GLPAnalyzer::SetupResults()
{
	mResults.reset( new GLPAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mLabelChannel );
}

void GLPAnalyzer::NewFrame(U64 data, U64 start, U64 end, AnalyzerChannelData* serial, AnalyzerResults* results)
{
	U32 spacer = 100;
	Frame frame;
	frame.mData1 = data;
	frame.mFlags = 0;
	frame.mStartingSampleInclusive = (start > spacer ? start - spacer : 0);
	frame.mEndingSampleInclusive = end + spacer;
	results->AddFrame(frame);
	results->CommitResults();
}
void GLPAnalyzer::WorkerThread()
{
	mSampleRateHz = GetSampleRate();

	mSerial = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mSerial->GetBitState() == BIT_LOW )
		mSerial->AdvanceToNextEdge();

	U32 flagStart = mSerial->GetSampleNumber();
	U32 deviceStart = flagStart;
	U32 samples_per_bit = mSampleRateHz / mSettings->mBitRate;

	U64 period = (mSampleRateHz / 1000 / 1000) * (mSettings->mPeriod); //get sample rate in microseconds and multiply by period in microseconds
	U64 gap = period * mSettings->mGapTime;

	U32 samples_to_first_center_of_first_data_bit = U32( 1.5 * double( mSampleRateHz ) / double( mSettings->mBitRate) );

	mSerial->Advance(period / 2);

	U8 b[3];
	U32 deviceID;
	U8 mask = 0;
	for( ; ; )
	{
		U8 data = 0;
		U64 starting_sample = mSerial->GetSampleNumber() - (period / 2);
		//each symbol is 3 bits
		for( U32 i=0; i<3; i++ )
		{
			U64 nextEdge = mSerial->GetSampleOfNextEdge();
			U64 dist = nextEdge - mSerial->GetSampleNumber();

			mResults->AddMarker(mSerial->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mInputChannel);

			b[i] = (mSerial->GetBitState() == BIT_HIGH ? 1 : 0);
			if (i == 1) //after second bit in symbol we should always be transitioning to low
			{
				mSerial->AdvanceToNextEdge();
				mSerial->Advance(10);
			}
			else if (i == 2)
			{
				U64 cur = mSerial->GetSampleNumber();
				U8 bit = 0;
				bool valid = false;
				if (b[0] == 0 && b[1] == 1 && b[2] == 0)
				{
					valid = true;
					bit = 1;
				}
				if (b[0] == 1 && b[1] == 1 && b[2] == 0)
				{
					valid = true;
					bit = 0;
				}
				U64 w = cur - flagStart;
				w = w / 2 + period / 2;

				if (bit)
					mResults->AddMarker(flagStart + w, AnalyzerResults::One, mSettings->mLabelChannel);
				else
					mResults->AddMarker(flagStart + w, AnalyzerResults::Zero, mSettings->mLabelChannel);


				if (bit)
					deviceID |= (1 << mask);
				mask++; 
				if (mask >= 32 || !valid) //should not be more than 32 bits in this ID...throw it out
				{
					mask = 0;
					flagStart = cur;
					deviceStart = cur;
					deviceID = 0;
					break;
				}
				if (dist > gap && mSerial->GetBitState() == BIT_LOW) //reached end of this ID
				{
					NewFrame(deviceID, deviceStart, cur, mSerial, mResults.get());
					ReportProgress(cur);

					deviceID = 0;
					mask = 0;

					mSerial->AdvanceToNextEdge(); 
					
					deviceStart = mSerial->GetSampleNumber();
					flagStart = deviceStart;
					mSerial->Advance(period / 2);
				}
				else {

					mSerial->Advance(period);
					flagStart = cur;
					b[0] = b[1] = b[2] = 0;
				}
			}
			else
				mSerial->Advance(period);
			
		}
	}
}

bool GLPAnalyzer::NeedsRerun()
{
	return false;
}

U32 GLPAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 GLPAnalyzer::GetMinimumSampleRateHz()
{
	return mSettings->mBitRate * 4;
}

const char* GLPAnalyzer::GetAnalyzerName() const
{
	return "Guardline Protocol";
}

const char* GetAnalyzerName()
{
	return "Guardline Protocol";
}

Analyzer* CreateAnalyzer()
{
	return new GLPAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}