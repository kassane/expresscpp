#include "expresscpp/expresscpp.hpp"
#include "gtest/gtest.h"

using namespace expresscpp;

TEST(BasicTests, StartAndStop) {
  {
    auto app = std::make_shared<ExpressCpp>();
    EXPECT_NE(app, nullptr);
    EXPECT_NE(app->GetRouter(), nullptr);
    app.reset();
  }
  {
    ExpressCpp app;
    EXPECT_NE(app.GetRouter(), nullptr);
  }
}
