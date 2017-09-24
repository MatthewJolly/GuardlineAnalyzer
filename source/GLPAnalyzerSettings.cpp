#include "GLPAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


GLPAnalyzerSettings::GLPAnalyzerSettings()
:	mInputChannel( UNDEFINED_CHANNEL ), mLabelChannel( UNDEFINED_CHANNEL ),
	mBitRate( 20000 ), mPeriod(333), mGapTime(3)
{
	mInputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mInputChannelInterface->SetTitleAndTooltip( "Serial", "Standard Guardline Protocol" );
	mInputChannelInterface->SetChannel( mInputChannel );
	mLabelChannelInterface.reset(new AnalyzerSettingInterfaceChannel());
	mLabelChannelInterface->SetTitleAndTooltip("Label", "Layer to use for labels and annotations");
	mLabelChannelInterface->SetChannel(mLabelChannel);

	mBitRateInterface.reset( new AnalyzerSettingInterfaceInteger() );
	mBitRateInterface->SetTitleAndTooltip( "Bit Rate (Bits/S)",  "Specify the bit rate in bits per second." );
	mBitRateInterface->SetMax( 6000000 );
	mBitRateInterface->SetMin( 1 );
	mBitRateInterface->SetInteger( mBitRate );

	mPeriodInterface.reset(new AnalyzerSettingInterfaceInteger());
	mPeriodInterface->SetTitleAndTooltip("Period (us)", "Specify the period of each bit in microseconds.");
	mPeriodInterface->SetMax(10000);
	mPeriodInterface->SetMin(1);
	mPeriodInterface->SetInteger(mPeriod);

	mGapInterface.reset(new AnalyzerSettingInterfaceInteger());
	mGapInterface->SetTitleAndTooltip("Gap Time (in periods)", "Specify the number of periods to consider a gap");
	mGapInterface->SetMax(25);
	mGapInterface->SetMin(1);
	mGapInterface->SetInteger(mGapTime);

	AddInterface( mInputChannelInterface.get() );
	AddInterface( mLabelChannelInterface.get());
	AddInterface( mBitRateInterface.get() );
	AddInterface(mPeriodInterface.get());
	AddInterface(mGapInterface.get());


	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( mInputChannel, "Serial", false );
}

GLPAnalyzerSettings::~GLPAnalyzerSettings()
{
}

bool GLPAnalyzerSettings::SetSettingsFromInterfaces()
{
	mInputChannel = mInputChannelInterface->GetChannel();
	mLabelChannel = mLabelChannelInterface->GetChannel();
	mBitRate = mBitRateInterface->GetInteger();
	mPeriod = mPeriodInterface->GetInteger();
	mGapTime = mGapInterface->GetInteger();

	ClearChannels();
	AddChannel( mInputChannel, "Guardline Protocol", true );

	return true;
}

void GLPAnalyzerSettings::UpdateInterfacesFromSettings()
{
	mInputChannelInterface->SetChannel( mInputChannel );
	mLabelChannelInterface->SetChannel( mLabelChannel );
	mBitRateInterface->SetInteger( mBitRate );
	mPeriodInterface->SetInteger(mPeriod);
	mGapInterface->SetInteger(mGapTime);
}

void GLPAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mInputChannel;
	text_archive >> mLabelChannel;
	text_archive >> mBitRate;
	text_archive >> mPeriod;
	text_archive >> mGapTime;

	ClearChannels();
	AddChannel( mInputChannel, "Guardline Protocol", true );

	UpdateInterfacesFromSettings();
}

const char* GLPAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mInputChannel;
	text_archive << mLabelChannel;
	text_archive << mBitRate;
	text_archive << mPeriod;
	text_archive << mGapTime;

	return SetReturnString( text_archive.GetString() );
}
