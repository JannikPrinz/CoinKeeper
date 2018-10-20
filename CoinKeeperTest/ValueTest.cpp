#include "stdafx.h"
#include "..\CoinKeeper\constants.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace CoinKeeperTest
{
	[TestClass]
	public ref class ValueTestClass
	{
	public:
		[TestMethod]
		void TestEqual()
		{
			Value a = Value(1, 1);
			Value b = Value(1, 1);
			Assert::IsTrue(a == b);
		}

		[TestMethod]
		void TestNotEqual()
		{
			Value a = Value(0, 0);
			Value b = Value(1, 1);
			Assert::IsTrue(a != b);
			Value c = Value(-1, 0);
			Value d = Value(1, 0);
			Assert::IsTrue(a != b);
		}

		[TestMethod]
		void TestToString()
		{
			Value a = Value(0, 0);
			Assert::IsTrue(a.ToString() == "0,00");
			a = Value(1, 7);
			Assert::IsTrue(a.ToString() == "1,07");
			a = Value(1, 70);
			Assert::IsTrue(a.ToString() == "1,70");
			a = Value(-1, 7);
			Assert::IsTrue(a.ToString() == "-1,07");
			a = Value(-1, 70);
			Assert::IsTrue(a.ToString() == "-1,70");
			a = Value(0, -7);
			Assert::IsTrue(a.ToString() == "-0,07");
			a = Value(0, -70);
			Assert::IsTrue(a.ToString() == "-0,70");
			a = Value(1250, 70);
			Assert::IsTrue(a.ToString() == "1.250,70");
			a = Value(-1250000, 7);
			Assert::IsTrue(a.ToString() == "-1.250.000,07");
		}

		[TestMethod]
		void TestMultiply()
		{
			Value a = Value(1, 20);
			Value b = a * -1;
			Assert::IsTrue(b == Value(-1, 20));
			Value c = a * 5;
			Assert::IsTrue(c == Value(6, 0));
			Value d = a * 7;
			Assert::IsTrue(d == Value(8, 40));
			c *= -2;
			Assert::IsTrue(c == Value(-12, 0));
			Value x = Value(0, 20);
			Assert::IsTrue(Value(0, -20) == x * -1);
		}

		[TestMethod]
		void TestAddPP()
		{
			Value a = Value(0, 0);
			Value b = Value(0, 0);
			Value c = a + b;
			Assert::IsTrue(c == Value(0, 0));
			a = Value(2, 1);
			b = Value(1, 1);
			c = a + b;
			Assert::IsTrue(c == Value(3, 2));
			a = Value(2, 11);
			b = Value(0, 0);
			c = a + b;
			Assert::IsTrue(c == Value(2, 11));
			a = Value(2, 11);
			b = Value(0, 99);
			c = a + b;
			Assert::IsTrue(c == Value(3, 10));
		}

		[TestMethod]
		void TestAddPN()
		{
			Value a = Value(0, 0);
			Value b = Value(-1, 1);
			Value c = a + b;
			Assert::IsTrue(c == Value(-1, 1));
			a = Value(2, 1);
			b = Value(-1, 1);
			c = a + b;
			Assert::IsTrue(c == Value(1, 0));
			a = Value(2, 1);
			b = Value(-1, 2);
			c = a + b;
			Assert::IsTrue(c == Value(0, 99));
			a = Value(2, 1);
			b = Value(-2, 1);
			c = a + b;
			Assert::IsTrue(c == Value(0, 0));
			a = Value(2, 10);
			b = Value(-2, 30);
			c = a + b;
			Assert::IsTrue(c == Value(0, -20));
			a = Value(1, 10);
			b = Value(0, -30);
			c = a + b;
			Assert::IsTrue(c == Value(0, 80));
			a = Value(2, 40);
			b = Value(0, -30);
			c = a + b;
			Assert::IsTrue(c == Value(2, 10));
			a = Value(2, 40);
			b = Value(-1, 80);
			c = a + b;
			Assert::IsTrue(c == Value(0, 60));
			a = Value(2, 40);
			b = Value(-2, 80);
			c = a + b;
			Assert::IsTrue(c == Value(0, -40));
		}

		[TestMethod]
		void TestAddNP()
		{
			Value a = Value(0, 0);
			Value b = Value(-1, 1);
			Value c = b + a;
			Assert::IsTrue(c == Value(-1, 1));
			a = Value(2, 1);
			b = Value(-1, 1);
			c = b + a;
			Assert::IsTrue(c == Value(1, 0));
			a = Value(2, 1);
			b = Value(-1, 2);
			c = b + a;
			Assert::IsTrue(c == Value(0, 99));
			a = Value(2, 1);
			b = Value(-2, 1);
			c = b + a;
			Assert::IsTrue(c == Value(0, 0));
			a = Value(2, 10);
			b = Value(-2, 30);
			c = b + a;
			Assert::IsTrue(c == Value(0, -20));
			a = Value(1, 10);
			b = Value(0, -30);
			c = b + a;
			Assert::IsTrue(c == Value(0, 80));
			a = Value(2, 40);
			b = Value(0, -30);
			c = b + a;
			Assert::IsTrue(c == Value(2, 10));
			a = Value(2, 40);
			b = Value(-1, 80);
			c = b + a;
			Assert::IsTrue(c == Value(0, 60));
			a = Value(2, 40);
			b = Value(-2, 80);
			c = b + a;
			Assert::IsTrue(c == Value(0, -40));
			a = Value(0, 40);
			b = Value(-2, 80);
			c = b + a;
			Assert::IsTrue(c == Value(-2, 40));
			a = Value(0, 40);
			b = Value(0, -80);
			c = b + a;
			Assert::IsTrue(c == Value(0, -40));
		}

		[TestMethod]
		void TestAddNN()
		{
			Value a = Value(-1, 10);
			Value b = Value(-1, 1);
			Value c = a + b;
			Assert::IsTrue(c == Value(-2, 11));
			a = Value(0, -10);
			b = Value(-1, 1);
			c = a + b;
			Assert::IsTrue(c == Value(-1, 11));
			a = Value(0, -10);
			b = Value(0, -1);
			c = a + b;
			Assert::IsTrue(c == Value(0, -11));
			a = Value(-1, 10);
			b = Value(-1, 99);
			c = a + b;
			Assert::IsTrue(c == Value(-3, 9));
			a = Value(0, -50);
			b = Value(-1, 50);
			c = a + b;
			Assert::IsTrue(c == Value(-2, 0));
		}
	};
}