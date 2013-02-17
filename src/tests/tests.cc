/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    status = CxxTest::Main<CxxTest::ErrorPrinter>( tmp, argc, argv );
    return status;
}
bool suite_EntitySystemTestSuite_init = false;
#include "C:\Users\Arttu\Desktop\Projects\Viqo\src\tests\main.cc"

static EntitySystemTestSuite suite_EntitySystemTestSuite;

static CxxTest::List Tests_EntitySystemTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EntitySystemTestSuite( "main.cc", 20, "EntitySystemTestSuite", suite_EntitySystemTestSuite, Tests_EntitySystemTestSuite );

static class TestDescription_suite_EntitySystemTestSuite_testEmptySystem : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EntitySystemTestSuite_testEmptySystem() : CxxTest::RealTestDescription( Tests_EntitySystemTestSuite, suiteDescription_EntitySystemTestSuite, 25, "testEmptySystem" ) {}
 void runTest() { suite_EntitySystemTestSuite.testEmptySystem(); }
} testDescription_suite_EntitySystemTestSuite_testEmptySystem;

static class TestDescription_suite_EntitySystemTestSuite_testCreation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EntitySystemTestSuite_testCreation() : CxxTest::RealTestDescription( Tests_EntitySystemTestSuite, suiteDescription_EntitySystemTestSuite, 40, "testCreation" ) {}
 void runTest() { suite_EntitySystemTestSuite.testCreation(); }
} testDescription_suite_EntitySystemTestSuite_testCreation;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
