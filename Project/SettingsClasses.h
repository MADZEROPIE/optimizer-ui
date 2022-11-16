#pragma once

namespace optimizerui
{
	using namespace System;

	ref class GraphSettings	{

	public:

		bool isIsolinesColored = false;
		bool numersOnIsolinesPlot = false;
		bool isGraphAppearsInNewWindow = true;
		bool showOneDimSolutionGraph = false;

	public:

		GraphSettings()
		{	}
		//Dispose
		~GraphSettings()
		{
			//release managed resources

			//call finalizer
			this->!GraphSettings();
		}
		!GraphSettings()
		{
			//release unmanaged resources
		}
	};
	ref class AlgorithmSettings	{
	public:

		bool isLocalEnabled = false;
		bool localVerification = false;
		int localMix = 0;
		int alpha = 15;
		int localStartIteration = 100;
		int localAdaptationMode = 0;

		AlgorithmSettings()
		{
		}
		//Dispose
		~AlgorithmSettings()
		{
			//release managed resources

			//call finalizer
			this->!AlgorithmSettings();
		}
		!AlgorithmSettings()
		{
			//release unmanaged resources
		}
	};
	ref class TaskGeneratorSettings	{
	public:

		unsigned GKLSDimension = 2;
		String ^dllPath = L"CustomProblem.dll";

		TaskGeneratorSettings()
		{
		}
		//Dispose
		~TaskGeneratorSettings()
		{
			//release managed resources

			//call finalizer
			this->!TaskGeneratorSettings();
		}
		!TaskGeneratorSettings()
		{
			//release unmanaged resources
		}
	};
	ref class AdaptiveNestedSettings {
	public:
		// Lipshitz
		bool globalM = true;
		bool localM = false;
		bool levelM = false;
		bool adaptiveM = false;

		// Index
		bool noneZ = true;
		bool localZ = false;
		bool globalZ = false;

		// New point
		bool halfPnt = true;
		bool medianPnt = false;

		// Monotonous
        bool notMonotonous = true;
        bool Monotonous = false;

		AdaptiveNestedSettings()
		{
		}
		//Dispose
		~AdaptiveNestedSettings()
		{
			//release managed resources

			//call finalizer
			this->!AdaptiveNestedSettings();
		}
		!AdaptiveNestedSettings()
		{
			//release unmanaged resources
		}
	};

	ref class LanguageSettings {
	public:

		bool english = true;

		LanguageSettings()
		{
		}
		//Dispose
		~LanguageSettings()
		{
			//release managed resources

			//call finalizer
			this->!LanguageSettings();
		}
		!LanguageSettings()
		{
			//release unmanaged resources
		}
	};
}