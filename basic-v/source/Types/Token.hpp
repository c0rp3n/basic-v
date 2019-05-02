#pragma once

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include "Lexeme.hpp"

/*
JSON Schema
{
  "tokens": [
	{
	  "line": "1",
	  "position": "2",
	  "token": "1",
	  "data": ""
	},
	{
	  "line": "1",
	  "position": "5",
	  "token": "4",
	  "data": "hello"
	}
  ]
}
*/

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

        static bool Parse(std::string jsonpath, std::vector<Token>* tokens)
        {
            std::ifstream ifs(jsonpath);
			if (ifs.bad())
			{
				return false;
			}

			std::string data;
			data.assign((std::istreambuf_iterator<char>(ifs)),
						(std::istreambuf_iterator<char>()));

			nlohmann::json json = nlohmann::json::parse(data);
			if (json["tokens"].is_array())
			{
				for (auto& e : json["tokens"].items())
				{
					auto& value = e.value();
					tokens->push_back(bv::Token(value["line"].get<uint64_t>(), value["position"].get<uint64_t>(), (bv::Lexeme)value["token"].get<uint64_t>(), value["value"].get<std::string>()));
				}
			}
			else
			{
				return false;
			}

            return true;
        } 

        static void Serialise(std::string jsonpath, std::vector<Token>* tokens)
        {
			nlohmann::json json;
			json["tokens"] = {};
			for (bv::Token& t : *tokens)
			{
				json["tokens"].push_back({
					{ "line", t.line },
					{ "position", t.position },
					{ "token", t.token },
					{ "value", t.value }
				});
			}

			std::ofstream o(jsonpath, std::ios::binary);
			o << std::setw(4) << json << std::endl;
			o.close();
        }
    };
}
