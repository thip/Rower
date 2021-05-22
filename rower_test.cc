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