#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTest
{		
	TEST_CLASS(texterTest){

	public:
		TEST_METHOD(texterConstructorTest){
			Texter testClass("emptyTextFile.txt");

			int expectedNumOfLines = 0;
			int constructorNum = testClass.getTotalNumberOfLines();

			Assert::AreEqual(expectedNumOfLines, constructorNum);
		}

		TEST_METHOD(texterCompressLineTest){
			Texter testClass("emptyTextFile.txt");

			const string expectedStringOutput = "teststring";
			const string actualStringOutput = testClass.compressLineTest();

			Assert::AreEqual(expectedStringOutput, actualStringOutput);
		}

		TEST_METHOD(texterSortTest){
			Texter testClass("SortingTest.txt");

			vector<string> expectedStrVec;
			expectedStrVec.push_back("abc");
			expectedStrVec.push_back("abc def");
			expectedStrVec.push_back("acb dfe");
			expectedStrVec.push_back("San");
			expectedStrVec.push_back("San Cristobal");
			expectedStrVec.push_back("Santa Barbara");
			expectedStrVec.push_back("Santa Cruz");
			expectedStrVec.push_back("San Tomas");

			vector<string> actualVec = testClass.getFileVec("SortingTest.txt");

			for (int i = 0; i < actualVec.size(); i++){
				if (actualVec[i] != expectedStrVec[i]){
					Assert::IsFalse;
				}
			}
			
		}

		TEST_METHOD(texterSearchTest){

		}

	};
}