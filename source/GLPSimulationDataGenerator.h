#ifndef GLP_SIMULATION_DATA_GENERATOR
#define GLP_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class GLPAnalyzerSettings;

class GLPSimulationDataGenerator
{
public:
	GLPSimulationDataGenerator();
	~GLPSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, GLPAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	GLPAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //GLP_SIMULATION_DATA_GENERATOR