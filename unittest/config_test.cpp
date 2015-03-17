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
  config::Route r1 = c.routes_[0];
  ASSERT_EQ("/sdv/1.mpg", r1.path);
  ASSERT_EQ("5500000.51", r1.qam_destination);
  ASSERT_EQ("192.0.2.11", r1.destination);
  ASSERT_EQ("101", r1.destination_port);
  ASSERT_EQ("232.1.1.1", r1.multicast_address);
  config::Route r2 = c.routes_[1];
  ASSERT_EQ("/sdv/2.mpg", r2.path);
  ASSERT_EQ("5500000.52", r2.qam_destination);
  ASSERT_EQ("192.0.2.12", r2.destination);
  ASSERT_EQ("102", r2.destination_port);
  ASSERT_EQ("232.1.1.2", r2.multicast_address);

  remove("sdv.xml");
}
