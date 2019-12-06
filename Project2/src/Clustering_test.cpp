#include "../test/sqrt.cpp"
#include "Point.cpp"
#include "Curve.cpp"
#include "dist.cpp"
#include <gtest/gtest.h>
#include <vector>
#include <iostream>

TEST(PAM, PAMCostPoints){
    vector<void*> items;

    Point *p = new Point("0");
    p->addCoordinate(10);
    p->addCoordinate(9);
    items.push_back((void*)p);

    p = new Point("1");
    p->addCoordinate(1);
    p->addCoordinate(0);
    items.push_back((void*)p);

    p = new Point("2");
    p->addCoordinate(5);
    p->addCoordinate(4);
    items.push_back((void*)p);


    ASSERT_EQ(28, pamCost(items,0,0));
    ASSERT_EQ(26, pamCost(items,1,0));
    ASSERT_EQ(18, pamCost(items,2,0));
}

TEST(PAM, PAMCostCurves){
    vector<void*> items;

    //Curve 0
    Curve *c = new Curve();
    c->setId("0");

    Point *p = new Point("0");
    p->addCoordinate(10);
    p->addCoordinate(9);
    c->PushToVector(p);

    p = new Point("1");
    p->addCoordinate(1);
    p->addCoordinate(0);
    c->PushToVector(p);
    items.push_back((void*)c);


    //Curve 1
    c = new Curve();
    c->setId("1");

    p = new Point("2");
    p->addCoordinate(5);
    p->addCoordinate(4);
    c->PushToVector(p);

    p = new Point("3");
    p->addCoordinate(1);
    p->addCoordinate(0);
    c->PushToVector(p);
    items.push_back((void*)c);


    //Curve 2
    c = new Curve();
    c->setId("2");

    p = new Point("4");
    p->addCoordinate(20);
    p->addCoordinate(21);
    c->PushToVector(p);

    p = new Point("5");
    p->addCoordinate(15);
    p->addCoordinate(14);
    c->PushToVector(p);
    items.push_back((void*)c);

    EXPECT_NEAR(42.4906, pamCost(items,0,1), 0.001);
    EXPECT_NEAR(49.5416, pamCost(items,1,1), 0.001);
    EXPECT_NEAR(77.89, pamCost(items,2,1), 0.001);
}

TEST(SquareRootTest, PositiveNos) 
    { 
    ASSERT_EQ(6, squareRoot(36.0));
    ASSERT_EQ(18.0, squareRoot(324.0));
    ASSERT_EQ(25.4, squareRoot(645.16));
    ASSERT_EQ(0, squareRoot(0.0));
    }
 
TEST(SquareRootTest, NegativeNos) 
    {
    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
    }
 
int main(int argc, char **argv) 
    {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    }
