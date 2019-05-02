#pragma once

#include <cstdint>
#include <vector>

namespace bv
{
	struct PNode
	{
	public:
		std::vector<size_t> branches;
		size_t datum;

		PNode()
		{
		}

		PNode(size_t datum)
		{
			this->datum = datum;
		}

		static bool Parse(std::string jsonpath, std::vector<PNode>* tree)
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
			if (json["nodes"].is_array())
			{
				for (auto& e : json["nodes"].items())
				{
					auto& value = e.value();

					PNode node(value["datum"].get<size_t>());
					for (auto& b : value["branches"].items())
					{
						node.branches.push_back(b.value().get<size_t>());
					}
					tree->push_back(node);
				}
			}
			else
			{
				return false;
			}

			return true;
		}

		static void Serialise(std::string jsonpath, std::vector<bv::PNode>* nodes)
		{
			nlohmann::json json;
			json[u8"nodes"] = {};
			for (bv::PNode& n : *nodes)
			{
				json[u8"nodes"].push_back({
					{ u8"branches", n.branches },
					{ u8"datum", n.datum },
					});
			}

			std::ofstream o(jsonpath, std::ios::binary);
			o << std::setw(4) << json << std::endl;
			o.close();
		}
	};
}