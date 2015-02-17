#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTest
{		
	TEST_CLASS(texterTest){

	public:
		TEST_METHOD(texterConstructorTest){
			Texter testClass;

			int expectedNumOfLines = 0;
			int constructorNum = testClass.getTotalNumberOfLines();

			Assert::AreEqual(expectedNumOfLines, constructorNum);
		}

	};
}