#ifndef GLP_ANALYZER_RESULTS
#define GLP_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class GLPAnalyzer;
class GLPAnalyzerSettings;

class GLPAnalyzerResults : public AnalyzerResults
{
public:
	GLPAnalyzerResults( GLPAnalyzer* analyzer, GLPAnalyzerSettings* settings );
	virtual ~GLPAnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );
protected: //functions

protected:  //vars
	GLPAnalyzerSettings* mSettings;
	GLPAnalyzer* mAnalyzer;
};

#endif //GLP_ANALYZER_RESULTS
