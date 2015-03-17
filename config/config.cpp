#include <cstdint>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>

#include "tinyxml/tinyxml.h"
#include "config.hpp"
#include <iostream>

namespace config {

void SDV::Load(TiXmlElement* sub) {
  assert(sub != nullptr);
  TiXmlElement* elem = nullptr;
  elem = sub->FirstChildElement("qamIp");
  if (elem && elem->GetText()) {
    qam_ip = elem->GetText();
  }
  elem = sub->FirstChildElement("qamPort");
  if (elem && elem->GetText()) {
    qam_port = std::stoi(elem->GetText());
  }
  for (TiXmlNode* node = sub->FirstChild(); node; node = node->NextSibling()) {
    TiXmlElement* elem = node->ToElement();
    if (elem && elem->ValueStr() == "route") {
      Route r;
      r.Load(elem);
      routes.push_back(r);
    }
  }
}

void Route::Load(TiXmlElement* sub) {
  assert(sub != nullptr);
  TiXmlElement* elem = nullptr;
  elem = sub->FirstChildElement("path");
  if (elem && elem->GetText()) {
    path = elem->GetText();
  }
  elem = sub->FirstChildElement("qamDestination");
  if (elem && elem->GetText()) {
    qam_destination = elem->GetText();
  }
  elem = sub->FirstChildElement("qamName");
  if (elem && elem->GetText()) {
    qam_name = elem->GetText();
  }
  elem = sub->FirstChildElement("destination");
  if (elem && elem->GetText()) {
    destination = elem->GetText();
  }
  elem = sub->FirstChildElement("destinationPort");
  if (elem && elem->GetText()) {
    destination_port = elem->GetText();
  }
  elem = sub->FirstChildElement("multicastAddress");
  if (elem && elem->GetText()) {
    multicast_address = elem->GetText();
  }
}

SDV Load(const std::string& filepath) {
  TiXmlDocument doc(filepath.c_str());
  if (false == doc.LoadFile()) {
    throw ParseError("fail to parse xml");
  }

  TiXmlElement* root = doc.RootElement();
  if (nullptr == root) {
    throw ParseError("invalid xml config, root element is null");
  }

  if ("sdvConfig" != root->ValueStr()) {
    throw ParseError("invalid xml config, root element must be admConfig");
  }

  SDV sdv;
  sdv.Load(root);
  return sdv;
}

}  // namespace config
