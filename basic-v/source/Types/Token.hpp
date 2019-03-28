#pragma once

#include <cstdint>
#include <iostream>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include "Lexeme.hpp"

namespace bv
{
    struct Token
    {
        uint64_t line;
        uint64_t position;
        Lexeme token;
        std::string value;

        Token()
        {
        };

        Token(uint64_t line, uint64_t position, Lexeme token, std::string value = "")
        {
            this->line = line;
            this->position = position;
            this->token = token;
            this->value = value;
        }

        bool Parse(std::string jsonpath, std::vector<Token>* tokens)
        {
            rapidjson::Document d;
            std::ifstream ifs(jsonpath);
            d.ParseStream(ifs);
            
            if (d["tokens"].IsArray())
            {
                for (auto& v : d.GetArray())
                {
                    tokens->push_back(Token
                    (
                        v["line"].GetUint64(),
                        v["position"].GetUint64(),
                        (Lexeme)(v["token"].GetUint64()),
                        std::string(v["value"].GetString())
                    ));
                }
            }
            else
            {
                return false;
            }

            return true;
        }

        bool Serialise(std::string jsonpath, std::vector<Token>* tokens)
        {
            rapidjson::Document d;
            d.SetObject();
            rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

            rapidjson::Value array(rapidjson::kArrayType);
            array.Reserve(sizeof(uint64_t) * 4 * tokens->size(), allocator);
            for (Token& t : *tokens)
            {
                rapidjson::Value token(rapidjson::kObjectType);
                token.AddMember("line", t.line, allocator);
                token.AddMember("position", t.position, allocator);
                token.AddMember("token", t.token, allocator);
                token.AddMember("value", t.value, allocator);

                array.PushBack(token, allocator);
            }

            d.AddMember("tokens", array, allocator);
            
            std::ofstream ofs(jsonpath);
            rapidjson::Writer<std::ostream> w(ofs);
            d.Accept(w);

            ofs.close();
        }
    };
}
