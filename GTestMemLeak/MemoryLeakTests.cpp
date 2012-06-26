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
#include "gtest\gtest.h"
#include "MemLeakInstrumentation.h"

TEST(MemoryLeakTests, ATestThatNewsWithoutDeletingShouldDetectAMemoryLeakAndFail)
{
	unsigned long *leak = new unsigned long;
}

TEST(MemoryLeakTests, ATestThatDoesNotLeakShouldNotDetectAMemoryLeak)
{
	unsigned long noleak;
}

TEST(MemoryLeakTests, ATestThatFailsWithoutALeakShouldNotDetectAMemoryLeak)
{
	unsigned long noleak;
	FAIL() << "Fail without memory leak.";
}

TEST(MemoryLeakTests, ATestThatFailsWithALeakShouldNotDetectAMemoryLeak)
{
	unsigned long *leak = new unsigned long;
	FAIL() << "Fail with memory leak.";
}

TEST(MemoryLeakTests, ATestThatNewsAnArrayWithoutDeletingShouldDetectAMemoryLeakAndFail)
{
	char* leak = new char[10];	
}

TEST(MemoryLeakTests, ATestThatMallocsShouldDetectAMemoryLeak)
{
	char* leak = static_cast<char*>(malloc(10));
}

// Cause Visual Studio to halt excution due to heap corruption.
//TEST(MemoryLeakTests, ATestThatDeletesMultipleTimesShouldDetectAMemoryCorruption)
//{
//	unsigned long *heap = new unsigned long;
//	delete heap;
//	delete heap;
//}
