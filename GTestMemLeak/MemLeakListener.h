/*Copyright (c) 2012 C.Armitage
Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#pragma once
#include "gtest\gtest.h"
#include <crtdbg.h>

int __cdecl printToStdErr(int reportType, char* szMsg, int* retVal){
	std::cerr << szMsg;
	return 1; // No further processing required by _CrtDebugReport
}

class MemLeakListener : public ::testing::EmptyTestEventListener {
	_CrtMemState memAtStart;
	bool leaksDetected;
	
	virtual void OnTestProgramStart(const ::testing::UnitTest& unit_test){
		_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL, &printToStdErr);
	}
	
	virtual void OnTestStart(const ::testing::TestInfo& test_info){
		_CrtMemCheckpoint( &memAtStart );
		leaksDetected = false;
	}

	virtual void OnTestEnd(const ::testing::TestInfo& test_info){
		if(test_info.result()->Passed()){
			CheckForMemLeaks(test_info);
		}
	}

	void CheckForMemLeaks(const ::testing::TestInfo& test_info){
		_CrtMemState memAtEnd;
		_CrtMemCheckpoint( &memAtEnd );

		_CrtMemState memDiff;
		if ( _CrtMemDifference( &memDiff, &memAtStart, &memAtEnd)){
			leaksDetected = true;
			_CrtMemDumpStatistics( &memDiff );
			FAIL() << "Memory leak in " << test_info.test_case_name() << "." << test_info.name() << '\n';
		}
	}

	virtual void OnTestProgramEnd(const ::testing::UnitTest& unit_test){
		if(leaksDetected){
#ifdef DETAILED_MEM_LEAKS
			_CrtDumpMemoryLeaks();
#else
			std::cerr << "Detailed leak information available by instrumenting your code with DETAILED_MEM_LEAKS macro & MemLeakInstrumentation.h header file.\n";
#endif
		}
		_CrtSetReportHook2(_CRT_RPTHOOK_REMOVE, &printToStdErr);
	}
};
