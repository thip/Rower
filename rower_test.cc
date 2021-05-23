#include <gtest/gtest.h>
#include "rower.h"

TEST(Rower, 0_ticks_is_0m) {
  Rower* rower = new Rower();
  
  EXPECT_FLOAT_EQ(rower->GetDistance(), 0.0f);
}

TEST(Rower, 100_ticks_is_20_81m) {
  Rower* rower = new Rower();

  for (int i = 0; i < 100; i++){
    rower->AddPulse(1);
  }
  
  EXPECT_NEAR(rower->GetDistance(), 20.81f, 0.01);
}

TEST(Rower, 150_ticks_is_31_22m) {
  Rower* rower = new Rower();

  for (int i = 0; i < 150; i++){
    rower->AddPulse(1);
  }
  
  EXPECT_NEAR(rower->GetDistance(), 31.22f, 0.01);
}

TEST(Rower, empty_split_is_zero) {
  Rower* rower = new Rower();

  EXPECT_EQ(rower->GetSplit(0), 0);
}

TEST(Rower, first_split) {
  Rower* rower = new Rower();

  for (int i=0; i < 1202; i++){
    rower->AddPulse(1);
  }

  EXPECT_EQ(rower->GetSplit(0), 1202);
}

TEST(Rower, second_empty_split) {
  Rower* rower = new Rower();

  for (int i=0; i < 1202; i++){
    rower->AddPulse(1);
  }

  EXPECT_EQ(rower->GetSplit(1), 0);
}

TEST(Rower, second_non_empty_split) {
  Rower* rower = new Rower();

  for (int i=0; i < 2404; i++){
    rower->AddPulse(1);
  }

  EXPECT_EQ(rower->GetSplit(1), 1202);
}

TEST(Rower, first_split_incomplete) {
  Rower* rower = new Rower();

  for (int i=0; i < 100; i++){
    rower->AddPulse(1);
  }

  EXPECT_EQ(rower->GetSplit(0), 100);
}

TEST(Rower, second_split_incomplete) {
  Rower* rower = new Rower();

  for (int i=0; i < 1302; i++){
    rower->AddPulse(1);
  }

  EXPECT_EQ(rower->GetSplit(1), 100);
}

TEST(Rower, third_split_incomplete) {
  Rower* rower = new Rower();

  for (int i=0; i < 2504; i++){
    rower->AddPulse(1);
  }

  EXPECT_EQ(rower->GetSplit(2), 100);
}
