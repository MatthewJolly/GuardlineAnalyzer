#ifndef GLP_ANALYZER_SETTINGS
#define GLP_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class GLPAnalyzerSettings : public AnalyzerSettings
{
public:
	GLPAnalyzerSettings();
	virtual ~GLPAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
	Channel mLabelChannel;
	U32 mBitRate;

	U32 mPeriod;

	U32 mGapTime;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mLabelChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mPeriodInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mGapInterface;
};

#endif //GLP_ANALYZER_SETTINGS
