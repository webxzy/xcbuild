/**
 Copyright (c) 2015-present, Facebook, Inc.
 All rights reserved.

 This source code is licensed under the BSD-style license found in the
 LICENSE file in the root directory of this source tree. An additional grant
 of patent rights can be found in the PATENTS file in the same directory.
 */

#include <plist/Format/SimpleXML.h>
#include <plist/Format/SimpleXMLParser.h>

using plist::Format::Type;
using plist::Format::Encoding;
using plist::Format::Format;
using plist::Format::SimpleXML;
using plist::Format::SimpleXMLParser;
using plist::Object;

SimpleXML::
SimpleXML(Encoding encoding) :
    _encoding(encoding)
{
}

Type SimpleXML::
Type()
{
    return Type::SimpleXML;
}

template<>
std::unique_ptr<SimpleXML> Format<SimpleXML>::
Identify(std::vector<uint8_t> const &contents)
{
    /* Not a standard format; don't auto-detect. */
    return nullptr;
}

template<>
std::pair<Object *, std::string> Format<SimpleXML>::
Deserialize(std::vector<uint8_t> const &contents, SimpleXML const &format)
{
    const std::vector<uint8_t> data = Encodings::Convert(contents, format.encoding(), Encoding::UTF8);

    SimpleXMLParser parser;
    Object *root = parser.parse(data);
    if (root == nullptr) {
        return std::make_pair(nullptr, parser.error());
    }

    return std::make_pair(root, std::string());
}

template<>
std::pair<std::unique_ptr<std::vector<uint8_t>>, std::string> Format<SimpleXML>::
Serialize(Object *object, SimpleXML const &format)
{
    return std::make_pair(nullptr, "not yet implemented");
}

SimpleXML SimpleXML::
Create(Encoding encoding)
{
    return SimpleXML(encoding);
}