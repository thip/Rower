#include <gtest/gtest.h>
#include "../src/jsonPresenter.h"


TEST(JsonPresenter, no_data_zeroes) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Present([](char* json){
      EXPECT_STREQ(json, "{\"distance\":0,\"velocity\":0.00}");
  });
}

TEST(JsonPresenter, distance_1) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Distance(1.0f);
  
  jsonPresenter->Present([](char* json){
      EXPECT_STREQ(json, "{\"distance\":1,\"velocity\":0.00}");
  });
}

TEST(JsonPresenter, distance_2) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Distance(2.0f);
  
  jsonPresenter->Present([](char* json){
      EXPECT_STREQ(json, "{\"distance\":2,\"velocity\":0.00}");
  });
}

TEST(JsonPresenter, distance_10000) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Distance(10000.0f);
  
  jsonPresenter->Present([](char* json){
      EXPECT_STREQ(json, "{\"distance\":10000,\"velocity\":0.00}");
  });
}

TEST(JsonPresenter, velocity_1) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Velocity(1.0f);
  
  jsonPresenter->Present([](char* json){
      EXPECT_STREQ(json, "{\"distance\":0,\"velocity\":1.00}");
  });
}

TEST(JsonPresenter, velocity_2_5) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Velocity(2.5f);
  
  jsonPresenter->Present([](char* json){
      EXPECT_STREQ(json, "{\"distance\":0,\"velocity\":2.50}");
  });
}

TEST(JsonPresenter, velocity_10_53) {
  JsonPresenter* jsonPresenter = new JsonPresenter();

  jsonPresenter->Velocity(10.53f);
  
  jsonPresenter->Present([](char* json){
      EXPECT_STREQ(json, "{\"distance\":0,\"velocity\":10.53}");
  });
}