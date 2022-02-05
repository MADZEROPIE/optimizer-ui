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

		unsigned GKLSDimention = 2;
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
		bool globalM = false;
		bool localM = true;
		bool levelM = false;

		// Index
		bool noneZ = false;
		bool localZ = true;
		bool globalZ = false;

		// New point
		bool halfPnt = false;
		bool medianPnt = true;
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
}