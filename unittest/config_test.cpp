#include "gtest/gtest.h"
#include "../config/config.hpp"
#include <fstream>

TEST(ConfigTest, Load) {
  std::ofstream xml("sdv.xml");
  xml << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\" ?>\n";
  xml << "<sdvConfig>\n";
  xml << "	<route>\n";
  xml << "		<path>/sdv/1.mpg</path>\n";
  xml << "		<qamDestination>5500000.51</qamDestination>\n";
  xml << "		<destination>192.0.2.11</destination>\n";
  xml << "		<destinationPort>101</destinationPort>\n";
  xml << "		<multicastAddress>232.1.1.1</multicastAddress>\n";
  xml << "	</route>\n";
  xml << "	<route>\n";
  xml << "		<path>/sdv/2.mpg</path>\n";
  xml << "		<qamDestination>5500000.52</qamDestination>\n";
  xml << "		<destination>192.0.2.12</destination>\n";
  xml << "		<destinationPort>102</destinationPort>\n";
  xml << "		<multicastAddress>232.1.1.2</multicastAddress>\n";
  xml << "	</route>\n";
  xml << "</sdvConfig>\n";
  xml.close();

  config::SDV c = config::Load("sdv.xml");
  ASSERT_EQ(2, c.routes_.size());
}
